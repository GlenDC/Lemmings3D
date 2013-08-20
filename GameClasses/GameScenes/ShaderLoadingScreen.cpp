//================================== INCLUDES ================================
#include "ShaderLoadingScreen.h"
//----------------------------------------------------------------------------
#include "../Entities/ParameterClass.h"
#include "../Managers/ParameterManager.h"
#include "../Managers/ScreenManager.h"
#include "../Managers/Stopwatch.h"
#include "../Managers/AudioManager.h"
#include "../GameScenes/GameScreen.h"
#include "../Managers/ColissionCollector.h"
#include <future>
#include "ShaderScreen.h"
//============================================================================
ShaderLoadingScreen::ShaderLoadingScreen(const tstring & previousScreen)
	: LoadingScreen(previousScreen)
	, m_Thread()
{
	AudioManager::GetInstance()->PlaySong(_T("Loading"));
	SetLoadingDescription(_T("G. Shader Demos"));
}

ShaderLoadingScreen::~ShaderLoadingScreen(void)
{

}

void ShaderLoadingScreen::Initialize()
{
	// manage screens		
	ScreenManager::GetInstance()->RemoveActiveScreen(m_PreviousScreenName);
	ScreenManager::GetInstance()->AddActiveScreen(m_name);
	ScreenManager::GetInstance()->SetControlScreen(m_name);
	// start a thread for the creation of the level
	m_Thread = std::thread([&] () 
	{
		ScreenManager::GetInstance()->AddScreen(new ShaderScreen());
		Stopwatch::GetInstance()->CreateTimer(_T("shader_start_timer"), 1.0f, true, false, [&]() 
		{	
			ScreenManager::GetInstance()->AddActiveScreen(_T("ShaderScreen"));
			ScreenManager::GetInstance()->RemoveActiveScreen(_T("LoadingScreen"));
			ScreenManager::GetInstance()->RemoveScreen(_T("LoadingScreen"));
			ScreenManager::GetInstance()->SetPhysicsDrawEnabled(true);
			ScreenManager::GetInstance()->SetControlScreen(_T("ShaderScreen"));
			AudioManager::GetInstance()->PlaySoundEffect(_T("Loading Finished"));
			AudioManager::GetInstance()->PlaySong(_T("Demo"));
		});
	});
	LoadingScreen::Initialize();
}

void ShaderLoadingScreen::Update(const GameContext& context)
{
	LoadingScreen::Update(context);
}

void ShaderLoadingScreen::Draw(const GameContext& context)
{
	LoadingScreen::Draw(context);
}

void ShaderLoadingScreen::BeginControl()
{
	LoadingScreen::BeginControl();
}

void ShaderLoadingScreen::EndControl()
{
	LoadingScreen::EndControl();
}

void ShaderLoadingScreen::Activated()
{
	LoadingScreen::Activated();
}

void ShaderLoadingScreen::Deactivated()
{
	LoadingScreen::Deactivated();
}