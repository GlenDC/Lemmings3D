//================================================== INCLUDES =====================================
#include "SkyBox.h"
//-------------------------------------------------------------------------------------------------
#include "../Materials/SkyBoxMaterial.h"
#include "Graphics/GraphicsDevice.h"
#include "../Entities/Level.h"
//=================================================================================================
SkyBox::SkyBox(Level * pLevel, const D3DXVECTOR3 & pos, const tstring & cube_file)
	: m_pVertexBuffer(nullptr)
	, m_pIndexBuffer(nullptr)
	, m_VecVertices(VERTEX_COUNT)
	, m_VecIndices(INDEX_COUNT)
	, m_IndexCount(0)
	, m_TextureFile(cube_file)
	, m_pMaterial(nullptr)
	, m_pLevel(pLevel)
	, m_Position(pos)
{
	m_pMaterial = new SkyBoxMaterial();
	m_pMaterial->SetCubeMap(m_TextureFile);
	m_pMaterial->SetPosition( pos );
	m_pMaterial->Initialize();
}

SkyBox::~SkyBox(void)
{
	Release();
}

void SkyBox::Initialize()
{
	BuildShape();
	BuildVertexBuffer();
	BuildIndexBuffer();
}

void SkyBox::Release()
{
	SafeDelete(m_pMaterial);
	SafeRelease(m_pVertexBuffer);
	SafeRelease(m_pIndexBuffer);
}

void SkyBox::Draw(const GameContext & context)
{
	// Set vertex buffer(s)
	UINT offset = 0;
	UINT vertexBufferStride = sizeof(VertexPos);
	GraphicsDevice::GetInstance()->GetDevice()->IASetVertexBuffers( 0, 1, &m_pVertexBuffer, &vertexBufferStride, &offset );

	// Set index buffer
	GraphicsDevice::GetInstance()->GetDevice()->IASetIndexBuffer(m_pIndexBuffer,DXGI_FORMAT_R32_UINT,0);

	// Set primitive topology
	GraphicsDevice::GetInstance()->GetDevice()->IASetPrimitiveTopology( D3D10_PRIMITIVE_TOPOLOGY_TRIANGLELIST );

	m_pMaterial->SetPosition(m_pLevel->GetCenter());
	m_pMaterial->Update(context);

	// Set the input layout.
	ID3D10InputLayout * inputLayout = m_pMaterial->GetInputLayout();
	GraphicsDevice::GetInstance()->GetDevice()->IASetInputLayout(inputLayout);

	ID3D10EffectTechnique* pTechnique= m_pMaterial->GetDefaultTechnique();
	D3D10_TECHNIQUE_DESC techDesc;
	pTechnique->GetDesc( &techDesc );
	for( UINT p = 0; p < techDesc.Passes; ++p )
	{
		pTechnique->GetPassByIndex(p)->Apply(0);
		GraphicsDevice::GetInstance()->GetDevice()->DrawIndexed(INDEX_COUNT, 0, 0 ); 
	}
}

int SkyBox::GetVertexCount() const
{
	return VERTEX_COUNT;
}

void SkyBox::SetPosition(const D3DXVECTOR3 & pos)
{
	m_Position = pos;
	m_pMaterial->SetPosition(pos);
}

const D3DXVECTOR3 & SkyBox::GetPosition() const
{
	return m_Position;
}

void SkyBox::BuildShape()
{
	// (1)
	float radius = float(RADIUS);
	m_VecVertices[0] = VertexPos(-radius,-radius,-radius);
	m_VecVertices[1] = VertexPos(-radius, radius,-radius);
	m_VecVertices[2] = VertexPos( radius,-radius,-radius);
	m_VecVertices[3] = VertexPos( radius, radius,-radius);
	m_VecVertices[4] = VertexPos(-radius,-radius, radius);
	m_VecVertices[5] = VertexPos(-radius, radius, radius);
	m_VecVertices[6] = VertexPos( radius,-radius, radius);
	m_VecVertices[7] = VertexPos( radius, radius, radius);

	// (2)
	AddTriangle(1,5,3);	// top (0)
	AddTriangle(7,5,3); // top (1)
	AddTriangle(0,2,4);	// bottom (0)
	AddTriangle(4,2,6); // bottom (1)
	AddTriangle(1,5,4);	// left (0)
	AddTriangle(0,4,1); // left (1)
	AddTriangle(7,3,2);	// right (0)
	AddTriangle(7,2,6); // right (1)
	AddTriangle(5,7,4);	// front (0)
	AddTriangle(4,7,6); // front (1)
	AddTriangle(1,3,0);	// back (0)
	AddTriangle(0,3,2); // back (1)
}

void SkyBox::AddTriangle (UINT a, UINT b, UINT c)
{
	AddIndex(a);
	AddIndex(b);
	AddIndex(c);
}

void SkyBox::AddIndex(UINT index)
{
	m_VecIndices[m_IndexCount] = index;
	++m_IndexCount;
}

void SkyBox::BuildVertexBuffer()
{
	//fill a buffer description to copy the vertex data into graphics memory
	D3D10_BUFFER_DESC bufferDescriptor = {};
	bufferDescriptor.Usage = D3D10_USAGE_DEFAULT;
	bufferDescriptor.ByteWidth = sizeof( VertexPos ) * VERTEX_COUNT;
	bufferDescriptor.BindFlags = D3D10_BIND_VERTEX_BUFFER;
	bufferDescriptor.CPUAccessFlags = 0;
	bufferDescriptor.MiscFlags = 0;

	D3D10_SUBRESOURCE_DATA initData = {};
	initData.pSysMem = m_VecVertices.data();
	//create a ID3D10Buffer in graphics memory containing the vertex info
	ASSERT(GraphicsDevice::GetInstance()->GetDevice()->CreateBuffer( &bufferDescriptor, &initData, &m_pVertexBuffer ) == S_OK,
		_T("Couldn't create the vertex buffer of the CubeMap Object."));
}

void SkyBox::BuildIndexBuffer()
{
	D3D10_BUFFER_DESC bd = {};
	bd.Usage = D3D10_USAGE_IMMUTABLE;
	bd.ByteWidth = sizeof(DWORD) * m_VecIndices.size();
	bd.BindFlags = D3D10_BIND_INDEX_BUFFER;
	bd.CPUAccessFlags = 0;
	bd.MiscFlags = 0;
	D3D10_SUBRESOURCE_DATA initData = {};
	initData.pSysMem = m_VecIndices.data();
	ASSERT(GraphicsDevice::GetInstance()->GetDevice()->CreateBuffer(&bd, &initData, &m_pIndexBuffer) == S_OK,
		_T("Couldn't create the index buffer of the CubeMap Object."));
}

bool SkyBox::SetCubeMap(const tstring & file)
{
	m_pMaterial->SetCubeMap(file);
	return true;
}