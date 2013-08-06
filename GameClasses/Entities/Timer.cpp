//====================== #INCLUDES ===================================
#include "Timer.h"
//====================================================================

Timer::Timer() //Default Constructor
	:m_TargetTime(1.0f)
	,m_CurrentTime(0)
	,m_CountingDown(false)
	,m_Looping(false)
	,m_Paused(false)
	,m_Infinite(false)
	,m_ExcecutingFunction(nullptr)
{
	//ToDo: Write Constructor
}

Timer::Timer(const float targetTime, const bool countingDown, const bool loop, std::function<void ()> func, const bool paused) 
	:m_TargetTime(targetTime)
	,m_CurrentTime(countingDown?targetTime:0)
	,m_CountingDown(countingDown)
	,m_Looping(loop)
	,m_Paused(paused)
	,m_Infinite(targetTime == 0 ? true : false)
	,m_ExcecutingFunction(func)
{
	//ToDo: Write Constructor
}

Timer::~Timer() //Default Destructor
{
	//ToDo: Write Destructor
}

Timer::Timer(const Timer& yRef)
{
	*this = yRef;
}

Timer& Timer::operator=(const Timer& yRef)
{
	m_TargetTime = yRef.m_TargetTime;
	m_CurrentTime = yRef.m_CurrentTime;
	m_CountingDown = yRef.m_CountingDown;
	m_Looping = yRef.m_Looping;
	m_Paused = yRef.m_Paused;
	m_Infinite = yRef.m_Infinite;
	m_ExcecutingFunction = yRef.m_ExcecutingFunction;
	return *this;
}

bool Timer::Update(const GameContext& context)
{
	if(m_Paused)
		return false;
	if(m_CountingDown && m_CurrentTime >= 0)
	{
		m_CurrentTime -= context.GameTime.ElapsedSeconds();
		if(m_CurrentTime < 0)
		{
			m_ExcecutingFunction();
			if(m_Looping)
			{
				Reset(false);
				return false;
			}
			return true;
		}
		return false;
	}
	else if(!m_CountingDown && m_CurrentTime <= m_TargetTime)
	{
		m_CurrentTime += context.GameTime.ElapsedSeconds();
		if(m_CurrentTime > m_TargetTime)
		{
			m_ExcecutingFunction();
			if(m_Looping)
			{
				Reset(false);
				return false;
			}
			return true;
		}
		return false;
	}
	return true;
}

void Timer::SetPaused(const bool paused)
{
	m_Paused = paused;
}

void Timer::SetCountingDown(const bool countingDown)
{
	m_CountingDown = countingDown;
}

void Timer::SetLoop(const bool looping)
{
	m_Looping = looping;
}

void Timer::Reset(const bool paused)
{
	m_CurrentTime = m_CountingDown ? m_TargetTime : 0;
	SetPaused(paused);
}

void Timer::SetTargetTime(const float targetTime, const bool reset, const bool paused)
{
	m_TargetTime = targetTime;
	if(reset)	Reset(paused);
}

void Timer::SetFunction(std::function<void ()> func)
{
	m_ExcecutingFunction = func;
}

int Timer::GetCurrentTimeMinutes() const
{
	int currentTime(0);
	currentTime = (int)m_CurrentTime;
	return currentTime / 60;
}

int Timer::GetCurrentTimeSeconds() const
{
	int currentTime(0);
	currentTime = (int)m_CurrentTime;
	return currentTime % 60;
}

int Timer::GetCurrentTimeTotalSeconds() const
{
	int currentTime(0);
	currentTime = (int)m_CurrentTime;
	return currentTime;
}