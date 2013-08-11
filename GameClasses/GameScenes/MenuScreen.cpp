//====================== #INCLUDES ===================================
#include "MenuScreen.h"
//--------------------------------------------------------------------
#include "../Managers/ScreenManager.h"
#include "../Managers/SpritefontManager.h"
#include "../UserInterface/UIDockInterface.h"
#include "../GameScenes/MainMenuScreen.h"
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
	, m_MainMenuDock(nullptr)
{
}


MenuScreen::~MenuScreen(void)
{
	SafeDelete(m_MainMenuDock);
}

void MenuScreen::Initialize()
{
	InputAction returnToGame((int)InputControls::KB_ESCAPE_PRESSED,Pressed,VK_ESCAPE);
	ScreenManager::GetInstance()->GetInputManager()->AddInputAction(returnToGame);

	m_pSpriteFont = SpritefontManager::GetInstance()->CreateOrGet(_T("ComicSansMS"), 25);

	m_MainMenuDock = new UIDockInterface(552, 278, 196, 195, m_pSpriteFont); 
	m_MainMenuDock->AddImage(0,0,_T("IMG_Background"), _T("MenuScreen_BG.png"));
	m_MainMenuDock->Initialize();
	m_MainMenuDock->AddButton(15, 15, _T("BTN_Continue"), _T("menuscreen_btn_continue.png"), 
		[&] () 
		{
			ScreenManager::GetInstance()->SetControlScreen(_T("GameScreen"));
			ScreenManager::GetInstance()->RemoveActiveScreen(_T("MenuScreen"));
		} );
	m_MainMenuDock->AddButton(15, 102, _T("BTN_Options"), _T("menuscreen_btn_options.png"), 
		[&] () { } );
	m_MainMenuDock->AddButton(15, 188, _T("BTN_Quit"), _T("menuscreen_btn_quit.png"), 
		[&] () 
		{
		});

	m_MainMenuDock->Initialize();

	BaseScreen::Initialize();
}

void MenuScreen::Update(const GameContext& context)
{
	if(context.Input->IsActionTriggered((int)InputControls::KB_ESCAPE_PRESSED))
	{
		ScreenManager::GetInstance()->SetControlScreen(_T("GameScreen"));
		ScreenManager::GetInstance()->RemoveActiveScreen(_T("MenuScreen"));
	}

	m_MainMenuDock->Update(context);

	BaseScreen::Update(context);
}

void MenuScreen::Draw(const GameContext& context)
{
	//SpriteBatch::DrawTextW(m_pSpriteFont.get(), _T("PAUSED") , D3DXVECTOR2((float)context.Window->GetBufferWidth()/2.0f - 25, (float)context.Window->GetBufferHeight()/2 - 10));
	m_MainMenuDock->Draw(context);
	ScreenManager::GetInstance()->DrawCursor(context);
	BaseScreen::Draw(context);
}

void MenuScreen::BeginControl()
{

}

void MenuScreen::EndControl()
{

}

void MenuScreen::Activated()
{
}

void MenuScreen::Deactivated()
{
}