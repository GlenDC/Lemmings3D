//====================== #INCLUDES ===================================
#include "StatusReport.h"
//--------------------------------------------------------------------
#include "Helpers/GeneralStructs.h"
//--------------------------------------------------------------------
#include "../Lib/GlobalParameters.h"
#include "../Lib/LemmingsHelpers.h"
#include "../Managers/Stopwatch.h"
#include "../GameScenes/GameScreen.h"
//====================================================================

StatusReport::StatusReport(GameScreen * pScreen, const bool save_log)
	: m_StatusQueue()
	, m_SaveLog(save_log)
	, m_AllowBroadcast(true)
	, m_CurrentTime(0)
	, m_TotalTime(0)
	, m_pGameScreen(pScreen)
{

}

StatusReport::~StatusReport()
{
	m_pGameScreen = nullptr;
	if(m_SaveLog)
	{
		//Save log to textfile
		LogFile();
	}
}

void StatusReport::Update(const GameContext & context)
{
	m_TotalTime += context.GameTime.ElapsedSpeedGameTime;
	m_CurrentTime = LemmingsHelpers::fRound(m_TotalTime,1);
	
	if(context.GameTime.ElapsedSpeedGameTime < 0)
	{
		auto it = m_StatusLog.find(m_CurrentTime);
		if(it != m_StatusLog.end())
		{
			//broadcast old message, if it excists!
			m_pGameScreen->BroadCast(it->second);
		}
	}
	else if(m_AllowBroadcast)
	{
		//Broadcast
		bool ok(false), reset(true);
		float maxDelay = GlobalParameters::GetParameters()->GetParameter<float>(_T("MAX_LOG_DELAY_TIME"));
		do
		{
			if(m_StatusQueue.size() == 0)
			{
				ok = true;
				reset = false;
			}
			else
			{
				if(context.GameTime.TotalSeconds() - m_StatusQueue.front().Time > maxDelay)
				{
					m_StatusQueue.pop();
					ok = false;
				}
				else
				{
					m_pGameScreen->BroadCast(m_StatusQueue.front().Message);
					m_StatusQueue.pop();
					ok = true;
					reset = true;
				}
			}
		} while(!ok);
		//Disable broadcasting a new message for the next LOG_WAIT_TIME" 
		if(reset)
		{
			m_AllowBroadcast = false;
			Stopwatch::GetInstance()->CreateTimer(_T("AllowBroadcast"), 
				GlobalParameters::GetParameters()->GetParameter<float>(_T("LOG_WAIT_TIME")), 
				false, false, [&] () { m_AllowBroadcast = true; });
		}
	}
}

void StatusReport::ReportStatus(const tstring & status)
{
	StatusStruct report;
	report.Time = m_CurrentTime;
	report.Message = status;
	m_StatusQueue.push(report);
	m_StatusLog.insert(std::pair<float, tstring>(m_CurrentTime, status));
}

void StatusReport::LogFile() const
{
	//m_StatusLog
	tofstream log;
	log.open (_T("Logs/Lemmings3D Status Log ") + LemmingsHelpers::GetFullTimeString() + _T(".log"), ios::trunc);
	log << _T("==================== Lemmings3D Log File =============================\n");
	log << _T("===== Developed by Glen De Cauwsemaecker @ www.glendc.com\n");
	log << _T("===== Log Session: ") << LemmingsHelpers::GetFullTimeString() << std::endl << std::endl;
	for(auto status : m_StatusLog)
	{
		int time = (int)status.first;
		int seconds = time % 60;
		int minutes = time / 60;
		int hours = time / 3600;
		log << _T("[") << (hours < 10 ? _T("0") : _T("")) << hours << _T(":") 
			<< (minutes < 10 ? _T("0") : _T("")) << minutes << _T(":") 
			<< (seconds < 10 ? _T("0") : _T("")) << seconds << _T("] ") 
			<< status.second << std::endl;
	}
	log.close();
}