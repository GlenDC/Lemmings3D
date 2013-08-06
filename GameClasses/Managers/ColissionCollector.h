#pragma once

//====================== #INCLUDES ===================================
#include "IManager.h"
#include <vector>
#include <memory>
//====================================================================

//====================== ColissionCollector Class =========================
// Description:
//		Collect colission on a dynamic way around all the entities that need this!
// Last Modification: July 2013
// Glen De Cauwsemaecker
// www.glendc.com
//====================================================================

class Game;
class GameScreen;
class IColissionUser;
class Level;
class PhysicsCube;

// Ancillary class, implementing the Singleton Design pattern
class ColissionCollector : public IManager
{
public:
	~ColissionCollector(void);

	static ColissionCollector* GetInstance();

	virtual void Initialize();
	virtual void Update(GameContext& context);
	virtual void Draw(GameContext& context);

	void AddUser(IColissionUser * pUser);
	bool RemoveUser(IColissionUser * pUser);

	void RefreshColissionList(const GameContext & context);
	void RefreshCollection(const GameContext & context);

	void SetLevel(shared_ptr<Level> pLevel) { m_pLevel = pLevel; }
	void SetGameScreen(GameScreen * pGameScreen) { m_pGameScene = pGameScreen; }


private:
	ColissionCollector(void);
	static ColissionCollector* m_pInstance;

	bool m_IsInitialized, m_RefreshAllowed;

	std::vector<IColissionUser*> m_UserVec;
	std::vector<PhysicsCube*> m_CubeVec[2];

	shared_ptr<Level> m_pLevel;
	GameScreen * m_pGameScene;

	int m_CurrentCheckNumber;
	UINT m_FrontBatch;

	// Disabling default copy constructor and default assignment operator.
	ColissionCollector(const ColissionCollector& t);
	ColissionCollector& operator=(const ColissionCollector& t);
};

