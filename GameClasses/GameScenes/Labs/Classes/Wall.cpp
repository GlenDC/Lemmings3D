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

#include "Wall.h"
#include "OverlordComponents.h"

Wall::Wall(float width, float height, float depth, bool isTrigger):
	m_Dimensions(width,height,depth),
	m_IsTrigger(isTrigger),
	m_WasTriggered(false)
	,m_pBoxCollider(nullptr)
	,m_pRigidBody(nullptr)
{
}


Wall::~Wall(void)
{
}

void Wall::Initialize()
{
	m_pRigidBody = new RigidBodyComponent();
	m_pRigidBody->SetStatic(true);
	if(m_IsTrigger) 
		m_pRigidBody->SetOnTriggerCallBack([this](RigidBodyComponent* trigger, RigidBodyComponent* receiver, TriggerAction action)
											{
												if(action == TriggerAction::ENTER)this->m_WasTriggered = true;
											});
	AddComponent(m_pRigidBody);

	m_pBoxCollider = new BoxColliderComponent(m_Dimensions.x,m_Dimensions.y,m_Dimensions.z);
	m_pBoxCollider->SetAsTrigger(m_IsTrigger);

	AddComponent(m_pBoxCollider);
	GameObject::Initialize();
}

void Wall::OnTrigger(RigidBodyComponent* triggerobject, RigidBodyComponent* otherobject, TriggerAction action)
{
	m_WasTriggered = true;
}
