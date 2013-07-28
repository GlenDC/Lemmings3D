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

#include "House.h"
#include "../../../Materials/FlatTextureMaterial.h"
#include "OverlordComponents.h"

House::House(float scale):
	m_pVisualMaterial(nullptr)
	,m_Scale(scale)
{
}


House::~House(void)
{
	SafeDelete(m_pVisualMaterial);
}

void House::Initialize()
{
	//Add code here
	GetComponent<TransformComponent>()->Scale(m_Scale,m_Scale,m_Scale);
	GetComponent<TransformComponent>()->Translate(0,0,0);

	m_pVisualMaterial = new FlatTextureMaterial();
	m_pVisualMaterial->SetDiffuse(L"./Resources/Level_Diffuse.png");

	auto model = new ModelComponent(L"./Resources/CharacterHouse.ovm");
	model->SetMaterial(m_pVisualMaterial);
	AddComponent(model);

	auto rigidBody = new RigidBodyComponent();
	rigidBody->SetStatic(true);
	AddComponent(rigidBody);
	/*rigidBody->AddConstraints(Constraints::DISABLE_GRAVITY);
	rigidBody->AddConstraints(Constraints::FREEZE_POS_X);
	rigidBody->AddConstraints(Constraints::FREEZE_POS_Y);
	rigidBody->AddConstraints(Constraints::FREEZE_POS_Z);
	rigidBody->AddConstraints(Constraints::FREEZE_ROT_X);
	rigidBody->AddConstraints(Constraints::FREEZE_ROT_Y);
	rigidBody->AddConstraints(Constraints::FREEZE_ROT_Z);*/

	/*auto meshCollider = new  MeshColliderComponent(L"./Resources/CharacterHouse_ConvexMesh.ovp",true);
	AddComponent(meshCollider);*/

	auto meshCollider2 = new  MeshColliderComponent(L"./Resources/CharacterHouse_TriangleMesh.ovp",false);
	AddComponent(meshCollider2);

	GameObject::Initialize();
}