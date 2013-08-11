#pragma once

//====================== #INCLUDES ===================================
#include "IManager.h"
#include <map>
#include <memory>
//====================================================================

//====================== ParameterManager Class =====================
// Description:
//		A singleton implementation, to collect parameter collections.
// Last Modification: August 2013
// Glen De Cauwsemaecker
// www.glendc.com
//====================================================================

class Game;
class ParameterClass;

// Ancillary class, implementing the Singleton Design pattern
class ParameterManager : public IManager
{
public:
	~ParameterManager(void);

	static ParameterManager* GetInstance();

	void Initialize();
	void Update(GameContext& context);
	void Draw(GameContext& context);
	
	ParameterClass & CreateOrGet(const tstring & collection);

private:
	ParameterManager(void);
	static ParameterManager* m_pInstance;

	map<UINT, ParameterClass> m_Parameters;
	
	bool m_IsInitialized;

	// Disabling default copy constructor and default assignment operator.
	ParameterManager(const ParameterManager& t);
	ParameterManager& operator=(const ParameterManager& t);
};

