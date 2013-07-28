#pragma once

//====================== #INCLUDES ===================================
#include "helpers/stdafx.h"
#include "helpers/d3dutil.h"
#include "helpers/generalstructs.h"
#include "Scenegraph/GameObject.h"
#include <memory>
//====================================================================

class BoxColliderComponent;
class RigidBodyComponent;

//====================== PhysicsCube Class =========================
// Description:
//		Material for the preview of objectss
// Last Modification: 08/06/2013
// Copyright Glen De Cauwsemaecker
// www.glendc.com
//====================================================================

class GameScreen;

class PhysicsCube : public GameObject
{
public:
	explicit PhysicsCube(const D3DXVECTOR3 & pos, float size);
	virtual ~PhysicsCube(void);

	virtual void Initialize();
	virtual void Update(const GameContext & context);
	virtual void Draw(const GameContext & context);

private:
	BoxColliderComponent * m_pCollider;
	RigidBodyComponent * m_pRigidBody;
	D3DXVECTOR3 m_Position;
	float m_Size;

	// -------------------------
	// Disabling default copy constructor and default 
	// assignment operator.
	// -------------------------
	PhysicsCube(const PhysicsCube& yRef);									
	PhysicsCube& operator=(const PhysicsCube& yRef);
};