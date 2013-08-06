#pragma once
//====================== #INCLUDES ===================================
#include "IManager.h"
#include "../Entities/Timer.h"

#include <map>
//====================================================================

//====================== Stopwatch Class =============================
// Description:
//		Management of timers. By an implementation of the singleton
//		pattern the stopwatch will serve as a global way to create
//		and manage timers. 
// TODO: 
//		Fix stopwatch bug => They stop and get deleted, when they shouldn't
//		Looping doesn't work correctly.
// Last Modification: July 2013
// Glen De Cauwsemaecker
// www.glendc.com
//====================================================================

class Timer;

// Ancillary class, implementing the Singleton Design pattern
class Stopwatch : public IManager
{
public:
	virtual ~Stopwatch();

	static Stopwatch * GetInstance();

	virtual void Initialize();
	virtual void Update(GameContext& context);
	virtual void Draw(GameContext& context){}

	bool CreateTimer(const tstring & name, const float targetTime, const bool countingDown, 
		const bool loop, const std::function<void ()> func, const bool paused = false);
	bool RemoveTimer(const tstring & name);
	void PauseTimer(const tstring & name, const bool paused);
	void SetCountingDownTimer(const tstring & name, const bool countingDown);
	void SetLoopTimer(const tstring & name, const bool looping);
	void ResetTimer(const tstring & name, const bool paused = false);
	void SetTargetTimeTimer(const tstring & name, const float targetTime, const bool reset = true, const bool paused = false);
	void SetFunctionTimer(const tstring & name, const std::function<void ()> func);

	int GetTimerMinutes(const tstring & name) const;
	int GetTimerSeconds(const tstring & name) const;
	int GetTimerTotalSeconds(const tstring & name) const;

private:
	static Stopwatch *m_pStopwatch; //Singleton
	std::map<const tstring, Timer> m_TimerContainer;
	std::map<const tstring, Timer> m_GarbageContainer;
	std::map<const tstring, Timer> m_TempContainer;

	Stopwatch();	// singletn pattern 

	// Disabling default copy constructor and default assignment operator.
	Stopwatch(const Stopwatch& yRef);									
	Stopwatch& operator=(const Stopwatch& yRef);
};