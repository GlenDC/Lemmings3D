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

#include "Week6.h"
#include "OverlordComponents.h"
#include "Scenegraph/GameObject.h"
#include "Graphics/GraphicsDevice.h"
#include "OverlordComponents.h"
#include "Helpers/GeneralStructs.h"
#include "../../GameObjects/GameEntity.h"
#include "../../Managers/ScreenManager.h"
#include "helpers/D3DUtil.h"


Week6::Week6(void)
	:BaseScreen(_T("Week6"), _T("Lab Week6: Geometry Shader 1.0"), true)
	,m_pSpikeySphere(nullptr)
	,m_pColorSpikeySphere(nullptr)
	,m_SpikeRotation(0)
{
}


Week6::~Week6(void)
{
}

void Week6::Initialize()
{
	//m_pInputManager->AddInputAction(InputAction(-1, Pressed, 'N'));
	//m_pInputManager->AddInputAction(InputAction(-2, Pressed, 'P'));

	m_pSpikeySphere = new GameEntity(MaterialType::MatSpikey);
	AddSceneObject(m_pSpikeySphere);

	m_pColorSpikeySphere = new GameEntity(MaterialType::MatSpikey);
	AddSceneObject(m_pColorSpikeySphere);

	BaseScreen::Initialize();
}

void Week6::Update(const GameContext& context)
{
	//handle special stuff
	if(context.Input->IsActionTriggered(-1))
	{
		ScreenManager::GetInstance()->RemoveActiveScreen(_T("Week6"));
		ScreenManager::GetInstance()->AddActiveScreen(_T("Week1"));
		ScreenManager::GetInstance()->SetControlScreen(_T("Week1"));
	}
	else if(context.Input->IsActionTriggered(-2))
	{
		ScreenManager::GetInstance()->RemoveActiveScreen(_T("Week6"));
		ScreenManager::GetInstance()->AddActiveScreen(_T("Week4"));
		ScreenManager::GetInstance()->SetControlScreen(_T("Week4"));
	}

	m_SpikeRotation += 200.0f * context.GameTime.ElapsedSeconds();
	m_pSpikeySphere->GetComponent<TransformComponent>()->Rotate(m_SpikeRotation,-m_SpikeRotation,0);
	m_pSpikeySphere->GetComponent<TransformComponent>()->Rotate(-m_SpikeRotation,0,m_SpikeRotation);

	BaseScreen::Update(context);
}

void Week6::Draw(const GameContext& context)
{
	GraphicsDevice::GetInstance()->Clear(D3DXCOLOR((float)(rand()%90+5)/100.0f,(float)(rand()%90+5)/100.0f,(float)(rand()%90+5)/100.0f,1));
	BaseScreen::Draw(context);
}