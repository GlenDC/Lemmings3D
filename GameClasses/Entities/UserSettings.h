#pragma once

//====================== #INCLUDES ===================================
#include "Helpers/stdafx.h"
#include "ParameterClass.h"
//====================================================================

//====================== UserSettings Class ==============
// Description:
//		User settings get auto saved and are linked to a player account
// Last Modification: 05/06/2013
// Copyright Glen De Cauwsemaecker
// www.glendc.com
//====================================================================

class Player;

class UserSettings
{
public:
	explicit UserSettings(Player * pPlayer);
	~UserSettings();
	void Refresh();
	

	template<typename T>
	T GetSetting(const tstring & name) const
	{
		ASSERT(m_pParameters != nullptr, _T("Parameters not loaded correctly!"));
		return m_pParameters->GetParameter<T>(name);
	}

	template<typename T>
	bool SetSetting(const tstring & name, const T & value)
	{
		ASSERT(m_pParameters != nullptr, _T("Parameters not loaded correctly!"));
		return m_pParameters->SetParameter<T>(name, value);
	}

	void SaveSettings();

private:
	void LoadSettings();

	ParameterClass * m_pParameters;
	Player *m_pPlayer;

	// -------------------------
	// Disabling default copy constructor and default 
	// assignment operator.
	// -------------------------
	UserSettings(const UserSettings& t);
	UserSettings& operator=(const UserSettings& t);
};