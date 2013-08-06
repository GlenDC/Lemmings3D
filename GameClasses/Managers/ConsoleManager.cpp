//====================== #INCLUDES ===================================
#include "ConsoleManager.h"
#include "Game.h"
//--------------------------------------------------------------------
#include <algorithm>
//====================================================================

ConsoleManager* ConsoleManager::m_pInstance = nullptr;

// private constructor
ConsoleManager::ConsoleManager(void)
	: m_IsInitialized(false)
{
}

// public destructor
ConsoleManager::~ConsoleManager(void)
{
}

// receive a poiner to the object, 
// and create it first if the object isn't created yet.
ConsoleManager* ConsoleManager::GetInstance()
{
	if (m_pInstance == nullptr)
	{
		m_pInstance = new ConsoleManager();
	}

	return m_pInstance;
}

// initialize the console manager only once per session.
void ConsoleManager::Initialize()
{
	if(!m_IsInitialized) 
	{
		// initialize nothing
		m_IsInitialized = true;
	}
}

// update nothing
void ConsoleManager::Update(GameContext& context) {}

// draw nothing
void ConsoleManager::Draw(GameContext& context) {}