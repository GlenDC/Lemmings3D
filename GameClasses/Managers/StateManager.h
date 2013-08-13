#pragma once

//====================== #INCLUDES ===================================
#include "IManager.h"
#include <map>
//====================================================================

//====================== StateManager Class =========================
// Description:
//		Acts as a state machine, where each state can draw and update stuff.
//		Every state is represented by a child class of the Abstract State class.
// Last Modification: August 2013
// Glen De Cauwsemaecker
// www.glendc.com
//====================================================================

class State;

// Ancillary class, implementing the Singleton Design pattern
class StateManager
{
public:
	StateManager(void);
	~StateManager(void);

	void Initialize();
	void Update(const GameContext& context);
	void Draw(const GameContext& context);
	void Draw2D(const GameContext& context);

	void AddState(const tstring & name, State * pState);
	bool RemoveState(const tstring & name);
	void Clear();

	void SetState(const tstring & name);

private:
	void DeactiveCurrentState();

	std::map<UINT, State*> m_States;
	State * m_pCurrentState;
	tstring m_CurrentStateName;

	// Disabling default copy constructor and default assignment operator.
	StateManager(const StateManager& t);
	StateManager& operator=(const StateManager& t);
};
