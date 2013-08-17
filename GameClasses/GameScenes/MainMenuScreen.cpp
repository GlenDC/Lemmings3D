//====================== #INCLUDES ===================================
#include "MainMenuScreen.h"
//--------------------------------------------------------------------
#include "../Managers/ScreenManager.h"
#include "../Managers/SpritefontManager.h"
#include "../Managers/ParameterManager.h"
#include "../Managers/AudioManager.h"
#include "../Entities/ParameterClass.h"
#include "../Lib/LemmingsHelpers.h"
#include "../UserInterface/UIDockInterface.h"
#include "../GameScenes/GameLoadingScreen.h"
#include "GameScreen.h"
//--------------------------------------------------------------------
#include <thread>
//--------------------------------------------------------------------
#include "Graphics/GraphicsDevice.h"
#include "Helpers/GeneralStructs.h"
#include "Managers/ContentManager.h"
#include "OverlordComponents.h"
#include "Scenegraph/GameObject.h"
//====================================================================

MainMenuScreen::MainMenuScreen(void)
	: BaseScreen(_T("MainMenuScreen"), _T("Lemmings3D Main Menu"), false)
	, m_pSpriteFont(nullptr)
	, m_pMainMenuDock(nullptr)
	, m_pLevelMenuDock(nullptr)
	, m_pStatisticsDock(nullptr)
{
}


MainMenuScreen::~MainMenuScreen(void)
{
	SafeDelete(m_pMainMenuDock);
	SafeDelete(m_pLevelMenuDock);
}

void MainMenuScreen::Initialize()
{
	ScreenManager::GetInstance()->SetPhysicsDrawEnabled(false);

	InputAction quitGame((int)InputControls::KB_ESCAPE_PRESSED,Pressed,VK_ESCAPE);
	ScreenManager::GetInstance()->GetInputManager()->AddInputAction(quitGame);
	InputAction startGame((int)InputControls::KB_RETURN_PRESSED,Pressed,VK_RETURN);
	ScreenManager::GetInstance()->GetInputManager()->AddInputAction(startGame);

	m_pSpriteFont = SpritefontManager::GetInstance()->CreateOrGet(_T("ComicSansMS"), 25);

	m_pMainMenuDock = new UIDockInterface(0, 0, 1280, 720, m_pSpriteFont); 
	m_pMainMenuDock->AddImage(0,0,_T("IMG_Background"), _T("MainMenu_BG.png"));
	m_pMainMenuDock->AddButton(710, 840, _T("Main_Btn_Options"), _T("MainMenu_btn_options.png"), [&] () { } );
	m_pMainMenuDock->AddButton(710, 950, _T("Main_Btn_Quit"), _T("MainMenu_btn_quit.png"), [&] () { PostQuitMessage(0); } );
	m_pMainMenuDock->Initialize();
	
	auto pFont = SpritefontManager::GetInstance()->CreateOrGet(_T("GameOver"),35);

	m_pLevelMenuDock = new UIDockInterface(50, 320, 1180, 450, pFont);
	ParameterClass & container_levels = ParameterManager::GetInstance()->CreateOrGet(_T("Levels"));
	m_pLevelMenuDock->AddButtonLevel(75,200,_T("Btn_Level_0"), 
		container_levels.GetParameter<tstring>(_T("0")),
		container_levels.GetChildParameter<tstring>(_T("0"), _T("BTN_IMAGE")), 0, 
		container_levels.GetChildParameter<UINT>(_T("0"), _T("BEST_SCORE")),
		container_levels.GetChildParameter<UINT>(_T("0"), _T("BEST_TIME")), [&] () 
		{
			ScreenManager::GetInstance()->AddScreen(new GameLoadingScreen(_T("MainMenuScreen"), 0));
		}, false);
	UINT level_0_succeeds = container_levels.GetChildParameter<UINT>(_T("0"), _T("TIMES_SUCCEED"));
	m_pLevelMenuDock->AddButtonLevel(480,200,_T("Btn_Level_1"), 
		container_levels.GetParameter<tstring>(_T("1")),
		container_levels.GetChildParameter<tstring>(_T("1"), _T("BTN_IMAGE")), 1, 
		container_levels.GetChildParameter<UINT>(_T("1"), _T("BEST_SCORE")),
		container_levels.GetChildParameter<UINT>(_T("1"), _T("BEST_TIME")), [&] () 
		{
			ScreenManager::GetInstance()->AddScreen(new GameLoadingScreen(_T("MainMenuScreen"), 1));
		}, level_0_succeeds == 0);
	UINT level_1_succeeds = container_levels.GetChildParameter<UINT>(_T("1"), _T("TIMES_SUCCEED"));
	m_pLevelMenuDock->AddButtonLevel(880,200,_T("Btn_Level_2"), 
		container_levels.GetParameter<tstring>(_T("1")),
		container_levels.GetChildParameter<tstring>(_T("2"), _T("BTN_IMAGE")), 2, 
		container_levels.GetChildParameter<UINT>(_T("2"), _T("BEST_SCORE")),
		container_levels.GetChildParameter<UINT>(_T("2"), _T("BEST_TIME")), [&] () 
		{
			ScreenManager::GetInstance()->AddScreen(new GameLoadingScreen(_T("MainMenuScreen"), 2));
		}, level_1_succeeds == 0);

	m_pLevelMenuDock->Initialize();

	tstringstream strstr;
	m_pStatisticsDock = new UIDockInterface(25, 570, 400, 250, pFont);
	ParameterClass & container = ParameterManager::GetInstance()->CreateOrGet(_T("UserStatistics"));
	strstr << _T("Total time played: ");
	strstr << LemmingsHelpers::GetFullTimeStringFromSecondsValue(container.GetParameter<UINT>(_T("TOTAL_TIME")));
	m_pStatisticsDock->AddTextField(0, 0, 250, 25, _T("txt_total_game_time"), strstr.str(), D3DXCOLOR(1,1,1,1));
	strstr.str(_T(""));
	strstr << _T("Total game sessions: ");
	UINT sessions = container.GetParameter<UINT>(_T("TOTAL_SESSIONS"));
	strstr << sessions;
	m_pStatisticsDock->AddTextField(0, 35, 250, 25, _T("txt_total_game_sessions"), strstr.str(), D3DXCOLOR(1,1,1,1));
	UINT total_succeeds(0);
	for(UINT i = 0 ; i < 3 ; ++i)
	{
		strstr.str(_T(""));
		strstr << i;
		UINT level_total_succeeds = container_levels.GetChildParameter<UINT>(strstr.str(), _T("TIMES_SUCCEED"));
		total_succeeds += level_total_succeeds;
	}
	container.SetParameter<UINT>(_T("TOTAL_SUCCEEDS"), total_succeeds);
	strstr.str(_T(""));
	strstr << _T("Total succeeds: ");
	strstr << container.GetParameter<UINT>(_T("TOTAL_SUCCEEDS"));
	m_pStatisticsDock->AddTextField(0, 70, 250, 25, _T("txt_total_game_succeeds"), strstr.str(), D3DXCOLOR(1,1,1,1));
	UINT most_played(0);
	for(UINT i = 0 ; i < 3 ; ++i)
	{
		strstr.str(_T(""));
		strstr << i;
		UINT most_games = container_levels.GetChildParameter<UINT>(strstr.str(), _T("TIMES_PLAYED"));
		if(most_games > most_played)
		{
			most_played = most_games;
			container.SetParameter<UINT>(_T("MOST_PLAYED"), i);
		}
	}
	strstr.str(_T(""));
	strstr << _T("Most played: ");
	strstr << container_levels.GetParameter<tstring>(container.GetParameter<tstring>(_T("MOST_PLAYED")));
	m_pStatisticsDock->AddTextField(0, 105, 250, 25, _T("txt_most_popular_level"), strstr.str(), D3DXCOLOR(1,1,1,1));
	strstr.str(_T(""));
	strstr << _T("Last session: ");
	strstr << container.GetParameter<tstring>(_T("LAST_PLAYED"));
	m_pStatisticsDock->AddTextField(0, 140, 250, 25, _T("txt_last_played"), strstr.str(), D3DXCOLOR(1,1,1,1));
	m_pStatisticsDock->Initialize();

	++sessions;
	container.SetParameter<UINT>(_T("TOTAL_SESSIONS"), sessions);
	container.Save();
	container_levels.Save();

	AudioManager::GetInstance()->PlaySong(_T("Main"));

	BaseScreen::Initialize();
}

void MainMenuScreen::Update(const GameContext& context)
{
	if(context.Input->IsActionTriggered((int)InputControls::KB_ESCAPE_PRESSED))
	{
		ScreenManager::GetInstance()->QuitGame();
	}

	m_pMainMenuDock->Update(context);
	m_pLevelMenuDock->Update(context);
	m_pStatisticsDock->Update(context);

	BaseScreen::Update(context);
}

void MainMenuScreen::Draw(const GameContext& context)
{
	m_pLevelMenuDock->Draw(context);
	//m_pStatisticsDock->Draw(context);
	m_pMainMenuDock->Draw(context);

	ScreenManager::GetInstance()->DrawCursor(context);

	BaseScreen::Draw(context);
}

void MainMenuScreen::BeginControl()
{

}

void MainMenuScreen::EndControl()
{

}

void MainMenuScreen::Activated()
{
}

void MainMenuScreen::Deactivated()
{
}