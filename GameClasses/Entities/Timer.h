//====================== #INCLUDES ===================================
#include "Helpers/stdafx.h"
#include "Helpers/D3DUtil.h"
#include "Helpers/GeneralStructs.h"

#include <functional>
//====================================================================

//====================== Timer Class =================================
// Description:
//		A stand allone timer class, used for the Stopwatch (== time management) class.
// Last Modification: 11/03/2013
// Copyright Glen De Cauwsemaecker
// www.glendc.com
//====================================================================

class Timer
{
public:
	Timer();
	Timer(float targetTime, bool countingDown, bool loop, std::function<void ()> func, bool paused = false);
	~Timer();
	Timer(const Timer& yRef);									
	Timer& operator=(const Timer& yRef);


	bool Update(const GameContext& context);
	void SetPaused(bool paused);
	void SetCountingDown(bool countingDown);
	void SetLoop(bool looping);
	void Reset(bool paused = false);
	void SetTargetTime(float targetTime, bool reset = true, bool paused = false);
	void SetFunction(std::function<void ()> func);

	int GetCurrentTimeMinutes() const;
	int GetCurrentTimeSeconds() const;
	int GetCurrentTimeTotalSeconds() const;

private:
	float m_TargetTime, m_CurrentTime;
	bool m_CountingDown, m_Looping, m_Paused, m_Infinite;

	std::function<void ()> m_ExcecutingFunction;
};