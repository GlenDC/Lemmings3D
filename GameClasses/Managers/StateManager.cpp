//========================= INCLUDES ==================================
#include "StateManager.h" 
//---------------------------------------------------------------------
#include "../Entities/State.h"
#include "../Lib/LemmingsHelpers.h"
//=====================================================================

StateManager::StateManager(void)
	: m_States()
	, m_pCurrentState(nullptr)
	, m_CurrentStateName()
{

}

StateManager::~StateManager(void)
{
	Clear();
}

void StateManager::Initialize()
{
	// do nothing, sad story of one interface
}

void StateManager::Update(const GameContext& context)
{
	if(m_pCurrentState != nullptr)
	{
		m_pCurrentState->Update(context);
	}
}

void StateManager::Draw(const GameContext& context)
{
	if(m_pCurrentState != nullptr)
	{
		m_pCurrentState->Draw(context);
	}
}

void StateManager::Draw2D(const GameContext& context)
{
	if(m_pCurrentState != nullptr)
	{
		m_pCurrentState->Draw2D(context);
	}
}


void StateManager::AddState(const tstring & name, State * pState)
{
	UINT id = LemmingsHelpers::GenerateHash(name);
	m_States[id] = pState;
	if(m_States.size() == 1)
	{
		m_pCurrentState = pState;
		m_CurrentStateName = name;
	}
}

bool StateManager::RemoveState(const tstring & name)
{
	if(m_CurrentStateName == name)
	{
		DeactiveCurrentState();
	}
	UINT id = LemmingsHelpers::GenerateHash(name);
	auto it = m_States.find(id);
	if(it != m_States.end())
	{
		m_States.erase(it);
		return true;
	}
	return false;
}

void StateManager::Clear()
{
	DeactiveCurrentState();
	for ( auto pair : m_States ) 
	{
		SafeDelete(pair.second);
	}
	m_States.clear();
	m_pCurrentState = nullptr;
}

void StateManager::SetState(const tstring & name)
{
	DeactiveCurrentState();
	UINT id = LemmingsHelpers::GenerateHash(name);
	// suggestion ... try catch? 
	m_pCurrentState = m_States[id];
	m_pCurrentState->Activate();
}

void StateManager::DeactiveCurrentState()
{
	if(m_pCurrentState != nullptr)
	{
		m_pCurrentState->Deactivate();
		m_pCurrentState = nullptr;
	}
}
