//--------------------------------------------------------------------------------------
//   _____     _______ ____  _     ___  ____  ____    _____ _   _  ____ ___ _   _ _____ 
//  / _ \ \   / / ____|  _ \| |   / _ \|  _ \|  _ \  | ____| \ | |/ ___|_ _| \ | | ____|
// | | | \ \ / /|  _| | |_) | |  | | | | |_) | | | | |  _| |  \| | |  _ | ||  \| |  _|  
// | |_| |\ V / | |___|  _ <| |__| |_| |  _ <| |_| | | |___| |\  | |_| || || |\  | |___ 
//  \___/  \_/  |_____|_| \_\_____\___/|_| \_\____/  |_____|_| \_|\____|___|_| \_|_____|
//
// Overlord Engine v0.44
// Copyright Overlord Brecht Kets & Overlord Thomas Goussaert
// http://www.digitalartsandentertainment.com/
//--------------------------------------------------------------------------------------

#include "Ball.h"
#include "../../../Materials/FlatColorMaterial.h"
#include "OverlordComponents.h"

Ball::Ball(float size):
	m_Size(size),
	m_pBallModelComp(nullptr),
	m_pSphereCollider(nullptr),
	m_pRigidBody(nullptr),
	m_pBallMaterial(nullptr),
	m_pPhysicsMaterial(nullptr)
{
}


Ball::~Ball(void)
{
	SafeDelete(m_pBallMaterial);
	SafeDelete(m_pPhysicsMaterial);
}

void Ball::Initialize()
{
	//Add code here

	GetComponent<TransformComponent>()->Scale(m_Size,m_Size,m_Size);

	m_pBallMaterial = new FlatColorMaterial();
	
	m_pBallModelComp = new ModelComponent(L"./Resources/Sphere.ovm");
	m_pBallModelComp->SetMaterial(m_pBallMaterial);
	AddComponent(m_pBallModelComp);

	m_pPhysicsMaterial = new PhysicsMaterial();
	m_pPhysicsMaterial->SetRestitution(1.0f);
	m_pPhysicsMaterial->SetRestitutionCombineMode(NxCombineMode::NX_CM_MAX);
	m_pPhysicsMaterial->SetDynamicFriction(0);
	m_pPhysicsMaterial->SetStaticFriction(0);
	m_pPhysicsMaterial->SetFrictionCombineMode(NxCombineMode::NX_CM_MIN);

	m_pRigidBody = new RigidBodyComponent();
	m_pRigidBody->AddConstraints(DISABLE_GRAVITY | FREEZE_POS_Y);
	m_pRigidBody->SetMass(1.0f);
	m_pRigidBody->SetAngularDamping(0.05f);
	AddComponent(m_pRigidBody);
	
	m_pSphereCollider = new SphereColliderComponent(m_Size);
	m_pSphereCollider->SetPhysicsMaterial(m_pPhysicsMaterial);
	AddComponent(m_pSphereCollider);

	GameObject::Initialize();
}