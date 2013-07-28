#pragma once

//====================== #INCLUDES ===================================
#include "../Interfaces/IGeometryBatch.h"
//====================================================================

//====================== WorldInstancedObject Class =======================
// Description:
//		WorldInstancedObject class
// Last Modification: 05/06/2013
// Copyright Glen De Cauwsemaecker
// www.glendc.com
//====================================================================

class InstancedBlockMaterial;
//class ModelComponent;

class WorldInstancedObject : public IGeometryBatch
{
public:
	explicit WorldInstancedObject(int instance_amount = 0);
	virtual ~WorldInstancedObject(void);

	void Initialize();
	void Release();

	virtual void Draw(const GameContext & context);
	virtual void Update(const GameContext & context);

	virtual int AddInstance(const D3DXMATRIX & world, int instance_id);
	virtual int RemoveInstance(const D3DXMATRIX & world);
	virtual D3DXMATRIX RemoveInstance(int id);
	virtual unsigned int Commit(void);

private:
	static const int VERTEX_COUNT = 8;

	//Vertex information
	struct VertexInformation
	{
		D3DXVECTOR3 Position;
		D3DXVECTOR2 TexCoords;
		int ID;
	};

	//Instance information
	struct InstanceInformation
	{
		D3DXVECTOR3 Position;
		int ID;
	};

	std::vector<InstanceInformation> m_InstanceVector;
	
	ID3D10Buffer* m_pVertexBuffer;
	VertexInformation * m_Vertices;

	InstancedBlockMaterial* m_pMaterial;

	// Disabling default copy constructor and default assignment operator.
	WorldInstancedObject(const WorldInstancedObject& yRef);									
	WorldInstancedObject& operator=(const WorldInstancedObject& yRef);
};