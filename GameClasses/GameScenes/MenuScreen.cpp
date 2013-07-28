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

#include "MenuScreen.h"
#include "OverlordComponents.h"
#include "Scenegraph/GameObject.h"
#include "Graphics/GraphicsDevice.h"
#include "OverlordComponents.h"
#include "Helpers/GeneralStructs.h"
#include "../Managers/ScreenManager.h"
#include "Managers/ContentManager.h"

MenuScreen::MenuScreen(void)
	:BaseScreen(_T("MenuScreen"), _T("Lemmings3D Menu"), false)
	,m_pSpriteFont(nullptr)
{
}


MenuScreen::~MenuScreen(void)
{
}

void MenuScreen::Initialize()
{
	InputAction returnToGame(0,Pressed,VK_ESCAPE);
	ScreenManager::GetInstance()->GetInputManager()->AddInputAction(returnToGame);

	m_pSpriteFont = ContentManager::Load<SpriteFont>(_T("./Resources/ComicSansMS_25.fnt"));

	BaseScreen::Initialize();
}

void MenuScreen::Update(const GameContext& context)
{
	if(context.Input->IsActionTriggered((int)InputControls::KB_ESCAPE_PRESSED))
	{
		ScreenManager::GetInstance()->SetControlScreen(_T("GameScreen"));
		ScreenManager::GetInstance()->RemoveActiveScreen(_T("MenuScreen"));
	}

	BaseScreen::Update(context);
}

void MenuScreen::Draw(const GameContext& context)
{
	SpriteBatch::DrawTextW(m_pSpriteFont, _T("PAUSED") , D3DXVECTOR2((float)context.Window->GetBufferWidth()/2.0f - 25, (float)context.Window->GetBufferHeight()/2 - 10));
	BaseScreen::Draw(context);
}

void MenuScreen::Activated()
{
	BaseScreen::Activated();
}

void MenuScreen::Deactivated()
{
	BaseScreen::Deactivated();
}