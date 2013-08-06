#pragma once

//====================== #INCLUDES ===================================
#include "IManager.h"
#include <vector>
//====================================================================

//====================== ConsoleManager Class =========================
// Description:
//		Catch input commands and excecute the function if possible
//		return warnings if syntax is wrong, else return return value
// Last Modification: July 2013
// Glen De Cauwsemaecker
// www.glendc.com
//====================================================================

class Game;

// Ancillary class, implementing the Singleton Design pattern
class ConsoleManager : public IManager
{
public:
	~ConsoleManager(void);

	static ConsoleManager* GetInstance();

	void Initialize();
	void Update(GameContext& context);
	void Draw(GameContext& context);

private:
	ConsoleManager(void);
	static ConsoleManager* m_pInstance;
	
	bool m_IsInitialized;

	// Disabling default copy constructor and default assignment operator.
	ConsoleManager(const ConsoleManager& t);
	ConsoleManager& operator=(const ConsoleManager& t);
};

