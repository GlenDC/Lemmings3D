#pragma once
//====================== #INCLUDES ===================================
#include "ColissionEntity.h"
#include "GameEntity.h"
//====================================================================

//====================== PortalExit Class =============================
// Description:
//		If A lemming object has reached this class, he is save and destroyed!
// Last Modification: August 2013
// Glen De Cauwsemaecker
// www.glendc.com
//====================================================================

class RigidBodyComponent;
class PhysicsMaterial;
class BaseColliderComponent;
class WarpMaterial;

class PortalExit : public ColissionEntity
{
private:

public:
	PortalExit();
	virtual ~PortalExit();

	virtual void Initialize();
	virtual void Update(const GameContext & context);

protected:
	virtual void InitializeRigidBody();

private:
	static const int MODEL_ID = 7;
	GameEntity * m_pWarp;
	WarpMaterial * m_pWarpMaterial;

	// Disabling default copy constructor and default assignment operator.
	PortalExit(const PortalExit& yRef);									
	PortalExit& operator=(const PortalExit& yRef);
};