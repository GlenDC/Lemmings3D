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

#include "Key.h"
#include "../../../Materials/FlatTextureMaterial.h"
#include "OverlordComponents.h"
#include "Character.h"

Key::Key(Character * pCharacter):
	m_pVisualMaterial(nullptr),
	m_Model(nullptr),
	m_pTriggerCharacter(pCharacter)
{
}


Key::~Key(void)
{
	SafeDelete(m_pVisualMaterial);
}

void Key::Initialize()
{
	//Add code here

	m_pVisualMaterial = new FlatTextureMaterial();
	m_pVisualMaterial->SetDiffuse(L"./Resources/Lab3/UberChest_Diffuse.png");

	m_Model = new ModelComponent(L"./Resources/Lab3/UberChest_Closed.ovm");
	m_Model->SetMaterial(m_pVisualMaterial);
	AddComponent(m_Model);

	auto rigidBody = new RigidBodyComponent();
	rigidBody->SetStatic(true);

	rigidBody->SetOnTriggerCallBack([this](RigidBodyComponent* trigger, RigidBodyComponent* receiver, TriggerAction action)
		{
			if(action == TriggerAction::ENTER)
			{
				m_pTriggerCharacter->AddToInventory(1);
				RemoveComponent(m_Model);
				m_Model = new ModelComponent(L"./Resources/Lab3/UberChest_Open.ovm");
				m_Model->SetMaterial(m_pVisualMaterial);
				AddComponent(m_Model);
			}
		});

	AddComponent(rigidBody);

	/*auto meshCollider = new  MeshColliderComponent(L"./Resources/CharacterHouse_ConvexMesh.ovp",true);
	AddComponent(meshCollider);*/

	auto meshCollider2 = new  MeshColliderComponent(L"./Resources/Lab3/UberChest_Closed_ConvexMesh.ovp",true);
	meshCollider2->SetAsTrigger(true);
	AddComponent(meshCollider2);


	GameObject::Initialize();
}