#pragma once

//====================== #INCLUDES ===================================
#include "IManager.h"

#include <vector>
//====================================================================

//====================== TimeManager Class =========================
// Description:
//		Manages time of the game and things related to its speed and flow
// Last Modification: July 2013
// Glen De Cauwsemaecker
// www.glendc.com
//====================================================================

class Game;
class GameScreen;

// Ancillary class, implementing the Singleton Design pattern
class TimeManager : public IManager
{
public:
	~TimeManager(void);

	static TimeManager* GetInstance();

	void Initialize();
	void Update(GameContext& context);
	void Draw(GameContext& context);

	int GetTimeMinutes() const;
	int GetTimeSeconds() const;
	int GetTimeTotalSeconds() const;

	void StartTimer();
	void PauseTimer(const bool pause);
	void ResetTimer(const bool start = true);

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

