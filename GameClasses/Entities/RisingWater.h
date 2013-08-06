#pragma once

//====================== #INCLUDES ===================================
#include "Helpers/stdafx.h"
#include "Helpers/D3DUtil.h"
#include "Helpers/GeneralStructs.h"
#include "Graphics/SpriteBatch.h"
//====================================================================

class InstancedWaterMaterial;

//====================== RisingWater Class =======================
// Description:
//		RisingWater class represents the water rising in the level!
// Last Modification: July 2013
// Glen De Cauwsemaecker
// www.glendc.com
//====================================================================

class RisingWater
{
public:
	explicit RisingWater (const float minDepth, const float maxDepth);
	virtual ~RisingWater();

	void Initialize();
	void Release();

	void Update(const GameContext & context);
	void Draw(const GameContext & context);
	void Draw2D(const GameContext & context);

	bool AddInstance(const D3DXVECTOR3 & position);
	bool RemoveInstance(const D3DXVECTOR3 & position);

	int GetVertexCount() const;
	int GetInstanceCount() const;

private:
	//Vertex information
	struct VertexType
	{
		D3DXVECTOR4 Position;
		D3DXVECTOR3 Normal;
		D3DXVECTOR2 TexCoords;
	};

	//Instance information
	struct InstanceType
	{
		D3DXVECTOR3 Position;
		float HeightLevel;
	};

	static const int VERTEX_COUNT = 30;
	static const int WATER_LEVEL_RISE_SPEED = 1;

	std::vector<InstanceType> m_InstanceVec;

	float m_WaterLevel;
	float m_WaterRange;

	bool m_RefreshWater;

	bool InitializeBuffers(ID3D10Device * pDevice);
	void InitializeInstanceBuffer(ID3D10Device * pDevice);
	void ReleaseBuffers();
	void RenderBuffers(ID3D10Device* pDevice);
	void RenderShader(ID3D10Device* pDevice);

	bool LoadTexture(ID3D10Device* pDevice, const tstring & file);
	void ReleaseTexture();

	void RandomizeWater();

	ID3D10Buffer* m_pVertexBuffer;
	ID3D10Buffer* m_pInstanceBuffer;

	tstring m_TextureFile;

	bool m_ReCreateInstanceBuffer;

	ID3D10ShaderResourceView *m_pWaterLevelTexture;
	SpriteInfo m_WaterSprite;

	InstancedWaterMaterial* m_pMaterial;

	// Disabling default copy constructor and default assignment operator.
	RisingWater(const RisingWater& yRef);									
	RisingWater& operator=(const RisingWater& yRef);
};