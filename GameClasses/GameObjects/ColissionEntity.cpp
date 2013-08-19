//====================== #INCLUDES ===================================
#include "ColissionEntity.h"
//--------------------------------------------------------------------
#include "Components/Physics/PhysicsComponents.h"
#include "OverlordComponents.h"
//--------------------------------------------------------------------
#include "../GameScenes/BaseScreen.h"
//====================================================================

ColissionEntity::ColissionEntity(Material * material)
	: GameEntity(material)
	, m_pPhysicsMaterial(nullptr)
	, m_pRigidBody(nullptr)
	, m_ColliderComponents(0)
	, m_IsStatic(false)
	, m_CollectionRange(50)
{

}

ColissionEntity::ColissionEntity(MaterialType material)
	: GameEntity(material)
	, m_pPhysicsMaterial(nullptr)
	, m_pRigidBody(nullptr)
	, m_ColliderComponents(0)
	, m_IsStatic(false)
	, m_CollectionRange(50)
{

}

ColissionEntity::ColissionEntity(const tstring & visualModelPath, MaterialType material)
	: GameEntity(visualModelPath, material)
	, m_pPhysicsMaterial(nullptr)
	, m_pRigidBody(nullptr)
	, m_ColliderComponents(0)
	, m_IsStatic(false)
	, m_CollectionRange(50)
{

}

ColissionEntity::ColissionEntity(const tstring & visualModelPath, Material * material)
	: GameEntity(visualModelPath, material)
	, m_pPhysicsMaterial(nullptr)
	, m_pRigidBody(nullptr)
	, m_ColliderComponents(0)
	, m_IsStatic(false)
	, m_CollectionRange(50)
{

}

ColissionEntity::~ColissionEntity() //Default Destructor
{
	SafeDelete(m_pPhysicsMaterial);
	if(!m_IsEnabled)
	{
		for( UINT i = 0 ; i < m_ColliderComponents.size() ; ++i )
		{
			SafeDelete(m_ColliderComponents[i]);
		}
	}
	m_ColliderComponents.clear();
}

void ColissionEntity::Initialize()
{
	m_pRigidBody = new RigidBodyComponent();
	AddComponent(m_pRigidBody);

	if(m_pPhysicsMaterial == nullptr)
		m_pPhysicsMaterial = new PhysicsMaterial();
	
	if(m_ColliderComponents.size() == 0)
	{
		auto boxCollider = new BoxColliderComponent();
		m_ColliderComponents.push_back(boxCollider);
		boxCollider->SetPhysicsMaterial(m_pPhysicsMaterial);
		if(m_IsEnabled)
		{
			AddComponent(boxCollider);	
		}
	}
	else if(m_IsEnabled)
	{
		for(auto it : m_ColliderComponents)
		{
			AddComponent(it);
		}
	}

	GameEntity::Initialize();
}

void ColissionEntity::Enable()
{
	if(!m_IsEnabled)
	{
		for( UINT i = 0 ; i < m_ColliderComponents.size() ; ++i )
		{
			AddComponent(m_ColliderComponents[i]);
		}
		Initialize();
	}
	GameEntity::Enable();
}

void ColissionEntity::Disable()
{
	if(!m_IsEnabled)
	{
		for( UINT i = 0 ; i < m_ColliderComponents.size() ; ++i )
		{
			RemoveComponent(m_ColliderComponents[i]);
		}
	}
	GameEntity::Disable();
}

void ColissionEntity::SetIsStatic(bool is_static)
{
	m_IsStatic = is_static;
	m_pRigidBody->SetStatic(is_static);
	if(m_IsStatic)
	{
		m_pRigidBody->AddConstraints(Constraints::DISABLE_GRAVITY | Constraints::FREEZE_POS_X | Constraints::FREEZE_POS_Y |
			Constraints::FREEZE_POS_Z | Constraints::FREEZE_ROT_X | Constraints::FREEZE_ROT_Y | Constraints::FREEZE_ROT_Z);
	}
	else
	{
		m_pRigidBody->RemoveConstraints(Constraints::DISABLE_GRAVITY | Constraints::FREEZE_POS_X | Constraints::FREEZE_POS_Y |
			Constraints::FREEZE_POS_Z | Constraints::FREEZE_ROT_X | Constraints::FREEZE_ROT_Y | Constraints::FREEZE_ROT_Z);
	}
}

bool ColissionEntity::IsStatic() const
{
	return m_IsStatic;
}

void ColissionEntity::SetPhysicsMaterial(float restituation, NxCombineMode restituationCombineMode,
	float dynamicFriction, float staticFriction, NxCombineMode frictionCombineMode)
{
	if(m_pPhysicsMaterial == nullptr)
		m_pPhysicsMaterial = new PhysicsMaterial();
	m_pPhysicsMaterial->SetRestitution(restituation);
	m_pPhysicsMaterial->SetRestitutionCombineMode(restituationCombineMode);
	m_pPhysicsMaterial->SetDynamicFriction(dynamicFriction);
	m_pPhysicsMaterial->SetStaticFriction(staticFriction);
	m_pPhysicsMaterial->SetFrictionCombineMode(frictionCombineMode);
}

void ColissionEntity::AddBoxCollider(float width, float height, 
									 float depth, bool useMaterial)
{
	auto boxCollider = new BoxColliderComponent(width, height, depth);
	if(useMaterial)
		boxCollider->SetPhysicsMaterial(m_pPhysicsMaterial);
	m_ColliderComponents.push_back(boxCollider);
}

void ColissionEntity::AddMeshCollider(const tstring & path, bool isConvex, 
									  bool useMaterial)
{
	auto meshCollider = new MeshColliderComponent(path, isConvex);
	if(useMaterial)
		meshCollider->SetPhysicsMaterial(m_pPhysicsMaterial);
	m_ColliderComponents.push_back(meshCollider);
}

void ColissionEntity::AddSphereCollider(float radius, bool useMaterial)
{
	auto sphereCollider = new SphereColliderComponent(radius);
	if(useMaterial)
		sphereCollider->SetPhysicsMaterial(m_pPhysicsMaterial);
	m_ColliderComponents.push_back(sphereCollider);
}

void ColissionEntity::AddPlaneCollider(float distance, const NxVec3 & normal, 
									   bool useMaterial)
{
	auto planeCollider = new PlaneColliderComponent(distance, normal);
	if(useMaterial)
		planeCollider->SetPhysicsMaterial(m_pPhysicsMaterial);
	m_ColliderComponents.push_back(planeCollider);
}

void ColissionEntity::AddCapsuleCollider(float height, float radius, 
										 bool useMaterial)
{
	auto capsuleCollider = new CapsuleColliderComponent(height, radius);
	if(useMaterial)
		capsuleCollider->SetPhysicsMaterial(m_pPhysicsMaterial);
	m_ColliderComponents.push_back(capsuleCollider);
}