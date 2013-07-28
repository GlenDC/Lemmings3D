#include "TimeManager.h"
#include "Game.h"

#include "Stopwatch.h"
#include "../GameScenes/GameScreen.h"

TimeManager* TimeManager::m_pInstance = nullptr;

TimeManager::TimeManager(void)
	: m_IsInitialized(false)
	, m_Paused(true)
	, m_TotalSeconds(0)
	, m_GameSpeed(3)
	, m_pGameScreen(nullptr)
{
	m_GameSpeedLevels[0] = -5.0f;
	m_GameSpeedLevels[1] = -3.0f;
	m_GameSpeedLevels[2] = -2.0f;
	m_GameSpeedLevels[3] = 1.0f;
	m_GameSpeedLevels[4] = 2.0f;
	m_GameSpeedLevels[5] = 3.0f;
	m_GameSpeedLevels[6] = 5.0f;
}

TimeManager::~TimeManager(void)
{
}

void TimeManager::Initialize()
{
	m_IsInitialized = true;
}

void TimeManager::Update(GameContext& context)
{
	if(!m_Paused)
	{
		m_TotalSeconds += context.GameTime.ElapsedSpeedGameTime;
		if(m_TotalSeconds < 0)
		{
			m_TotalSeconds = 0;
			ResetGameSpeed();
			if(m_pGameScreen != nullptr)
			{
				m_pGameScreen->SetGameSpeedTxtField();
			}
		}
	}
}

void TimeManager::Draw(GameContext& context)
{
}

int TimeManager::GetTimeMinutes() const
{
	int minutes(0);
	minutes = (int)m_TotalSeconds;
	return minutes / 60;
}

int TimeManager::GetTimeSeconds() const
{
	int seconds(0);
	seconds = (int)m_TotalSeconds;
	return seconds % 60;
}

int TimeManager::GetTimeTotalSeconds() const
{
	int seconds(0);
	seconds = (int)m_TotalSeconds;
	return seconds;
}

void TimeManager::StartTimer()
{
	m_Paused = false;
	m_TotalSeconds = 0;
}

void TimeManager::PauseTimer(bool pause)
{
	m_Paused = pause;
}

void TimeManager::ResetTimer(bool start)
{
	m_TotalSeconds = 0;
	m_Paused = !start;
}

bool TimeManager::IncreaseGameSpeed()
{
	++m_GameSpeed;
	if(m_GameSpeed == GAME_SPEED_LEVELS)
	{
		--m_GameSpeed;
		return false;
	}
	return true;
}

bool TimeManager::DecreaseGameSpeed()
{
	--m_GameSpeed;
	if(m_GameSpeed < 0)
	{
		++m_GameSpeed;
		return false;
	}
	return true;
}

void TimeManager::ResetGameSpeed()
{
	m_GameSpeed = 3;
}

float TimeManager::GetGameSpeed() const 
{ 
	return m_Paused ? 0.0f : m_GameSpeedLevels[m_GameSpeed]; 
}