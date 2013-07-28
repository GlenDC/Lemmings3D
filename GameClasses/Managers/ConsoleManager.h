#pragma once

//====================== #INCLUDES ===================================
#include "ManagerInterface.h"
#include <vector>
//====================================================================

//====================== ConsoleManager Class =========================
// Description:
//		Catch input commands and excecute the function if possible
//		return warnings if syntax is wrong, else return return value
// Last Modification: 22/03/2013
// Copyright Glen De Cauwsemaecker
// www.glendc.com
//====================================================================

class Game;

class ConsoleManager : public ManagerInterface
{
public:
	~ConsoleManager(void);

	static ConsoleManager* GetInstance()
	{
		if (m_pInstance == nullptr)
			m_pInstance = new ConsoleManager();

		return m_pInstance;
	}

	virtual void Initialize();
	virtual void Update(GameContext& context);
	virtual void Draw(GameContext& context);

	/*template <typename R, typename O>
	void Add_Function_0(R (*functionPtr)(O* sourcePtr));*/

private:
	ConsoleManager(void);
	static ConsoleManager* m_pInstance;
	
	bool m_IsInitialized;

private:
	// -------------------------
	// Disabling default copy constructor and default 
	// assignment operator.
	// -------------------------
	//template <typename R, typename O>
	//std::vector<R (*)(O*)> m_FunctionList_0;
	///*template <typename R, typename T>
	//std::vector<std::function<R (T)> m_FunctionList_1;*/

	ConsoleManager(const ConsoleManager& t);
	ConsoleManager& operator=(const ConsoleManager& t);
};

