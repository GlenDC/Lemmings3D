#include "RisingWater.h"
#include "../Materials/InstancedWaterMaterial.h"
#include "../Lib/GlobalParameters.h"
#include "Graphics/GraphicsDevice.h"
#include "../Managers/Stopwatch.h"
#include "Managers/ContentManager.h"
#include "../Lib/LemmingsHelpers.h"
#include <cmath>

RisingWater::RisingWater (float minDepth, float maxDepth)
	: m_InstanceVec(0)
	, m_pVertexBuffer(nullptr)
	, m_pInstanceBuffer(nullptr)
	, m_ReCreateInstanceBuffer(true)
	, m_pMaterial(nullptr)
	, m_WaterLevel(0)
	, m_RefreshWater(true)
	, m_WaterRange(maxDepth - minDepth)
	, m_pWaterLevelTexture(nullptr)
{
}

RisingWater::~RisingWater()
{
	Release();
}

void RisingWater::Initialize()
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
	
	m_pWaterLevelTexture = ContentManager::Load<ID3D10ShaderResourceView>(_T("./Resources/Lemmings3D/ui/Minimap_Waterlevel.png"));

	m_WaterSprite.pTexture = m_pWaterLevelTexture;
	m_WaterSprite.Color = D3DXCOLOR(1,1,1,1);

	Stopwatch::GetInstance()->CreateTimer(_T("RefreshWater"), 2.5f, false, true, [&] () { m_RefreshWater = true; });
}

void RisingWater::Release()
{
	// Release the model texture.
	ReleaseTexture();

	// Release the vertex and instance buffers.
	ReleaseBuffers();
}

void RisingWater::Update(const GameContext & context)
{
	m_WaterLevel += context.GameTime.ElapsedSpeedGameTime * (float)WATER_LEVEL_RISE_SPEED * 0.5f;
	if(m_RefreshWater)
	{
		RandomizeWater();
		m_ReCreateInstanceBuffer = true;
		m_RefreshWater = false;
	}
}

void RisingWater::Draw(const GameContext & context)
{
	if(m_ReCreateInstanceBuffer)
	{
		InitializeInstanceBuffer(GraphicsDevice::GetInstance()->GetDevice());
	}
	// Put the vertex and instance buffers on the graphics pipeline to prepare them for drawing.
	RenderBuffers(GraphicsDevice::GetInstance()->GetDevice());
	m_pMaterial->SetWaterLevel(m_WaterLevel);
	m_pMaterial->SetWaterAlpha(0.25f + 0.75f * (m_WaterLevel / m_WaterRange));
	m_pMaterial->SetEffectVariables(context, nullptr);
	RenderShader(GraphicsDevice::GetInstance()->GetDevice());
}

void RisingWater::Draw2D(const GameContext & context)
{
	m_WaterSprite.Transform = LemmingsHelpers::MatrixScale(1,m_WaterLevel / m_WaterRange * -2.25f, 1) * 
								LemmingsHelpers::MatrixTranslation(945,687,0.02f);
    SpriteBatch::Draw(m_WaterSprite);
}

int RisingWater::GetVertexCount() const
{
	return VERTEX_COUNT;
}

bool RisingWater::AddInstance(const D3DXVECTOR3 & position)
{
	InstanceType instance;
	instance.Position = position;
	instance.HeightLevel = 0;
	m_InstanceVec.push_back(instance);

	m_ReCreateInstanceBuffer = true;
	return true;
}

bool RisingWater::RemoveInstance(const D3DXVECTOR3 & position)
{
	for(UINT i = 0 ; i < m_InstanceVec.size() ; ++i)
	{
		if(m_InstanceVec[i].Position == position)
		{
			m_InstanceVec.erase(m_InstanceVec.begin() + i);
			m_ReCreateInstanceBuffer = true;
			return true;
		}
	}
	return false;
}

int RisingWater::GetInstanceCount() const
{
	return m_InstanceVec.size();
}

bool RisingWater::InitializeBuffers(ID3D10Device* device)
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
	size *= 15.0f;

	VertexType ver[8];
	ver[0].Position = D3DXVECTOR4(-size, size, -size, 1.0f);
	ver[0].TexCoords = D3DXVECTOR2(0, 1);
	ver[1].Position = D3DXVECTOR4(size, size, -size, 1.0f);
	ver[1].TexCoords = D3DXVECTOR2(1, 1);
	ver[2].Position = D3DXVECTOR4(-size, -size, -size, 1.0f);
	ver[2].TexCoords = D3DXVECTOR2(0, 0);
	ver[3].Position = D3DXVECTOR4(size, -size, -size, 1.0f);
	ver[3].TexCoords = D3DXVECTOR2(1, 0);
	ver[4].Position = D3DXVECTOR4(-size, size, size, 1.0f);
	ver[4].TexCoords = D3DXVECTOR2(1, 1);
	ver[5].Position = D3DXVECTOR4(size, size, size, 1.0f);
	ver[5].TexCoords = D3DXVECTOR2(0, 1);
	ver[6].Position = D3DXVECTOR4(-size, -size, size, 1.0f);
	ver[6].TexCoords = D3DXVECTOR2(1, 0);
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
		vertices[6] = ver[5];
		vertices[7] = ver[4];
		vertices[8] = ver[7];
		vertices[9] = ver[7];
		vertices[10] = ver[4];
		vertices[11] = ver[6];
		vertices[6].Normal = D3DXVECTOR3(0,0,1);
		vertices[7].Normal = D3DXVECTOR3(0,0,1);
		vertices[8].Normal = D3DXVECTOR3(0,0,1);
		vertices[9].Normal = D3DXVECTOR3(0,0,1);
		vertices[10].Normal = D3DXVECTOR3(0,0,1);
		vertices[11].Normal = D3DXVECTOR3(0,0,1);
		#pragma endregion back-plane

		#pragma region
		vertices[12] = ver[0];
		vertices[13] = ver[1];
		vertices[14] = ver[2];
		vertices[15] = ver[2];
		vertices[16] = ver[1];
		vertices[17] = ver[3];
		vertices[12].Normal = D3DXVECTOR3(0,0,-1);
		vertices[13].Normal = D3DXVECTOR3(0,0,-1);
		vertices[14].Normal = D3DXVECTOR3(0,0,-1);
		vertices[15].Normal = D3DXVECTOR3(0,0,-1);
		vertices[16].Normal = D3DXVECTOR3(0,0,-1);
		vertices[17].Normal = D3DXVECTOR3(0,0,-1);
		#pragma endregion front-plane

		#pragma region
		vertices[18] = ver[4];
		vertices[19] = ver[0];
		vertices[20] = ver[6];
		vertices[21] = ver[6];
		vertices[22] = ver[0];
		vertices[23] = ver[2];
		vertices[18].Normal = D3DXVECTOR3(-1,0,0);
		vertices[19].Normal = D3DXVECTOR3(-1,0,0);
		vertices[20].Normal = D3DXVECTOR3(-1,0,0);
		vertices[21].Normal = D3DXVECTOR3(-1,0,0);
		vertices[22].Normal = D3DXVECTOR3(-1,0,0);
		vertices[23].Normal = D3DXVECTOR3(-1,0,0);
		#pragma endregion left-plane

		#pragma region
		vertices[24] = ver[1];
		vertices[25] = ver[5];
		vertices[26] = ver[3];
		vertices[27] = ver[3];
		vertices[28] = ver[5];
		vertices[29] = ver[7];
		vertices[24].Normal = D3DXVECTOR3(1,0,0);
		vertices[25].Normal = D3DXVECTOR3(1,0,0);
		vertices[26].Normal = D3DXVECTOR3(1,0,0);
		vertices[27].Normal = D3DXVECTOR3(1,0,0);
		vertices[28].Normal = D3DXVECTOR3(1,0,0);
		vertices[29].Normal = D3DXVECTOR3(1,0,0);
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

	InitializeInstanceBuffer(device);
	// Release the instance array now that the instance buffer has been created and loaded.
	/*delete [] pInstances;
	pInstances = nullptr;*/

	return true;
}

void RisingWater::InitializeInstanceBuffer(ID3D10Device * pDevice)
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

void RisingWater::ReleaseBuffers()
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

void RisingWater::RenderBuffers(ID3D10Device* device)
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

void RisingWater::RenderShader(ID3D10Device* pDevice)
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

bool RisingWater::LoadTexture(ID3D10Device* device, const tstring & file)
{
	// Create the material object
	m_pMaterial = new InstancedWaterMaterial();
	if(m_pMaterial == nullptr)
	{
		return false;
	}

	// Initialize the material object
	m_pMaterial->Initialize();
	return true;
}


void RisingWater::ReleaseTexture()
{
	// Release the material object
	if(m_pMaterial != nullptr)
	{
		delete m_pMaterial;
		m_pMaterial = nullptr;
	}
}

void RisingWater::RandomizeWater()
{
	float size = GlobalParameters::GetParameters()->GetParameter<float>(_T("GRID_SIZE"));
	int randStart = rand() % m_InstanceVec.size();
	int randEnd = rand() % 200 + randStart;
	randEnd = min((int)m_InstanceVec.size() -1, randEnd);
	for(int i = randStart ; i < randEnd ; ++i)
	{
		float heightLevel(0);
		int randNumber = rand() % 100 - 50;
		heightLevel = randNumber * size * 0.0035f;
		m_InstanceVec[i].HeightLevel = heightLevel;
	}
}