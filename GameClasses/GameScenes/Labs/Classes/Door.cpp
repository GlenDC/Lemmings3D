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

#include "Door.h"
#include "../../../Materials/FlatTextureMaterial.h"
#include "OverlordComponents.h"
#include "Character.h"
#include "Helpers/GeneralStructs.h"

Door::Door(Character * pCharacter):
	m_pVisualMaterial(nullptr),
	m_Model(nullptr),
	m_pTriggerCharacter(pCharacter),
	m_Open(false)
{
}


Door::~Door(void)
{
	SafeDelete(m_pVisualMaterial);
}

void Door::Initialize()
{
	//Add code here

	m_pVisualMaterial = new FlatTextureMaterial();
	m_pVisualMaterial->SetDiffuse(L"./Resources/Lab3/UberDoor_Diffuse.png");

	m_Model = new ModelComponent(L"./Resources/Lab3/UberDoor.ovm");
	m_Model->SetMaterial(m_pVisualMaterial);
	AddComponent(m_Model);

	auto rigidBody = new RigidBodyComponent();
	rigidBody->SetStatic(true);

	rigidBody->SetOnTriggerCallBack([this](RigidBodyComponent* trigger, RigidBodyComponent* receiver, TriggerAction action)
		{
			if(action == TriggerAction::ENTER)
			{
				if(m_pTriggerCharacter->HasItem(1))
				{
					m_Open = true;
				}
			}
		});

	AddComponent(rigidBody);

	/*auto meshCollider = new  MeshColliderComponent(L"./Resources/CharacterHouse_ConvexMesh.ovp",true);
	AddComponent(meshCollider);*/

	auto meshCollider2 = new  MeshColliderComponent(L"./Resources/Lab3/UberDoor_ConvexMesh.ovp",true);
	meshCollider2->SetAsTrigger(true);
	AddComponent(meshCollider2);


	GameObject::Initialize();
}

void Door::Update(const GameContext& context)
{
	D3DXQUATERNION rotation = GetComponent<TransformComponent>()->GetLocalRotation();
	if(m_Open)
	{
		GetComponent<TransformComponent>()->Rotate(0, rotation.y + 0.00001f * context.GameTime.ElapsedSeconds(),0);
		wstringstream strstr;
		OutputDebugString(strstr.str().c_str());
		D3DXVECTOR3 vec = GetComponent<TransformComponent>()->GetWorldPosition();
		float moveSpeed = 75.0f * context.GameTime.ElapsedSeconds();
		GetComponent<TransformComponent>()->Translate(vec.x - moveSpeed, vec.y , vec.z - moveSpeed);
		if(rotation.y < 1.65806e-007)
			m_Open = false;
	}

	GameObject::Update(context);
}