#include "PreviewObject.h"
#include "Graphics/GraphicsDevice.h"
#include "../Materials/PreviewMaterial.h"
#include "OverlordComponents.h"
#include "../Lib/LemmingsHelpers.h"
#include "../Lib/GlobalParameters.h"
#include "Managers/ContentManager.h"

PreviewObject::PreviewObject(void)
	: m_pVertexBuffer(nullptr)
	, m_pIndexBuffer(nullptr)
	, m_TextureFile(_T(""))
	, m_pMaterial(nullptr)
	, m_Position()
{

}

PreviewObject::~PreviewObject()
{
	Release();
}

void PreviewObject::Initialize()
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

void PreviewObject::Release()
{
	// Release the model texture.
	ReleaseTexture();

	// Release the vertex and instance buffers.
	ReleaseBuffers();
}

void PreviewObject::Draw(const GameContext & context)
{
	// Put the vertex and instance buffers on the graphics pipeline to prepare them for drawing.
	RenderBuffers(GraphicsDevice::GetInstance()->GetDevice());
	m_pMaterial->SetPosition(m_Position);
	m_pMaterial->SetEffectVariables(context, nullptr);
	RenderShader(GraphicsDevice::GetInstance()->GetDevice());
}

void PreviewObject::Update(const GameContext & context)
{
}

int PreviewObject::GetVertexCount() const
{
	return VERTEX_COUNT;
}

void PreviewObject::SetPosition(const D3DXVECTOR3 & pos)
{
	m_Position = pos;
}

const D3DXVECTOR3 & PreviewObject::GetPosition() const
{
	return m_Position;
}

ID3D10ShaderResourceView* PreviewObject::GetTexture() const
{
	return m_pMaterial->GetTexture();
}

//bool PreviewObject::InitializeBuffers(ID3D10Device* device)
//{
//	BuildShape();
//	BuildVertexBuffer();
//	BuildIndexBuffer();
//	return true;
//}

//void PreviewObject::ReleaseBuffers()
//{
//	// Release the new index buffer in the ShutdownBuffers function.
//	// Release the instance buffer.
//	if(m_pIndexBuffer)
//	{
//		m_pIndexBuffer->Release();
//		m_pIndexBuffer = nullptr;
//	}
//
//	// Release the vertex buffer.
//	if(m_pVertexBuffer)
//	{
//		m_pVertexBuffer->Release();
//		m_pVertexBuffer = nullptr;
//	}
//
//	return;
//}


bool PreviewObject::InitializeBuffers(ID3D10Device * pDevice)
{
	//VertexType* pVertices;
	//D3D10_BUFFER_DESC vertexBufferDesc, instanceBufferDesc;
//	D3D10_BUFFER_DESC instanceBufferDesc;
	//D3D10_SUBRESOURCE_DATA vertexData, instanceData;
	//D3D10_SUBRESOURCE_DATA instanceData;
	HRESULT result;
	
	D3D10_BUFFER_DESC vertexBufferDesc;
	D3D10_SUBRESOURCE_DATA vertexData;

	// Set up the description of the vertex buffer.
	vertexBufferDesc.Usage = D3D10_USAGE_DEFAULT;
	vertexBufferDesc.ByteWidth = sizeof(VertexPosNormTex) * GetVertexCount();
	vertexBufferDesc.BindFlags = D3D10_BIND_VERTEX_BUFFER;
	vertexBufferDesc.CPUAccessFlags = 0;
	vertexBufferDesc.MiscFlags = 0;
	
	float size = GlobalParameters::GetParameters()->GetParameter<float>(_T("GRID_SIZE"));
	size *= 0.5f;
	//size *= 66.0f;

	VertexPosNormTex ver[8];
	ver[0].Position = D3DXVECTOR3(-size, size, -size);
	ver[0].TexCoords = D3DXVECTOR2(0, 1);
	ver[1].Position = D3DXVECTOR3(size, size, -size);
	ver[1].TexCoords = D3DXVECTOR2(1, 1);
	ver[2].Position = D3DXVECTOR3(-size, -size, -size);
	ver[2].TexCoords = D3DXVECTOR2(0, 0);
	ver[3].Position = D3DXVECTOR3(size, -size, -size);
	ver[3].TexCoords = D3DXVECTOR2(1, 0);
	ver[4].Position = D3DXVECTOR3(-size, size, size);
	ver[4].TexCoords = D3DXVECTOR2(1, 1);
	ver[5].Position = D3DXVECTOR3(size, size, size);
	ver[5].TexCoords = D3DXVECTOR2(0, 1);
	ver[6].Position = D3DXVECTOR3(-size, -size, size);
	ver[6].TexCoords = D3DXVECTOR2(1, 0);
	ver[7].Position = D3DXVECTOR3(size, -size, size);
	ver[7].TexCoords = D3DXVECTOR2(0, 0);

	// Set Vertex Points
	VertexPosNormTex vertices[VERTEX_COUNT];
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

	// Now finally create the vertex buffer.
	result = pDevice->CreateBuffer(&vertexBufferDesc, &vertexData, &m_pVertexBuffer);
	ASSERT(SUCCEEDED(result), _T("Couldn't create the Vertex buffer!"));
	return true;
}

void PreviewObject::ReleaseBuffers()
{
	// Release the vertex buffer.
	if(m_pVertexBuffer)
	{
		m_pVertexBuffer->Release();
		m_pVertexBuffer = nullptr;
	}

	return;
}

void PreviewObject::RenderBuffers(ID3D10Device* pDevice)
{
	UINT stride = sizeof(VertexPosNormTex);
	UINT offset = 0;
	// Set the vertex and instance buffers to active in the input assembler so it can be rendered.
	pDevice->IASetVertexBuffers(0, 1, &m_pVertexBuffer, &stride, &offset);

	// Set the type of primitive that should be rendered from this vertex buffer, in this case triangles.
	pDevice->IASetPrimitiveTopology(D3D10_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
}

ID3D10Buffer* m_pVertexBuffer;

//void PreviewObject::BuildShape()
//{
//	float size = GlobalParameters::GetParameters()->GetParameter<float>(_T("GRID_SIZE")) * 2;
//
//#pragma region
//	//front 
//	VertexPosNormTex v(D3DXVECTOR3(-size/2,  -size/2, -size/2),D3DXVECTOR3(0,  -0, -1),D3DXVECTOR2(0,1));//lB
//	m_VecVertices.push_back(v);
//	v=VertexPosNormTex(D3DXVECTOR3(-size/2,   size/2, -size/2),D3DXVECTOR3(-0,  -0, -1),D3DXVECTOR2(0,0));//LT
//	m_VecVertices.push_back(v);
//	v=VertexPosNormTex(D3DXVECTOR3( size/2,  -size/2, -size/2),D3DXVECTOR3(-0,  -0, -1),D3DXVECTOR2(1,1));//RB
//	m_VecVertices.push_back(v);
//	v=VertexPosNormTex(D3DXVECTOR3( size/2,   size/2, -size/2),D3DXVECTOR3(-0,  -0, -1),D3DXVECTOR2(1,0));//RT
//	m_VecVertices.push_back(v);
//	//back 
//	v=VertexPosNormTex(D3DXVECTOR3(-size/2, -size/2, size/2),D3DXVECTOR3(0,  0, 1),D3DXVECTOR2(1,1));
//	m_VecVertices.push_back(v);
//	v=VertexPosNormTex(D3DXVECTOR3(-size/2,  size/2, size/2),D3DXVECTOR3(0,  0, 1),D3DXVECTOR2(1,0));
//	m_VecVertices.push_back(v);
//	v=VertexPosNormTex(D3DXVECTOR3( size/2, -size/2, size/2),D3DXVECTOR3(0,  0, 1),D3DXVECTOR2(0,1));
//	m_VecVertices.push_back(v);
//	v=VertexPosNormTex(D3DXVECTOR3( size/2,  size/2, size/2),D3DXVECTOR3(0,  0, 1),D3DXVECTOR2(0,0));
//	m_VecVertices.push_back(v);
//
//	//left 
//	v=VertexPosNormTex(D3DXVECTOR3(-size/2, -size/2, -size/2),D3DXVECTOR3(-1,  0, 0),D3DXVECTOR2(1,1));
//	m_VecVertices.push_back(v);
//	v=VertexPosNormTex(D3DXVECTOR3(-size/2,  size/2, -size/2),D3DXVECTOR3(-1,  0, 0),D3DXVECTOR2(1,0));
//	m_VecVertices.push_back(v);
//	v=VertexPosNormTex(D3DXVECTOR3(-size/2, -size/2,  size/2),D3DXVECTOR3(-1,  0, 0),D3DXVECTOR2(0,1));
//	m_VecVertices.push_back(v);
//	v=VertexPosNormTex(D3DXVECTOR3(-size/2,  size/2,  size/2),D3DXVECTOR3(-1,  0, 0),D3DXVECTOR2(0,0));
//	m_VecVertices.push_back(v);
//
//	//right 
//	v=VertexPosNormTex(D3DXVECTOR3(size/2, -size/2, -size/2),D3DXVECTOR3(1,  0, 0),D3DXVECTOR2(0,1));
//	m_VecVertices.push_back(v);
//	v=VertexPosNormTex(D3DXVECTOR3(size/2,  size/2, -size/2),D3DXVECTOR3(1,  0, 0),D3DXVECTOR2(0,0));
//	m_VecVertices.push_back(v);
//	v=VertexPosNormTex(D3DXVECTOR3(size/2, -size/2,  size/2),D3DXVECTOR3(1,  0, 0),D3DXVECTOR2(1,1));
//	m_VecVertices.push_back(v);
//	v=VertexPosNormTex(D3DXVECTOR3(size/2,  size/2,  size/2),D3DXVECTOR3(1,  0, 0),D3DXVECTOR2(1,0));
//	m_VecVertices.push_back(v);
//
//	//top 
//	v=VertexPosNormTex(D3DXVECTOR3(-size/2,  size/2,  size/2),D3DXVECTOR3(0,  1, 0),D3DXVECTOR2(1,1));
//	m_VecVertices.push_back(v);
//	v=VertexPosNormTex(D3DXVECTOR3(-size/2,  size/2, -size/2),D3DXVECTOR3(0,  1, 0),D3DXVECTOR2(1,0));
//	m_VecVertices.push_back(v);
//	v=VertexPosNormTex(D3DXVECTOR3(size/2,  size/2,   size/2),D3DXVECTOR3(0,  1, 0),D3DXVECTOR2(0,1));
//	m_VecVertices.push_back(v);
//	v=VertexPosNormTex(D3DXVECTOR3(size/2,  size/2,  -size/2),D3DXVECTOR3(0,  1, 0),D3DXVECTOR2(0,0));
//	m_VecVertices.push_back(v);
//
//	//bottom 
//	v=VertexPosNormTex(D3DXVECTOR3(-size/2,  -size/2,  size/2), D3DXVECTOR3(0,  -1, 0),D3DXVECTOR2(0,1));
//	m_VecVertices.push_back(v);
//	v=VertexPosNormTex(D3DXVECTOR3(-size/2,  -size/2, -size/2), D3DXVECTOR3(0,  -1, 0),D3DXVECTOR2(0,0));
//	m_VecVertices.push_back(v);
//	v=VertexPosNormTex(D3DXVECTOR3( size/2,  -size/2,  size/2), D3DXVECTOR3(0,  -1, 0),D3DXVECTOR2(1,1));
//	m_VecVertices.push_back(v);
//	v=VertexPosNormTex(D3DXVECTOR3( size/2,  -size/2, -size/2), D3DXVECTOR3(0,  -1, 0),D3DXVECTOR2(1,0));
//	m_VecVertices.push_back(v);
//#pragma endregion add vertices
//
//#pragma region
//	//front
//	AddTriangle(0,1,2);
//	AddTriangle(2,1,3);
//	//back
//	AddTriangle(4,6,5);
//	AddTriangle(5,6,7);
//	//left
//	AddTriangle(8,10,9);
//	AddTriangle(9,10,11);
//	//right
//	AddTriangle(12,13,14);
//	AddTriangle(14,13,15);
//	//top
//	AddTriangle(16,18,17);
//	AddTriangle(17,18,19);
//	//bottom
//	AddTriangle(20,21,22);
//	AddTriangle(22,21,23);
//#pragma endregion add triangles (indeces)
//}
//
//void PreviewObject::AddTriangle(UINT a, UINT b, UINT c)
//{
//	m_VecIndices.push_back(a);
//	m_VecIndices.push_back(b);
//	m_VecIndices.push_back(c);
//}
//
//void PreviewObject::BuildVertexBuffer()
//{
//	//fill a buffer description to copy the vertexdata into graphics memory
//	D3D10_BUFFER_DESC bd = {};
//	bd.Usage = D3D10_USAGE_DEFAULT;
//	bd.ByteWidth = sizeof( VertexPosNormTex ) * m_VecVertices.size();
//	bd.BindFlags = D3D10_BIND_VERTEX_BUFFER;
//	bd.CPUAccessFlags = 0;
//	bd.MiscFlags = 0;
//
//	D3D10_SUBRESOURCE_DATA initData;
//	initData.pSysMem = &m_VecVertices[0];
//	//create a ID3D10Buffer in graphics memory containing the vertex info
//	HRESULT result = GraphicsDevice::GetInstance()->GetDevice()->CreateBuffer( &bd, &initData, &m_pVertexBuffer);
//	ASSERT(SUCCEEDED(result), _T("Couldn't create the vertex buffer."));
//}
//
//void PreviewObject::BuildIndexBuffer()
//{
//	D3D10_BUFFER_DESC bd = {};
//    bd.Usage = D3D10_USAGE_IMMUTABLE;
//    bd.ByteWidth = sizeof(DWORD) * m_VecIndices.size();
//    bd.BindFlags = D3D10_BIND_INDEX_BUFFER;
//    bd.CPUAccessFlags = 0;
//    bd.MiscFlags = 0;
//    D3D10_SUBRESOURCE_DATA initData;
//	initData.pSysMem = &m_VecIndices[0];
//    HRESULT result = GraphicsDevice::GetInstance()->GetDevice()->CreateBuffer(&bd, &initData, &m_pIndexBuffer);
//	ASSERT(SUCCEEDED(result), _T("Couldn't create the vertex buffer."));
//}

//void PreviewObject::RenderBuffers(ID3D10Device* device)
//{
//	// Set vertex buffer
//    UINT offset = 0;
//	UINT vertexBufferStride = sizeof(VertexPosNormTex);
//    GraphicsDevice::GetInstance()->GetDevice()->IASetVertexBuffers( 0, 1, &m_pVertexBuffer, &vertexBufferStride, &offset );
//   	
//	// Set index buffer
//	GraphicsDevice::GetInstance()->GetDevice()->IASetIndexBuffer(m_pIndexBuffer,DXGI_FORMAT_R32_UINT,0);
//}

void PreviewObject::RenderShader(ID3D10Device* pDevice)
{
	D3D10_TECHNIQUE_DESC techniqueDesc;
	unsigned int i;

	// Set the input layout.
	ID3D10InputLayout * inputLayout = m_pMaterial->GetInputLayout();
	pDevice->IASetInputLayout(inputLayout);

	// Get the description structure of the technique from inside the shader so it can be used for rendering.
	m_pMaterial->GetDefaultTechnique()->GetDesc(&techniqueDesc);

	for(i=0; i<techniqueDesc.Passes; ++i)
    {
		m_pMaterial->GetDefaultTechnique()->GetPassByIndex(i)->Apply(0);
		pDevice->Draw(VERTEX_COUNT, 0);
    }
}

bool PreviewObject::LoadTexture(ID3D10Device* device, const tstring & file)
{
	// Create the material object
	m_pMaterial = new PreviewMaterial();
	if(m_pMaterial == nullptr)
	{
		return false;
	}

	// Initialize the material object
	m_pMaterial->Initialize();
	return true;
}


void PreviewObject::ReleaseTexture()
{
	// Release the material object
	if(m_pMaterial != nullptr)
	{
		delete m_pMaterial;
		m_pMaterial = nullptr;
	}
}