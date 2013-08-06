//====================== #INCLUDES ===================================
#include "Stopwatch.h"
//--------------------------------------------------------------------
#include <algorithm>
//====================================================================

Stopwatch * Stopwatch::m_pStopwatch = nullptr;
	
Stopwatch::Stopwatch()	// Default constructor == Private => singleton pattern
{
}

Stopwatch::~Stopwatch()	//Default destructor
{

}

Stopwatch * Stopwatch::GetInstance()
{
	if(m_pStopwatch == nullptr)
	{
		m_pStopwatch = new Stopwatch();
		m_pStopwatch->Initialize();
	}
	return m_pStopwatch;
}

void Stopwatch::Initialize()
{

}

void Stopwatch::Update(GameContext& context)
{
	//clean up the trash
	for(auto it : m_GarbageContainer)
	{
		m_TimerContainer.erase(it.first);
	}
	m_GarbageContainer.clear();

	//add new timers
	for(auto it : m_TempContainer)
	{
		m_TimerContainer[it.first] = it.second;
	}
	m_TempContainer.clear();

	for(auto it = m_TimerContainer.begin() ; it != m_TimerContainer.end() ; ) 
	{
		if (it->second.Update(context)) 
		{
			m_TimerContainer.erase(it++);
        } 
		else 
		{
			 ++it;
        }
	}
}

bool Stopwatch::CreateTimer(const tstring & name, const float targetTime, const bool countingDown, const bool loop, 
							const std::function<void ()> func, const bool paused)
{
	for(auto it : m_TempContainer)
	{
		if(it.first == name)
		{
			return false;
		}
	}

	for (auto it = m_TimerContainer.begin(); it != m_TimerContainer.end() ; ++it)
	{
		if(it->first == name)
		{
			m_GarbageContainer[it->first] = it->second;
			break;
		}
	}

	Timer newTimer(targetTime, countingDown, loop, func, paused);
	m_TempContainer[name] = newTimer;
	return true;
}

bool Stopwatch::RemoveTimer(const tstring & name)
{
	for (auto it = m_TimerContainer.begin(); it != m_TimerContainer.end() ; ++it)
	{
		if (it->first == name)
		{
			m_GarbageContainer[it->first] = it->second;
			return true;
		}
	}
	return false;
}

void Stopwatch::PauseTimer(const tstring & name, const bool paused)
{
	for(auto it : m_TimerContainer)
	{
		if(it.first == name)
		{
			it.second.SetPaused(paused);
			return;
		}
	}
}

void Stopwatch::SetCountingDownTimer(const tstring & name, const bool countingDown)
{
	for(auto it : m_TimerContainer)
	{
		if(it.first == name)
		{
			it.second.SetCountingDown(countingDown);
			return;
		}
	}
}

void Stopwatch::SetLoopTimer(const tstring & name, const bool looping)
{
	for(auto it : m_TimerContainer)
	{
		if(it.first == name)
		{
			it.second.SetLoop(looping);
			return;
		}
	}
}

void Stopwatch::ResetTimer(const tstring & name, const bool paused)
{
	for(auto it : m_TimerContainer)
	{
		if(it.first == name)
		{
			it.second.Reset(paused);
			return;
		}
	}
}

void Stopwatch::SetTargetTimeTimer(const tstring & name, const float targetTime, const bool reset, const bool paused)
{
	for(auto it : m_TimerContainer)
	{
		if(it.first == name)
		{
			it.second.SetTargetTime(paused);
			return;
		}
	}
}

void Stopwatch::SetFunctionTimer(const tstring & name, const std::function<void ()> func)
{
	for(auto it : m_TimerContainer)
	{
		if(it.first == name)
		{
			it.second.SetFunction(func);
			return;
		}
	}
}

int Stopwatch::GetTimerMinutes(const tstring & name) const
{
	for(auto it : m_TimerContainer)
	{
		if(it.first == name)
		{
			return it.second.GetCurrentTimeMinutes();
		}
	}
	return 0;
}

int Stopwatch::GetTimerSeconds(const tstring & name) const
{
	for(auto it : m_TimerContainer)
	{
		if(it.first == name)
		{
			return it.second.GetCurrentTimeSeconds();
		}
	}
	return 0;
}

int Stopwatch::GetTimerTotalSeconds(const tstring & name) const
{
	for(auto it : m_TimerContainer)
	{
		if(it.first == name)
		{
			return it.second.GetCurrentTimeTotalSeconds();
		}
	}
	return 0;
}