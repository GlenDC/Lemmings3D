//====================== #INCLUDES ===================================
#include "MenuModeScreen.h"
//--------------------------------------------------------------------
#include "Graphics/GraphicsDevice.h"
#include "Helpers/D3DUtil.h"
#include "Helpers/GeneralStructs.h"
#include "OverlordComponents.h"
//--------------------------------------------------------------------
#include "GameScreen.h"
#include "../Entities/ParameterClass.h"
#include "../Lib/GlobalParameters.h"
#include "../Lib/LemmingsHelpers.h"
#include "../Managers/ScreenManager.h"
#include "../Managers/SpritefontManager.h"
#include "../UserInterface/UIDockInterface.h"
//====================================================================

MenuModeScreen::MenuModeScreen(GameScreen * parent, InputManager *inputManager)
	: BaseModeScreen(parent, inputManager)
	, m_pSpriteFont(nullptr)
	, m_MainMenuDock(nullptr)
{

}


MenuModeScreen::~MenuModeScreen(void)
{
}

void MenuModeScreen::Initialize()
{
	m_pSpriteFont = SpritefontManager::GetInstance()->CreateOrGet(_T("ComicSansMS"), 25);

	m_MainMenuDock = new UIDockInterface(552, 278, 196, 195, m_pSpriteFont); 
	m_MainMenuDock->AddImage(0,0,_T("IMG_Background"), _T("MenuScreen_BG.png"));
	m_MainMenuDock->Initialize();
	m_MainMenuDock->AddButton(15, 15, _T("BTN_Continue"), _T("menuscreen_btn_continue.png"), 
		[&] () 
		{
			m_pParentScreen->SetPreviousState();
		} );
	m_MainMenuDock->AddButton(15, 102, _T("BTN_Options"), _T("menuscreen_btn_options.png"), 
		[&] () { } );
	m_MainMenuDock->AddButton(15, 188, _T("BTN_Quit"), _T("menuscreen_btn_quit.png"), 
		[&] () 
		{
			ScreenManager::GetInstance()->AddActiveScreen(_T("MainMenuScreen"));	
			ScreenManager::GetInstance()->SetControlScreen(_T("MainMenuScreen"));
			ScreenManager::GetInstance()->RemoveActiveScreen(_T("GameScreen"));
			ScreenManager::GetInstance()->RemoveScreen(_T("GameScreen"));
			ScreenManager::GetInstance()->SetPhysicsDrawEnabled(false);
		});

	m_MainMenuDock->Initialize();
}

void MenuModeScreen::Update(const GameContext& context)
{
	if(context.Input->IsActionTriggered((int)InputControls::KB_ESCAPE_PRESSED))
	{
		m_pParentScreen->SetPreviousState();
	}
	m_MainMenuDock->Update(context);
}

void MenuModeScreen::Draw(const GameContext& context)
{
	m_MainMenuDock->Draw(context);
}

void MenuModeScreen::Draw2D(const GameContext& context)
{
}

void MenuModeScreen::Activate()
{
	m_pParentScreen->PauseGame(true);
	ScreenManager::GetInstance()->SetPhysicsDrawEnabled(false);

	BaseModeScreen::Activate();
}

void MenuModeScreen::Deactivate()
{
	m_pParentScreen->PauseGame(false);
	ScreenManager::GetInstance()->SetPreviousPhysicsDrawEnabled();

	BaseModeScreen::Deactivate();
}