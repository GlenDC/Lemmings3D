#pragma once
//====================== #INCLUDES ===================================
#include "ColissionEntity.h"
//====================================================================

//====================== KeyObject Class =============================
// Description:
//		KeyObject
// Last Modification: August 2013
// Glen De Cauwsemaecker
// www.glendc.com
//====================================================================

class RigidBodyComponent;
class PhysicsMaterial;
class BaseColliderComponent;

class KeyObject : public ColissionEntity
{
private:

public:
	KeyObject();
	virtual ~KeyObject();

	virtual void Initialize();
	virtual void Update(const GameContext & context);

private:
	static const int MODEL_ID = 1;
	D3DXVECTOR3 m_OriginalPosition;
	float m_Height, m_Rotation;
	int m_Direction;

	// Disabling default copy constructor and default assignment operator.
	KeyObject(const KeyObject& yRef);									
	KeyObject& operator=(const KeyObject& yRef);
};