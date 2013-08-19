//================================== INCLUDES ================================
#include "GameLoadingScreen.h"
//----------------------------------------------------------------------------
#include "../Entities/ParameterClass.h"
#include "../Managers/ParameterManager.h"
#include "../Managers/ScreenManager.h"
#include "../Managers/Stopwatch.h"
#include "../Managers/AudioManager.h"
#include "../GameScenes/GameScreen.h"
#include "../Managers/ColissionCollector.h"
#include <future>
//============================================================================
GameLoadingScreen::GameLoadingScreen(const tstring & previousScreen, UINT leveL_id)
	: LoadingScreen(previousScreen)
	, m_LevelID(leveL_id)
	, m_Thread()
	, m_InnerThread()
{

}

GameLoadingScreen::~GameLoadingScreen(void)
{

}

void GameLoadingScreen::Initialize()
{
	// Increase the play counter of this level for user stats
	tstringstream strstr;
	strstr << m_LevelID;
	tstring levelstring = strstr.str();
	ParameterClass & container = ParameterManager::GetInstance()->CreateOrGet(_T("Levels"));
	SetLoadingDescription(container.GetParameter<tstring>(levelstring));
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
		m_InnerThread = std::thread([&] ()
		{
			ColissionCollector::GetInstance()->CopyEnvironment();
			Stopwatch::GetInstance()->CreateTimer(_T("leveL_start_timer"), 1.0f, true, false, []() 
			{	
				ScreenManager::GetInstance()->AddActiveScreen(_T("GameScreen"));
				ScreenManager::GetInstance()->RemoveActiveScreen(_T("LoadingScreen"));
				ScreenManager::GetInstance()->RemoveScreen(_T("LoadingScreen"));
				ScreenManager::GetInstance()->SetPhysicsDrawEnabled(false);
				ScreenManager::GetInstance()->SetControlScreen(_T("GameScreen"));
			});
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