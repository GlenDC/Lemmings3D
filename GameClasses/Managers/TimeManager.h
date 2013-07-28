#pragma once

//====================== #INCLUDES ===================================
#include "ManagerInterface.h"

#include <vector>
//====================================================================

//====================== TimeManager Class =========================
// Description:
//		Manages time of the game and things related to its speed and flow
// Last Modification: 01/06/2013
// Copyright Glen De Cauwsemaecker
// www.glendc.com
//====================================================================

class Game;
class GameScreen;

class TimeManager : public ManagerInterface
{
public:
	~TimeManager(void);

	static TimeManager* GetInstance()
	{
		if (m_pInstance == nullptr)
			m_pInstance = new TimeManager();

		return m_pInstance;
	}

	virtual void Initialize();
	virtual void Update(GameContext& context);
	virtual void Draw(GameContext& context);

	int GetTimeMinutes() const;
	int GetTimeSeconds() const;
	int GetTimeTotalSeconds() const;

	void StartTimer();
	void PauseTimer(bool pause);
	void ResetTimer(bool start = true);

	bool IncreaseGameSpeed();
	bool DecreaseGameSpeed();
	void ResetGameSpeed();

	float GetGameSpeed() const;

	void SetGameScreen(GameScreen * pScreen) { m_pGameScreen = pScreen; }

private:
	TimeManager(void);
	static TimeManager* m_pInstance;

	static const int GAME_SPEED_LEVELS = 7;
	
	bool m_IsInitialized;
	bool m_Paused;

	float m_TotalSeconds;

	int m_GameSpeed;
	float m_GameSpeedLevels[GAME_SPEED_LEVELS];

	GameScreen * m_pGameScreen;

private:
	// -------------------------
	// Disabling default copy constructor and default 
	// assignment operator.
	// -------------------------
	TimeManager(const TimeManager& t);
	TimeManager& operator=(const TimeManager& t);
};

