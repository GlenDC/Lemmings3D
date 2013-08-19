#pragma once
//====================== #INCLUDES ===================================
#include "ColissionEntity.h"
//====================================================================

//====================== Lemming Class =============================
// Description:
//		Lemming (Character) Object
// Last Modification: August 2013
// Glen De Cauwsemaecker
// www.glendc.com
//====================================================================

class RigidBodyComponent;
class PhysicsMaterial;
class BaseColliderComponent;

class Lemming : public ColissionEntity
{
private:

public:
	explicit Lemming(const tstring & diff_texture);
	virtual ~Lemming();

	virtual void Initialize();
	virtual void Update(const GameContext & context);

private:

	// Disabling default copy constructor and default assignment operator.
	Lemming(const Lemming& yRef);									
	Lemming& operator=(const Lemming& yRef);
};