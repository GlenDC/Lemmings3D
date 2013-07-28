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

#include "Peddle.h"
#include "../../../Materials/FlatColorMaterial.h"
#include "OverlordComponents.h"


Peddle::Peddle(float width, float height, float depth):
	m_Dimensions(width,height,depth),
	m_pPeddleModelComp(nullptr),
	m_pBoxCollider(nullptr),
	m_pRigidBody(nullptr),
	m_pPeddleMaterial(nullptr)
{
}


Peddle::~Peddle(void)
{
	SafeDelete(m_pPeddleMaterial);
}

void Peddle::Initialize()
{
	GetComponent<TransformComponent>()->Scale(m_Dimensions);

	m_pPeddleMaterial = new FlatColorMaterial();

	m_pPeddleModelComp = new ModelComponent(L"./Resources/Box.ovm");
	m_pPeddleModelComp->SetMaterial(m_pPeddleMaterial);
	AddComponent(m_pPeddleModelComp);

	m_pRigidBody = new RigidBodyComponent();
	m_pRigidBody->SetStatic(true);
	AddComponent(m_pRigidBody);

	m_pBoxCollider = new BoxColliderComponent(m_Dimensions.x, m_Dimensions.y, m_Dimensions.z);
	AddComponent(m_pBoxCollider);

	GameObject::Initialize();
}