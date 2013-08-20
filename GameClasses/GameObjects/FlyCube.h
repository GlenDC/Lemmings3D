#pragma once
//====================== #INCLUDES ===================================
#include "ColissionEntity.h"
//====================================================================

//====================== FlyCube Class =============================
// Description:
//		A flying cube for demo purposes 
// Last Modification: August 2013
// Glen De Cauwsemaecker
// www.glendc.com
//====================================================================

class RigidBodyComponent;
class PhysicsMaterial;
class BaseColliderComponent;

class FlyCube : public ColissionEntity
{
public:
	FlyCube();
	virtual ~FlyCube();

	void ShootCube(const D3DXVECTOR3 & pos, const D3DXVECTOR3 & direction);

protected:
	const static float SPEED;

private:
	// Disabling default copy constructor and default assignment operator.
	FlyCube(const FlyCube& yRef);									
	FlyCube& operator=(const FlyCube& yRef);
};