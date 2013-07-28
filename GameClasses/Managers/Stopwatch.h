#pragma once
//====================== #INCLUDES ===================================
#include "ManagerInterface.h"
#include "../Entities/Timer.h"

#include <map>
//====================================================================

//====================== Stopwatch Class =============================
// Description:
//		Management of timers. By an implementation of the singleton
//		pattern the stopwatch will serve as a global way to create
//		and manage timers. 
// Last Modification: 11/03/2013
// Copyright Glen De Cauwsemaecker
// www.glendc.com
//====================================================================


//====================== Forward Declerations ========================
class Timer;
//====================================================================

class Stopwatch : public ManagerInterface
{
public:
	virtual ~Stopwatch();

	static Stopwatch * GetInstance();

	virtual void Initialize();
	virtual void Update(GameContext& context);
	virtual void Draw(GameContext& context){}

	bool CreateTimer(const tstring & name, float targetTime, bool countingDown, bool loop, std::function<void ()> func, bool paused = false);
	bool RemoveTimer(const tstring & name);
	void PauseTimer(const tstring & name, bool paused);
	void SetCountingDownTimer(const tstring & name, bool countingDown);
	void SetLoopTimer(const tstring & name, bool looping);
	void ResetTimer(const tstring & name, bool paused = false);
	void SetTargetTimeTimer(const tstring & name, float targetTime, bool reset = true, bool paused = false);
	void SetFunctionTimer(const tstring & name, std::function<void ()> func);

	int GetTimerMinutes(const tstring & name) const;
	int GetTimerSeconds(const tstring & name) const;
	int GetTimerTotalSeconds(const tstring & name) const;

private:
	static Stopwatch *m_pStopwatch; //SingleTon
	std::map<const tstring, Timer> m_TimerContainer;
	std::map<const tstring, Timer> m_GarbageContainer;
	std::map<const tstring, Timer> m_TempContainer;

	//private methods
	Stopwatch();	// singletn pattern 
	// Disabling default copy constructor and default assignment operator.
	Stopwatch(const Stopwatch& yRef);									
	Stopwatch& operator=(const Stopwatch& yRef);
};