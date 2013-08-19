#pragma once
//====================== #INCLUDES ===================================
#include "GameEntity.h"
#include "ColissionEntity.h"
//====================================================================

//====================== PortalEnter Class =============================
// Description:
//		Spawning position for Lemmings!
// Last Modification: August 2013
// Glen De Cauwsemaecker
// www.glendc.com
//====================================================================

class RigidBodyComponent;
class PhysicsMaterial;
class BaseColliderComponent;

class PortalEnter : public GameEntity
{
private:

public:
	PortalEnter();
	virtual ~PortalEnter();

	virtual void Initialize();
	virtual void Update(const GameContext & context);

private:
	static const int MODEL_ID = 6;
	bool m_CanSpawn;

	// Disabling default copy constructor and default assignment operator.
	PortalEnter(const PortalEnter& yRef);									
	PortalEnter& operator=(const PortalEnter& yRef);
};