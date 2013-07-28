#pragma once

//====================== #INCLUDES ===================================
#include "Helpers/stdafx.h" 
#include <queue>
#include <map>
//====================================================================

//====================== StatusReport Class ==============
// Description:
//		User settings get auto saved and are linked to a player account
// Last Modification: 05/06/2013
// Copyright Glen De Cauwsemaecker
// www.glendc.com
//====================================================================

struct GameContext;
class GameScreen;

class StatusReport
{
public:
	explicit StatusReport(GameScreen * pGame, bool save_log);
	~StatusReport();

	void Update(const GameContext & context);

	void ReportStatus(const tstring & status);

private:
	struct StatusStruct
	{
		float Time;
		tstring Message;
	};

	std::queue<StatusStruct> m_StatusQueue;
	std::multimap<float, tstring> m_StatusLog;

	bool m_SaveLog;
	bool m_AllowBroadcast;

	float m_CurrentTime;
	float m_TotalTime;

	GameScreen * m_pGameScreen;

	void LogFile() const;

	// -------------------------
	// Disabling default copy constructor and default 
	// assignment operator.
	// -------------------------
	StatusReport(const StatusReport& t);
	StatusReport& operator=(const StatusReport& t);
};