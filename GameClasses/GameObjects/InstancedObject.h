#pragma once

//define LEVEL_VALIDATION to validate the level!
#define LEVEL_VALIDATION

//====================== #INCLUDES ===================================
#include "Helpers/stdafx.h"
#include "Helpers/D3DUtil.h"
#include "Helpers/GeneralStructs.h"
//====================================================================

//====================== InstancedObject Class =======================
// Description:
//		InstancedObject class
// Last Modification: 30/05/2013
// Copyright Glen De Cauwsemaecker
// www.glendc.com
//====================================================================

class InstancedBlockMaterial;
class ModelComponent;

struct InstanceType
{
	D3DXVECTOR3 Position;
	int ID;
};

class InstancedObject
{
public:
	explicit InstancedObject(const tstring & textureFile);
	virtual ~InstancedObject(void);

	void Initialize();
	void Release();

	void Draw(const GameContext & context);
	void Update(const GameContext & context);

	bool AddInstance(const D3DXVECTOR3 & position, int id);
	bool RemoveInstance(const D3DXVECTOR3 & position);
	bool EditInstance(const D3DXVECTOR3 & position, int id);

	void RecheckCubes(std::vector<InstanceType> & vec);

	int GetVertexCount() const;
	int GetInstanceCount() const;
	ID3D10ShaderResourceView* GetTexture() const;

	D3DXVECTOR3 GetClosestPosition(const D3DXVECTOR3 & pos);
	void ParsePositionVector(std::vector<D3DXVECTOR3> & posVec) const;
	const std::vector<D3DXVECTOR3> & GetPositions() const { return m_InstancePositionVec; }
	const std::vector<InstanceType> & GetInstances() const { return m_InstanceVec; }

private:

	//Vertex information
	struct VertexType
	{
		D3DXVECTOR4 Position;
		D3DXVECTOR3 Normal;
		D3DXVECTOR2 TexCoords;
	};

	//Instance information

	static const int VERTEX_COUNT = 36;

	std::vector<InstanceType> m_InstanceVec;
	std::vector<D3DXVECTOR3> m_InstancePositionVec;

	bool InitializeBuffers(ID3D10Device * pDevice);
	void InitializeInstanceBuffer(ID3D10Device * pDevice);
	void ReleaseBuffers();
	void RenderBuffers(ID3D10Device* pDevice);
	void RenderShader(ID3D10Device* pDevice);

	bool LoadTexture(ID3D10Device* pDevice, const tstring & file);
	void ReleaseTexture();

	ID3D10Buffer* m_pVertexBuffer;
	ID3D10Buffer* m_pInstanceBuffer;

	tstring m_TextureFile;

	bool m_ReCreateInstanceBuffer;

	InstancedBlockMaterial* m_pMaterial;
	ModelComponent * m_pInstancedObject;

	// Disabling default copy constructor and default assignment operator.
	InstancedObject(const InstancedObject& yRef);									
	InstancedObject& operator=(const InstancedObject& yRef);
};