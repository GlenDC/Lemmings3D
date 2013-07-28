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

#include "BaseModeScreen.h"
#include "OverlordComponents.h"
#include "Scenegraph/GameObject.h"
#include "Graphics/GraphicsDevice.h"
#include "OverlordComponents.h"
#include "Helpers/GeneralStructs.h"
#include "../GameObjects/GameEntity.h"
#include "../GameObjects/ColissionEntity.h"
#include "../Managers/ScreenManager.h"
#include "../Managers/Stopwatch.h"
#include "../Entities/ParameterClass.h"
#include "helpers/D3DUtil.h"
#include "../UserInterface/BaseCursor.h"
#include "Helpers/SpriteFont.h"
#include "Managers/ContentManager.h"
#include "Game.h"
#include "../XML/XMLConverter.h"

BaseModeScreen::BaseModeScreen(GameScreen * parent, InputManager *inputManager)
	:m_pParentScreen(parent)
	,m_pInputManager(inputManager)
{
	m_pDefaultFont = ContentManager::Load<SpriteFont>(_T("./Resources/ComicSansMS_25.fnt"));
	/*m_pDeveloperZone = new UIZone((int)(GraphicsDevice::GetInstance()->GetWindowDimensions().x - 45),5,5,false,m_pDefaultFont);
	m_pDebugZone = new UIZone((int)(GraphicsDevice::GetInstance()->GetWindowDimensions().x - 350),5,5,false,m_pDefaultFont);*/
//	m_pDeveloperZone->AddButton(D3DXVECTOR2(35,35), _T("QuitGame"), [&] {
	/*	PostQuitMessage(0);
	}, _T("L3D_ui_QuitGame_n.png"), _T("L3D_ui_QuitGame_h.png")
		,_T("L3D_ui_QuitGame_c.png"));*/
}

BaseModeScreen::~BaseModeScreen(void)
{
	/*delete m_pDeveloperZone;
	delete m_pDebugZone;*/
}

void BaseModeScreen::Initialize()
{
	/*m_pDebugZone->AddTextField(D3DXVECTOR2(0,0), _T("FPS"), D3DXCOLOR(1,1,0,1), _T("FPS_ZONE"));

	m_pDeveloperZone->Initialize();*/
	//m_pDebugZone->Initialize();
}

void BaseModeScreen::Update(const GameContext& context)
{
	/*m_pDebugZone->UpdateTextField(_T("FPS_ZONE"), XMLConverter::ConvertToTString<double>(Game::GetFPS()));
	m_pDeveloperZone->Update(context);*/
	//m_pDebugZone->Update(context);
}

void BaseModeScreen::Draw(const GameContext& context)
{
	/*m_pDeveloperZone->Draw(context);
	m_pDebugZone->Draw(context);*/
}