//===================================== INCLUDES ==============================
#include "FlyCube.h"
#include "OverlordComponents.h"
//=============================================================================

const float FlyCube::SPEED = 2000.0f;

FlyCube::FlyCube()
	: ColissionEntity()
{

}

FlyCube::~FlyCube()
{

}

void FlyCube::ShootCube(const D3DXVECTOR3 & pos, const D3DXVECTOR3 & direction)
{
	NxVec3 dir(direction.x, direction.y, direction.z);
	m_pRigidBody->SetLinearVelocity(dir * SPEED);
	Translate(pos);
}