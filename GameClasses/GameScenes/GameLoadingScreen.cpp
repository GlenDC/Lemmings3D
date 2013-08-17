//================================== INCLUDES ================================
#include "GameLoadingScreen.h"
//----------------------------------------------------------------------------
#include "../Entities/ParameterClass.h"
#include "../Managers/ParameterManager.h"
#include "../Managers/ScreenManager.h"
#include "../Managers/Stopwatch.h"
#include "../Managers/AudioManager.h"
#include "../GameScenes/GameScreen.h"
//============================================================================
GameLoadingScreen::GameLoadingScreen(const tstring & previousScreen, UINT leveL_id)
	: LoadingScreen(previousScreen)
	, m_LevelID(leveL_id)
	, m_Thread()
{

}

GameLoadingScreen::~GameLoadingScreen(void)
{

}

void GameLoadingScreen::Initialize()
{
	// Increase the playcounter of this level for user stats
	tstringstream strstr;
	strstr << m_LevelID;
	tstring levelstring = strstr.str();
	ParameterClass & container = ParameterManager::GetInstance()->CreateOrGet(_T("Levels"));
	UINT totals_played = container.GetChildParameter<UINT>(levelstring, _T("TIMES_PLAYED"));
	++totals_played;
	container.SetChildParameter<UINT>(levelstring, _T("TIMES_PLAYED"), totals_played);
	container.Save();
	// manage screens		
	ScreenManager::GetInstance()->RemoveActiveScreen(m_PreviousScreenName);
	ScreenManager::GetInstance()->AddActiveScreen(m_name);
	ScreenManager::GetInstance()->SetControlScreen(m_name);
	// start a thread for the creation of the level

	m_Thread = std::thread([&] () 
	{
		AudioManager::GetInstance()->PlaySong(container.GetChildParameter<tstring>(strstr.str(), _T("SOUND_TRACK")));
		tstringstream strstr;
		strstr << _T("level") << m_LevelID;
		ScreenManager::GetInstance()->AddScreen(new GameScreen(strstr.str()));
		Stopwatch::GetInstance()->CreateTimer(_T("leveL_start_timer"), 1.0f, true, false, []() 
		{
			ScreenManager::GetInstance()->AddActiveScreen(_T("GameScreen"));	
			ScreenManager::GetInstance()->SetControlScreen(_T("GameScreen"));
			ScreenManager::GetInstance()->RemoveActiveScreen(_T("LoadingScreen"));
			ScreenManager::GetInstance()->RemoveScreen(_T("LoadingScreen"));
			ScreenManager::GetInstance()->SetPhysicsDrawEnabled(true);
		});
	});
	LoadingScreen::Initialize();
}

void GameLoadingScreen::Update(const GameContext& context)
{
	LoadingScreen::Update(context);
}

void GameLoadingScreen::Draw(const GameContext& context)
{
	LoadingScreen::Draw(context);
}

void GameLoadingScreen::BeginControl()
{
	LoadingScreen::BeginControl();
}

void GameLoadingScreen::EndControl()
{
	LoadingScreen::EndControl();
}

void GameLoadingScreen::Activated()
{
	LoadingScreen::Activated();
}

void GameLoadingScreen::Deactivated()
{
	LoadingScreen::Deactivated();
}