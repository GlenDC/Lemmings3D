#include "InstancedObject.h"
#include "Graphics/GraphicsDevice.h"
#include "../Materials/InstancedBlockMaterial.h"
#include "OverlordComponents.h"
#include "../Lib/LemmingsHelpers.h"
#include "../Lib/GlobalParameters.h"
#include "Managers/ContentManager.h"
#include "Diagnostics/Logger.h"

InstancedObject::InstancedObject(const tstring & file)
	: m_InstanceVec(0)
	, m_pVertexBuffer(nullptr)
	, m_pInstanceBuffer(nullptr)
	, m_TextureFile(file)
	, m_ReCreateInstanceBuffer(true)
	, m_pMaterial(nullptr)
	, m_pInstancedObject(nullptr)
{

}

InstancedObject::~InstancedObject()
{
	Release();
}

void InstancedObject::Initialize()
{
	bool result(true);

	//m_pInstancedObject = ContentManager::Load<ModelComponent>(_T("./Resources/Lemmings3D/models/LemmingsCube.ovm"));
	//m_pInstancedObject->Initialize();

	// Load the texture for this model.
	result = LoadTexture(GraphicsDevice::GetInstance()->GetDevice(), m_TextureFile);
	ASSERT(result, _T("Couldn't Load the Texture of the instancedObject!"));
	if(!result)
	{
		Release();
		return;
	}

	// Initialize the vertex and instance buffer that hold the geometry for the triangles.
	result = InitializeBuffers(GraphicsDevice::GetInstance()->GetDevice());
	ASSERT(result, _T("Couldn't initialize buffers of the instancedObject!"));
	if(!result)
	{
		ReleaseBuffers();
		return;
	}
}

void InstancedObject::Release()
{
	// Release the model texture.
	ReleaseTexture();

	// Release the vertex and instance buffers.
	ReleaseBuffers();

	SafeDelete(m_pInstancedObject);
}

void InstancedObject::Draw(const GameContext & context)
{
	if(m_ReCreateInstanceBuffer)
	{
		InitializeInstanceBuffer(GraphicsDevice::GetInstance()->GetDevice());
	}
	// Put the vertex and instance buffers on the graphics pipeline to prepare them for drawing.
	RenderBuffers(GraphicsDevice::GetInstance()->GetDevice());
	m_pMaterial->SetEffectVariables(context, nullptr);
	RenderShader(GraphicsDevice::GetInstance()->GetDevice());
}

void InstancedObject::Update(const GameContext & context)
{
}

int InstancedObject::GetVertexCount() const
{
	return VERTEX_COUNT;
}

bool InstancedObject::AddInstance(const D3DXVECTOR3 & position, int id)
{
#ifdef LEVEL_VALIDATION
	for(UINT i = 0 ; i < m_InstancePositionVec.size() ; ++i)
	{
		if(m_InstancePositionVec[i] == position)
		{
			Logger::Log(_T("Illegal action: Don't build 2 blocks at the same position!"), Warning);
			return false;
		}
	}
#endif
	InstanceType instance;
	instance.Position = position;
	instance.ID = id;
	m_InstanceVec.push_back(instance);
	m_InstancePositionVec.push_back(position);

	m_ReCreateInstanceBuffer = true;
	return true;
}

bool InstancedObject::RemoveInstance(const D3DXVECTOR3 & position)
{
	for(UINT i = 0 ; i < m_InstanceVec.size() ; ++i)
	{
		if(m_InstanceVec[i].Position == position)
		{
			m_InstanceVec.erase(m_InstanceVec.begin() + i);
			m_ReCreateInstanceBuffer = true;
			m_InstancePositionVec.erase(m_InstancePositionVec.begin() + i);
			Logger::Log(_T("Editor: environment block deleted!"), Info);
			return true;
		}
	}
	return false;
}

bool InstancedObject::EditInstance(const D3DXVECTOR3 & position, int id)
{
	for(UINT i = 0 ; i < m_InstanceVec.size() ; ++i)
	{
		if(m_InstanceVec[i].Position == position)
		{
			m_InstanceVec[i].ID = id;
			m_ReCreateInstanceBuffer = true;
			return true;
		}
	}
	return false;
}

void InstancedObject::RecheckCubes(std::vector<InstanceType> & vec)
{
	float size = GlobalParameters::GetParameters()->GetParameter<float>(_T("GRID_SIZE"));
	for(UINT i = 0 ; i < m_InstanceVec.size() ; ++i)
	{
		if(m_InstanceVec[i].ID == 1 || m_InstanceVec[i].ID == 5)
		{
			m_InstanceVec[i].ID = 1;
			for(UINT u = 0 ; u < m_InstanceVec.size() ; ++u)
			{
				if(i != u && (m_InstanceVec[u].ID == 1 || m_InstanceVec[u].ID == 5) && 
					m_InstanceVec[i].Position.x == m_InstanceVec[u].Position.x &&
					m_InstanceVec[i].Position.z == m_InstanceVec[u].Position.z &&
					m_InstanceVec[i].Position.y == m_InstanceVec[u].Position.y - size)
				{
					m_InstanceVec[i].ID = 5;
					vec.push_back(m_InstanceVec[i]);
					break;
				}
			}
		}
	}
	m_ReCreateInstanceBuffer = true;
}

int InstancedObject::GetInstanceCount() const
{
	return m_InstanceVec.size();
}


ID3D10ShaderResourceView* InstancedObject::GetTexture() const
{
	return m_pMaterial->GetTexture();
}

D3DXVECTOR3 InstancedObject::GetClosestPosition(const D3DXVECTOR3 & pos)
{
	if(m_InstanceVec.size() > 0)
	{
		D3DXVECTOR3 vecLength(m_InstanceVec[0].Position - pos);
		float length(D3DXVec3Length(&vecLength));
		D3DXVECTOR3 closestPos(m_InstanceVec[0].Position);
		for(UINT i = 1 ; i < m_InstanceVec.size() ; ++i)
		{
			vecLength = m_InstanceVec[i].Position - pos;
			float newLength(D3DXVec3Length(&vecLength));
			if(newLength < length)
			{
				closestPos = m_InstanceVec[i].Position;
				length = newLength;
			}
		}
		return closestPos;
	}
	return D3DXVECTOR3();
}

void InstancedObject::ParsePositionVector(std::vector<D3DXVECTOR3> & posVec) const
{
	for(UINT i = 0 ; i < m_InstanceVec.size() ; ++i)
	{
		posVec.push_back(m_InstanceVec[i].Position);
	}
}


bool InstancedObject::InitializeBuffers(ID3D10Device* device)
{
	HRESULT result;
	
	D3D10_BUFFER_DESC vertexBufferDesc;
	D3D10_SUBRESOURCE_DATA vertexData;

	// Set up the description of the vertex buffer.
	vertexBufferDesc.Usage = D3D10_USAGE_DEFAULT;
	vertexBufferDesc.ByteWidth = sizeof(VertexType) * GetVertexCount();
	vertexBufferDesc.BindFlags = D3D10_BIND_VERTEX_BUFFER;
	vertexBufferDesc.CPUAccessFlags = 0;
	vertexBufferDesc.MiscFlags = 0;
	
	float size = GlobalParameters::GetParameters()->GetParameter<float>(_T("GRID_SIZE"));
	size *= 0.5f;

	VertexType ver[8];
	ver[0].Position = D3DXVECTOR4(-size, size, -size, 1.0f);
	ver[0].TexCoords = D3DXVECTOR2(0, 0);
	ver[1].Position = D3DXVECTOR4(size, size, -size, 1.0f);
	ver[1].TexCoords = D3DXVECTOR2(1, 0);
	ver[2].Position = D3DXVECTOR4(-size, -size, -size, 1.0f);
	ver[2].TexCoords = D3DXVECTOR2(0, 1);
	ver[3].Position = D3DXVECTOR4(size, -size, -size, 1.0f);
	ver[3].TexCoords = D3DXVECTOR2(1, 1);
	ver[4].Position = D3DXVECTOR4(-size, size, size, 1.0f);
	ver[4].TexCoords = D3DXVECTOR2(1, 0);
	ver[5].Position = D3DXVECTOR4(size, size, size, 1.0f);
	ver[5].TexCoords = D3DXVECTOR2(0, 1);
	ver[6].Position = D3DXVECTOR4(-size, -size, size, 1.0f);
	ver[6].TexCoords = D3DXVECTOR2(1, 1);
	ver[7].Position = D3DXVECTOR4(size, -size, size, 1.0f);
	ver[7].TexCoords = D3DXVECTOR2(0, 0);

	// Set Vertex Points
	VertexType vertices[VERTEX_COUNT];
	#pragma region

		#pragma region
		vertices[0] = ver[4];
		vertices[1] = ver[5];
		vertices[2] = ver[0];
		vertices[3] = ver[0];
		vertices[4] = ver[5];
		vertices[5] = ver[1];
		vertices[0].Normal = D3DXVECTOR3(0,1,0);
		vertices[1].Normal = D3DXVECTOR3(0,1,0);
		vertices[2].Normal = D3DXVECTOR3(0,1,0);
		vertices[3].Normal = D3DXVECTOR3(0,1,0);
		vertices[4].Normal = D3DXVECTOR3(0,1,0);
		vertices[5].Normal = D3DXVECTOR3(0,1,0);
		#pragma endregion top-plane

		#pragma region
		vertices[6] = ver[2];
		vertices[7] = ver[3];
		vertices[8] = ver[6];
		vertices[9] = ver[6];
		vertices[10] = ver[3];
		vertices[11] = ver[7];
		vertices[6].Normal = D3DXVECTOR3(0,-1,0);
		vertices[7].Normal = D3DXVECTOR3(0,-1,0);
		vertices[8].Normal = D3DXVECTOR3(0,-1,0);
		vertices[9].Normal = D3DXVECTOR3(0,-1,0);
		vertices[10].Normal = D3DXVECTOR3(0,-1,0);
		vertices[11].Normal = D3DXVECTOR3(0,-1,0);
		#pragma endregion bottom-plane

		#pragma region
		vertices[12] = ver[5];
		vertices[13] = ver[4];
		vertices[14] = ver[7];
		vertices[15] = ver[7];
		vertices[16] = ver[4];
		vertices[17] = ver[6];
		vertices[12].Normal = D3DXVECTOR3(0,0,1);
		vertices[13].Normal = D3DXVECTOR3(0,0,1);
		vertices[14].Normal = D3DXVECTOR3(0,0,1);
		vertices[15].Normal = D3DXVECTOR3(0,0,1);
		vertices[16].Normal = D3DXVECTOR3(0,0,1);
		vertices[17].Normal = D3DXVECTOR3(0,0,1);
		#pragma endregion back-plane

		#pragma region
		vertices[18] = ver[0];
		vertices[19] = ver[1];
		vertices[20] = ver[2];
		vertices[21] = ver[2];
		vertices[22] = ver[1];
		vertices[23] = ver[3];
		vertices[18].Normal = D3DXVECTOR3(0,0,-1);
		vertices[19].Normal = D3DXVECTOR3(0,0,-1);
		vertices[20].Normal = D3DXVECTOR3(0,0,-1);
		vertices[21].Normal = D3DXVECTOR3(0,0,-1);
		vertices[22].Normal = D3DXVECTOR3(0,0,-1);
		vertices[23].Normal = D3DXVECTOR3(0,0,-1);
		#pragma endregion front-plane

		#pragma region
		vertices[24] = ver[4];
		vertices[25] = ver[0];
		vertices[26] = ver[6];
		vertices[27] = ver[6];
		vertices[28] = ver[0];
		vertices[29] = ver[2];
		vertices[24].Normal = D3DXVECTOR3(-1,0,0);
		vertices[25].Normal = D3DXVECTOR3(-1,0,0);
		vertices[26].Normal = D3DXVECTOR3(-1,0,0);
		vertices[27].Normal = D3DXVECTOR3(-1,0,0);
		vertices[28].Normal = D3DXVECTOR3(-1,0,0);
		vertices[29].Normal = D3DXVECTOR3(-1,0,0);
		#pragma endregion left-plane

		#pragma region
		vertices[30] = ver[1];
		vertices[31] = ver[5];
		vertices[32] = ver[3];
		vertices[33] = ver[3];
		vertices[34] = ver[5];
		vertices[35] = ver[7];
		vertices[30].Normal = D3DXVECTOR3(1,0,0);
		vertices[31].Normal = D3DXVECTOR3(1,0,0);
		vertices[32].Normal = D3DXVECTOR3(1,0,0);
		vertices[33].Normal = D3DXVECTOR3(1,0,0);
		vertices[34].Normal = D3DXVECTOR3(1,0,0);
		vertices[35].Normal = D3DXVECTOR3(1,0,0);
		#pragma endregion right-plane
	#pragma endregion Set up vertices...
		
	// Give the subresource structure a pointer to the vertex data.
	vertexData.pSysMem = vertices;

	if(m_pVertexBuffer != nullptr)
	{
		SafeRelease(m_pVertexBuffer);
	}

	// Now finally create the vertex buffer.
	result = device->CreateBuffer(&vertexBufferDesc, &vertexData, &m_pVertexBuffer);
	ASSERT(SUCCEEDED(result), _T("Couldn't create the Vertex buffer!"));

    // Set vertex buffer(s)
   /* UINT offset = 0;
	UINT stride = sizeof(VertexType) * GetVertexCount();*/
	//GraphicsDevice::GetInstance()->GetDevice()->IASetVertexBuffers( 0, 1, &m_pVertexBuffer , &stride, &offset );


	// Next we create a temporary instance array using the instance count. 
	// Note we use the InstanceType structure for the array type which is defined 
	//// in the ModelClass header file.

	//// Create the instance array.
	//pInstances = new InstanceType[m_InstanceCount];
	//if(pInstances == nullptr)
	//{
	//	return false;
	//}

	//Now here is where we setup the different positions for each instance of the triangle. 
	// I have set four different x, y, z positions for each triangle. Note that this is where 
	// you could set color, scaling, different texture coordinates, and so forth. 
	// An instance can be modified in any way you want it to be. For this tutorial 
	// I used position as it is easy to see visually which helps understand how instancing works.

	// Load the instance array with data.
	/*pInstances[0].position = D3DXVECTOR3(-1.5f, -1.5f, 5.0f);
	pInstances[1].position = D3DXVECTOR3(-1.5f,  1.5f, 5.0f);
	pInstances[2].position = D3DXVECTOR3( 1.5f, -1.5f, 5.0f);
	pInstances[3].position = D3DXVECTOR3( 1.5f,  1.5f, 5.0f);*/

	//The instance buffer description is setup exactly the same as a vertex buffer description.

	InitializeInstanceBuffer(device);
	// Release the instance array now that the instance buffer has been created and loaded.
	/*delete [] pInstances;
	pInstances = nullptr;*/

	return true;
}

void InstancedObject::InitializeInstanceBuffer(ID3D10Device * pDevice)
{
	HRESULT result;

	//VertexType* pVertices;
	//D3D10_BUFFER_DESC vertexBufferDesc, instanceBufferDesc;
	D3D10_BUFFER_DESC instanceBufferDesc;
	//D3D10_SUBRESOURCE_DATA vertexData, instanceData;
	D3D10_SUBRESOURCE_DATA instanceData;

	// Set up the description of the instance buffer.
	instanceBufferDesc.Usage = D3D10_USAGE_DEFAULT;
	instanceBufferDesc.ByteWidth = sizeof(InstanceType) * GetInstanceCount();
	instanceBufferDesc.BindFlags = D3D10_BIND_VERTEX_BUFFER;
	instanceBufferDesc.CPUAccessFlags = 0;
	instanceBufferDesc.MiscFlags = 0;

	// Just like the vertex buffer we get the pointer to the instance array 
	// and then create the instance buffer. Once the instance buffer is created 
	// we can release the temporary instance array since the data from the array 
	// has been copied into the instance buffer.

	// Give the subresource structure a pointer to the instance data.
	instanceData.pSysMem = &m_InstanceVec[0];

	if(m_pInstanceBuffer != nullptr)
	{
		SafeRelease(m_pInstanceBuffer);
	}

	// Create the instance buffer.
	result = pDevice->CreateBuffer(&instanceBufferDesc, &instanceData, &m_pInstanceBuffer);
	ASSERT(SUCCEEDED(result), _T("Couldn't create the instance buffer!"));

	m_ReCreateInstanceBuffer = false;
}

void InstancedObject::ReleaseBuffers()
{
	// Release the new instance buffer in the ShutdownBuffers function.
	// Release the instance buffer.
	if(m_pInstanceBuffer)
	{
		m_pInstanceBuffer->Release();
		m_pInstanceBuffer = nullptr;
	}

	// Release the vertex buffer.
	if(m_pVertexBuffer)
	{
		m_pVertexBuffer->Release();
		m_pVertexBuffer = nullptr;
	}

	return;
}

void InstancedObject::RenderBuffers(ID3D10Device* device)
{
	unsigned int strides[2];
	unsigned int offsets[2];
	ID3D10Buffer* bufferPointers[2];
	
	// The instance buffer is just a second vertex buffer containing different 
	// information so it is set on the device at the same time using the same call 
	// as the vertex buffer. So instead of how we previously sent in a single stride, offset, 
	// and buffer we now send an array of strides, offsets, and buffers to the IASetVertexBuffers call.

	// First we set the two strides to the size of the VertexType and InstanceType.

	// Set the buffer strides.
	strides[0] = sizeof(VertexType); 
	strides[1] = sizeof(InstanceType); 

	// We then set the offsets for both the vertex and instance buffer.

	// Set the buffer offsets.
	offsets[0] = 0;
	offsets[1] = 0;

	// Next we create an array that holds the pointers to the vertex buffer and the instance buffer.

	// Set the array of pointers to the vertex and instance buffers.
	bufferPointers[0] = m_pVertexBuffer;	
	bufferPointers[1] = m_pInstanceBuffer;

	// Finally we set both the vertex buffer and the instance buffer on the device in the same call.

	// Set the vertex and instance buffers to active in the input assembler so it can be rendered.
	device->IASetVertexBuffers(0, 2, bufferPointers, strides, offsets);

	// Set the type of primitive that should be rendered from this vertex buffer, in this case triangles.
	device->IASetPrimitiveTopology(D3D10_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
}

void InstancedObject::RenderShader(ID3D10Device* pDevice)
{
	D3D10_TECHNIQUE_DESC techniqueDesc;
	unsigned int i;

	// Set the input layout.
	ID3D10InputLayout * inputLayout = m_pMaterial->GetInputLayout();
	pDevice->IASetInputLayout(inputLayout);

	// Get the description structure of the technique from inside the shader so it can be used for rendering.
	m_pMaterial->GetDefaultTechnique()->GetDesc(&techniqueDesc);

	// Go through each pass in the technique (should be just one currently) and render the triangles.
	for(i=0; i<techniqueDesc.Passes; ++i)
	{
		m_pMaterial->GetDefaultTechnique()->GetPassByIndex(i)->Apply(0);
		pDevice->DrawInstanced(GetVertexCount(), GetInstanceCount(), 0, 0);
	}
}

bool InstancedObject::LoadTexture(ID3D10Device* device, const tstring & file)
{
	// Create the material object
	m_pMaterial = new InstancedBlockMaterial();
	if(m_pMaterial == nullptr)
	{
		return false;
	}

	// Initialize the material object
	m_pMaterial->Initialize();
	m_pMaterial->SetTexture(_T("./Resources/Lemmings3D/textures/EnvironmentTextures.png"));
	return true;
}


void InstancedObject::ReleaseTexture()
{
	// Release the material object
	if(m_pMaterial != nullptr)
	{
		delete m_pMaterial;
		m_pMaterial = nullptr;
	}
}