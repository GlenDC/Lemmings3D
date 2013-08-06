//====================== #INCLUDES ===================================
#include "MenuScreen.h"
//--------------------------------------------------------------------
#include "../Managers/ScreenManager.h"
#include "../Managers/SpritefontManager.h"
//--------------------------------------------------------------------
#include "Graphics/GraphicsDevice.h"
#include "Helpers/GeneralStructs.h"
#include "Managers/ContentManager.h"
#include "OverlordComponents.h"
#include "Scenegraph/GameObject.h"
//====================================================================

MenuScreen::MenuScreen(void)
	: BaseScreen(_T("MenuScreen"), _T("Lemmings3D Menu"), false)
	, m_pSpriteFont(nullptr)
{
}


MenuScreen::~MenuScreen(void)
{
}

void MenuScreen::Initialize()
{
	InputAction returnToGame(0,Pressed,VK_ESCAPE);
	ScreenManager::GetInstance()->GetInputManager()->AddInputAction(returnToGame);

	m_pSpriteFont = SpritefontManager::GetInstance()->CreateOrGet(_T("ComicSansMS"), 25);

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
	SpriteBatch::DrawTextW(m_pSpriteFont.get(), _T("PAUSED") , D3DXVECTOR2((float)context.Window->GetBufferWidth()/2.0f - 25, (float)context.Window->GetBufferHeight()/2 - 10));
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