#include "WorldInstancedObject.h"
#include "Graphics/GraphicsDevice.h"
#include <algorithm>
#include "../Lib/GlobalParameters.h"
#include "../Lib/LemmingsHelpers.h"
#include "../Materials/InstancedBlockMaterial.h"

#ifndef device 
#define device GraphicsDevice::GetInstance()->GetDevice() 
#endif

WorldInstancedObject::WorldInstancedObject(int instance_amount)
	: m_InstanceVector(instance_amount)
	, m_pVertexBuffer(nullptr)
	, m_Vertices(nullptr)
	, m_pMaterial(nullptr)
{
	m_pRenderContext = new RenderContext(_T("effect"));
}

WorldInstancedObject::~WorldInstancedObject(void)
{
	Release();
}

void WorldInstancedObject::Initialize()
{
	
	// Create the material object
	m_pMaterial = new InstancedBlockMaterial();

	// Initialize the material object
	m_pMaterial->Initialize();
}

void WorldInstancedObject::Release()
{
	delete m_pRenderContext;
	if(m_Vertices != nullptr)
	{
		delete [] m_Vertices;
	}
	
	delete m_pMaterial;
	m_pMaterial = nullptr;
}

void WorldInstancedObject::Draw(const GameContext & context)
{
	D3D10_TECHNIQUE_DESC techniqueDesc;
	unsigned int i;

	// Set the input layout.
	device->IASetInputLayout(m_pMaterial->GetInputLayout());

	// Get the description structure of the technique from inside the shader so it can be used for rendering.
	m_pMaterial->GetDefaultTechnique()->GetDesc(&techniqueDesc);

	// Go through each pass in the technique (should be just one currently) and render the triangles.
	for(i=0; i<techniqueDesc.Passes; ++i)
	{
		m_pMaterial->GetDefaultTechnique()->GetPassByIndex(i)->Apply(0);
	}
}

void WorldInstancedObject::Update(const GameContext & context)
{

}

unsigned int WorldInstancedObject::Commit(void)
{
	HRESULT result;

	if(m_Vertices != nullptr)
	{
		delete [] m_Vertices;
	}
	
	D3D10_BUFFER_DESC vertexBufferDesc;
	D3D10_SUBRESOURCE_DATA vertexData;

	// Set up the description of the vertex buffer.
	vertexBufferDesc.Usage = D3D10_USAGE_DEFAULT;
	int vertexCount = VERTEX_COUNT * m_InstanceVector.size();
	vertexBufferDesc.ByteWidth = sizeof(VertexInformation) * vertexCount;
	vertexBufferDesc.BindFlags = D3D10_BIND_VERTEX_BUFFER;
	vertexBufferDesc.CPUAccessFlags = 0;
	vertexBufferDesc.MiscFlags = 0;

	// Set Vertex Points
	VertexInformation vertices[VERTEX_COUNT];
	float size = GlobalParameters::GetParameters()->GetParameter<float>(_T("GRID_SIZE"));
	#pragma region
		// Vertex #0 
		vertices[0].ID = 0;
		vertices[0].Position = D3DXVECTOR3(-1, 1, 1);
		vertices[0].TexCoords = D3DXVECTOR2(0, 1);
		// Vertex #1 
		vertices[1].ID = 0;
		vertices[1].Position = D3DXVECTOR3(1, 1, 1);
		vertices[1].TexCoords = D3DXVECTOR2(1, 1);
		// Vertex #2 
		vertices[2].ID = 0;
		vertices[2].Position = D3DXVECTOR3(-1, 1, -1);
		vertices[2].TexCoords = D3DXVECTOR2(0, -1);
		// Vertex #3 
		vertices[3].ID = 0;
		vertices[3].Position = D3DXVECTOR3(1, 1, -1);
		vertices[3].TexCoords = D3DXVECTOR2(1, -1);
		// Vertex #4 
		vertices[4].ID = 0;
		vertices[4].Position = D3DXVECTOR3(-1, 1, 1);
		vertices[4].TexCoords = D3DXVECTOR2(0, 1);
		// Vertex #5
		vertices[5].ID = 0;
		vertices[5].Position = D3DXVECTOR3(1, 1, 1);
		vertices[5].TexCoords = D3DXVECTOR2(1, 1);
		// Vertex #6
		vertices[6].ID = 0;
		vertices[6].Position = D3DXVECTOR3(-1, 1, -1);
		vertices[6].TexCoords = D3DXVECTOR2(0, -1);
		// Vertex #7
		vertices[7].ID = 0;
		vertices[7].Position = D3DXVECTOR3(1, 1, -1);
		vertices[7].TexCoords = D3DXVECTOR2(1, -1);
	#pragma endregion Set up vertices...

	m_Vertices = new VertexInformation[vertexCount];
	for(int i = 0 ; i < vertexCount ; i += VERTEX_COUNT)
	{
		int instanceCount = i / VERTEX_COUNT;
		for(int u = 0 ; u < VERTEX_COUNT ; ++u)
		{
			m_Vertices[i+u] = vertices[u];
			m_Vertices[i+u].Position += m_InstanceVector[instanceCount].Position;
		}
	}
		
	// Give the subresource structure a pointer to the vertex data.
	vertexData.pSysMem = m_Vertices;
	
	// Now finally create the vertex buffer.
	result = device->CreateBuffer(&vertexBufferDesc, &vertexData, &m_pVertexBuffer);

	ASSERT(SUCCEEDED(result), _T("Couldn't create  the vertex buffer for the WorldInstancedObject!"));

	return (unsigned int)result;
}

int WorldInstancedObject::AddInstance(const D3DXMATRIX & world, int instance_id)
{
	InstanceInformation instance;
	D3DXVECTOR3 translation, scale;
	D3DXQUATERNION rotation;
	D3DXMatrixDecompose(&scale, &rotation, &translation, &world);
	instance.Position = translation;
	instance.ID = instance_id;
	m_InstanceVector.push_back(instance);
	return instance_id;
}

int WorldInstancedObject::RemoveInstance(const D3DXMATRIX & world)
{
	for(unsigned int i = 0 ; i < m_InstanceVector.size() ; ++i)
	{
		if(LemmingsHelpers::MatrixTranslation(m_InstanceVector[i].Position) == world)
		{
			int id = m_InstanceVector[i].ID;
			m_InstanceVector.erase(m_InstanceVector.begin() + i);
			return id;
		}
	}
	return -1;
}

D3DXMATRIX WorldInstancedObject::RemoveInstance(int id)
{
	for(unsigned int i = 0 ; i < m_InstanceVector.size() ; ++i)
	{
		if(m_InstanceVector[i].ID == id)
		{
			D3DXMATRIX world = LemmingsHelpers::MatrixTranslation(m_InstanceVector[i].Position);
			m_InstanceVector.erase(m_InstanceVector.begin() + i);
			return world;
		}
	}
	return D3DXMATRIX();
}