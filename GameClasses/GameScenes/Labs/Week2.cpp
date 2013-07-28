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

#include "Week2.h"
#include "OverlordComponents.h"
#include "Scenegraph/GameObject.h"
#include "Graphics/GraphicsDevice.h"
#include "Helpers/GeneralStructs.h"
#include "../../GameObjects/GameEntity.h"
#include "../../GameObjects/ColissionEntity.h"
#include "../../Managers/ScreenManager.h"
#include "Classes/House.h"
#include "Classes/Character.h"
#include "Classes/Key.h"
#include "Classes/Door.h"
#include "helpers/D3DUtil.h"


Week2::Week2(void)
	:BaseScreen(_T("Week2"), _T("Lab Week2: CharacterScene"), true)
	,m_pCamera(nullptr)
	,m_pHouse(nullptr)
	,m_pKey(nullptr)
	,m_pMrBlue(nullptr)
	,m_HouseRotation(0)
{
}


Week2::~Week2(void)
{
}

void Week2::Initialize()
{
	
	m_pCamera = new GameObject();
	auto camComponent = new CameraComponent();
	//SetActiveCamera(camComponent);
	m_pCamera->AddComponent(camComponent);
	camComponent->SetFieldOfView((float)D3DX_PI/4.0f);
	
	//m_pCamera->GetComponent<TransformComponent>()->Translate(175,0,0);
	m_pCamera->GetComponent<TransformComponent>()->Rotate(0,0,90);

	m_pHouse = new House(1.0f);
	m_pMrBlue = new Character(1.0f);
	m_pKey = new Key(m_pMrBlue);
	m_pDoor = new Door(m_pMrBlue);
	
	AddSceneObject(m_pCamera);
	AddSceneObject(m_pHouse);
	AddSceneObject(m_pKey);
	AddSceneObject(m_pDoor);
	AddSceneObject(m_pMrBlue);

	m_pMrBlue->GetComponent<TransformComponent>()->Translate(0,50,0);
	m_pHouse->GetComponent<TransformComponent>()->Rotate(-90,0,90);

	m_pKey->GetComponent<TransformComponent>()->Translate(35,6.5f,0);
	m_pKey->GetComponent<TransformComponent>()->Rotate(0,90,0);
	
	m_pDoor->GetComponent<TransformComponent>()->Translate(-28,23,-1);
	m_pDoor->GetComponent<TransformComponent>()->Rotate(0,90,0);
	
	BaseScreen::Initialize();
}

void Week2::Update(const GameContext& context)
{
	BaseScreen::Update(context);
}

void Week2::Draw(const GameContext& context)
{
	GraphicsDevice::GetInstance()->Clear(D3DXCOLOR(0.6f,0.81f,0.92f,1.0f));

	BaseScreen::Draw(context);
}