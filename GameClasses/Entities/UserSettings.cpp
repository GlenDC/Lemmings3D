#include "UserSettings.h"
#include "Player.h"

UserSettings::UserSettings(Player * pPlayer)
	: m_pPlayer(pPlayer)
{
	LoadSettings();
}

UserSettings::~UserSettings()
{
	m_pPlayer = nullptr;
}

void UserSettings::Refresh()
{
	if(m_pParameters == nullptr)
	{
		LoadSettings();
	}
	m_pParameters->Refresh();
}

void UserSettings::SaveSettings()
{
	m_pParameters->Save();
}

void UserSettings::LoadSettings()
{
	ASSERT(m_pPlayer != nullptr, _T("Create a player before trying to load the user settings."));
	m_pParameters = new ParameterClass(_T("Settings_") + m_pPlayer->GetName());
}