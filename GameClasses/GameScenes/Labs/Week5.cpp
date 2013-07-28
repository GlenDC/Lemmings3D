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

#include "Week5.h"
#include "OverlordComponents.h"
#include "Scenegraph/GameObject.h"
#include "Graphics/GraphicsDevice.h"
#include "OverlordComponents.h"
#include "Helpers/GeneralStructs.h"
#include "../../GameObjects/GameEntity.h"
#include "../../GameObjects/ColissionEntity.h"
#include "../../Managers/ScreenManager.h"
#include "../../Managers/Stopwatch.h"
#include "../../Entities/ParameterClass.h"
#include "../../Materials/SkinnedMaterial.h"
#include "helpers/D3DUtil.h"


Week5::Week5(void)
	:BaseScreen(_T("Week5"), _T("Lab Week5: Animations... Walk my little puppet!"), false)
	,m_pSkinnedMaterial(nullptr)
	,m_pModelComponent(nullptr)
	,m_pGameObject(nullptr)
{
}


Week5::~Week5(void)
{
	delete m_pSkinnedMaterial;
}

void Week5::Initialize()
{
	m_pSkinnedMaterial = new SkinnedMaterial();
	m_pSkinnedMaterial->SetDiffuse(_T("./Resources/Vampire_Diffuse.dds"));

	m_pModelComponent = new ModelComponent(_T("./Resources/HeroTest.ovm"));
	m_pModelComponent->SetMaterial(m_pSkinnedMaterial);

	m_pGameObject = new GameObject();
	m_pGameObject->AddComponent(m_pModelComponent);

	AddSceneObject(m_pGameObject);

	BaseScreen::Initialize();
}

void Week5::Update(const GameContext& context)
{
	m_pSkinnedMaterial->SetBoneTransformations(m_pModelComponent->GetBoneTransformations());
	BaseScreen::Update(context);
}

void Week5::Draw(const GameContext& context)
{
	GraphicsDevice::GetInstance()->Clear(D3DXCOLOR(1,1,1,1));
	BaseScreen::Draw(context);
}