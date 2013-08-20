#pragma once
//====================== #INCLUDES ===================================
#include "GameEntity.h"
//====================================================================

//====================== KeyPickup Class =============================
// Description:
//		Visual Key, created after picking up a KeyPickup
// Last Modification: August 2013
// Glen De Cauwsemaecker
// www.glendc.com
//====================================================================

class RigidBodyComponent;
class PhysicsMaterial;
class BaseColliderComponent;

class KeyPickup : public GameEntity
{
private:

public:
	KeyPickup();
	virtual ~KeyPickup();

	virtual void Initialize();
	virtual void Update(const GameContext & context);

	void SetOwner(GameEntity * owner) { m_pOwner = owner; }

private:
	GameEntity * m_pOwner;
	static const int MODEL_ID = 1;
	D3DXVECTOR3 m_OriginalPosition;
	float m_Height, m_Rotation;
	int m_Direction;

	// Disabling default copy constructor and default assignment operator.
	KeyPickup(const KeyPickup& yRef);									
	KeyPickup& operator=(const KeyPickup& yRef);
};