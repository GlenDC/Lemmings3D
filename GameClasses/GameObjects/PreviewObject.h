#pragma once

//====================== #INCLUDES ===================================
#include "Helpers/stdafx.h"
#include "Helpers/D3DUtil.h"
#include "Helpers/GeneralStructs.h"
//====================================================================

//====================== PreviewObject Class =======================
// Description:
//		PreviewObjects used in editor Mode!
// Last Modification: 08/06/2013
// Copyright Glen De Cauwsemaecker
// www.glendc.com
//====================================================================

class PreviewMaterial;

class PreviewObject
{
public:
	PreviewObject(void);
	virtual ~PreviewObject(void);

	void Initialize();
	void Release();

	void Draw(const GameContext & context);
	void Update(const GameContext & context);

	int GetVertexCount() const;
	ID3D10ShaderResourceView* GetTexture() const;

	void SetPosition(const D3DXVECTOR3 & pos);
	const D3DXVECTOR3 & GetPosition() const;

private:

	//Vertex information
	struct VertexPosNormTex
	{
		D3DXVECTOR3 Position;
		D3DXVECTOR3 Normal;
		D3DXVECTOR2 TexCoords;
	};

	static const int VERTEX_COUNT = 36;

	bool InitializeBuffers(ID3D10Device * pDevice);
	void ReleaseBuffers();

	void BuildShape();
	void AddTriangle(UINT a, UINT b, UINT c);
	void BuildVertexBuffer();
	void BuildIndexBuffer();

	void RenderBuffers(ID3D10Device* pDevice);
	void RenderShader(ID3D10Device* pDevice);

	bool LoadTexture(ID3D10Device* pDevice, const tstring & file);
	void ReleaseTexture();

	ID3D10Buffer* m_pVertexBuffer;
	ID3D10Buffer* m_pIndexBuffer;

	vector<VertexPosNormTex> m_VecVertices;
	vector<UINT> m_VecIndices;

	tstring m_TextureFile;

	PreviewMaterial* m_pMaterial;

	D3DXVECTOR3 m_Position;

	// Disabling default copy constructor and default assignment operator.
	PreviewObject(const PreviewObject& yRef);									
	PreviewObject& operator=(const PreviewObject& yRef);
};