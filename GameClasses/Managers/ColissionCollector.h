#pragma once

//====================== #INCLUDES ===================================
#include "ManagerInterface.h"
#include <vector>
//====================================================================

//====================== ColissionCollector Class =========================
// Description:
//		Collect colission on a dynamic way around all the entities that need this!
// Last Modification: 09/06/2013
// Copyright Glen De Cauwsemaecker
// www.glendc.com
//====================================================================

class Game;
class IColissionUser;
class Level;
class PhysicsCube;
class GameScreen;

class ColissionCollector : public ManagerInterface
{
public:
	~ColissionCollector(void);

	static ColissionCollector* GetInstance()
	{
		if (m_pInstance == nullptr)
			m_pInstance = new ColissionCollector();

		return m_pInstance;
	}

	virtual void Initialize();
	virtual void Update(GameContext& context);
	void RefreshCollection(const GameContext & context);
	virtual void Draw(GameContext& context);

	void AddUser(IColissionUser * pUser);
	bool RemoveUser(IColissionUser * pUser);

	void SetLevel(Level * pLevel) { m_pLevel = pLevel; }
	void SetGameScreen(GameScreen *pGameScreen) { m_pGameScene = pGameScreen; }

	void RefreshColissionList(const GameContext & context);

private:
	ColissionCollector(void);
	static ColissionCollector* m_pInstance;

	
	bool m_IsInitialized;

	std::vector<IColissionUser*> m_UserVec;
	std::vector<PhysicsCube*> m_CubeVec[2];

	Level * m_pLevel;
	GameScreen *m_pGameScene;

	int m_CurrentCheckNumber;
	UINT m_FrontBatch;

	bool m_RefreshAllowed;

private:
	// -------------------------
	// Disabling default copy constructor and default 
	// assignment operator.
	// -------------------------
	ColissionCollector(const ColissionCollector& t);
	ColissionCollector& operator=(const ColissionCollector& t);
};

