//====================== #INCLUDES ===================================
#include "PhysicsCube.h"
//--------------------------------------------------------------------
#include "Components/Physics/BoxColliderComponent.h"
#include "Components/Physics/RigidBodyComponent.h"
#include "Components/TransformComponent.h"
//====================================================================

PhysicsCube::PhysicsCube(const D3DXVECTOR3 & pos, const float size)
	: GameObject()
	, m_pCollider(nullptr)
	, m_pRigidBody(nullptr)
	, m_Position(pos)
	, m_Size(size)
{
}

PhysicsCube::~PhysicsCube(void)
{
	RemoveComponent(m_pCollider);
	RemoveComponent(m_pRigidBody);
}
	
void PhysicsCube::Initialize()
{
	m_pRigidBody = new RigidBodyComponent();
	m_pRigidBody->AddConstraints(Constraints::DISABLE_GRAVITY | Constraints::FREEZE_POS_X | Constraints::FREEZE_POS_Y |
		Constraints::FREEZE_POS_Z | Constraints::FREEZE_ROT_X | Constraints::FREEZE_ROT_Y | Constraints::FREEZE_ROT_Z);
	AddComponent(m_pRigidBody);

	m_pCollider = new BoxColliderComponent(m_Size, m_Size, m_Size);

	PhysicsMaterial * pMaterial = new PhysicsMaterial();
	pMaterial->SetRestitution(0.7f);
	pMaterial->SetStaticFriction(0.5f);
	pMaterial->SetDynamicFriction(0.5f);

	m_pCollider->SetPhysicsMaterial(pMaterial);
	AddComponent(m_pCollider);

	auto transform = GetComponent<TransformComponent>();
	transform->Translate(m_Position);

	GameObject::Initialize();
}

void PhysicsCube::Update(const GameContext & context)
{
	GameObject::Update(context);
}

void PhysicsCube::Draw(const GameContext & context)
{
}