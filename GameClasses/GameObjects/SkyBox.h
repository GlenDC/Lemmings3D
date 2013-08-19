#pragma once

//====================== #INCLUDES ===================================
#include "Helpers/stdafx.h"
#include "Helpers/D3DUtil.h"
#include "Helpers/GeneralStructs.h"
//====================================================================

//====================== SkyBox Class =======================
// Description:
//		SkyBox model object class (aka cube map)
// Last Modification: August 2013
// Glen De Cauwsemaecker
// www.glendc.com
//====================================================================

class SkyBoxMaterial;
class Level;

class SkyBox
{
public:
	SkyBox(Level * pLevel, const D3DXVECTOR3 & pos, const tstring & cube_file);
	virtual ~SkyBox(void);

	void Initialize();
	void Release();

	void Draw(const GameContext & context);

	int GetVertexCount() const;

	void SetPosition(const D3DXVECTOR3 & pos);
	const D3DXVECTOR3 & GetPosition() const;

private:
	//Vertex information
	struct VertexPos
	{
		VertexPos()
			: Position ()
		{
		}

		VertexPos(float x, float y, float z)
			: Position (x, y, z)
		{
		}

		D3DXVECTOR3 Position;
	};

	void BuildShape();
	void AddTriangle (UINT a, UINT b, UINT c);
	void AddIndex(UINT index);
	void BuildVertexBuffer();
	void BuildIndexBuffer();

	bool SetCubeMap(const tstring & file);

	ID3D10Buffer* m_pVertexBuffer;
	ID3D10Buffer* m_pIndexBuffer;

	vector<VertexPos> m_VecVertices;
	vector<DWORD> m_VecIndices;

	static const UINT	VERTEX_COUNT = 8,
						INDEX_COUNT = 36,
						RADIUS = 500;

	UINT m_IndexCount;

	tstring m_TextureFile;

	SkyBoxMaterial* m_pMaterial;

	Level * m_pLevel;

	D3DXVECTOR3 m_Position;

	// Disabling default copy constructor and default assignment operator.
	SkyBox(const SkyBox& yRef);									
	SkyBox& operator=(const SkyBox& yRef);
};