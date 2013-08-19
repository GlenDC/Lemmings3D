#pragma once

//====================== #INCLUDES ===================================
#include "IManager.h"
#include <vector>
#include <memory>
#include <thread>
//====================================================================

//====================== ColissionCollector Class =========================
// Description:
//		Collect colission on a dynamic way around all the entities that need this!
// Last Modification: August 2013
// Glen De Cauwsemaecker
// www.glendc.com
//====================================================================

class Game;
class GameScreen;
class ColissionEntity;
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

	void AddUser(ColissionEntity * pUser);
	bool RemoveUser(ColissionEntity * pUser);

	void RefreshColissionList(const GameContext & context);
	void RefreshCollection(const GameContext & context);

	void SetLevel(shared_ptr<Level> pLevel) { m_pLevel = pLevel; }
	void SetGameScreen(GameScreen * pGameScreen) { m_pGameScene = pGameScreen; }

	void CopyEnvironment();
	void ClearEnvironment();

	void UpdateIdleList(const GameContext & context);

	void AddEnvironment(const D3DXVECTOR3 & pos);
	void RemoveEnvironment(const D3DXVECTOR3 & pos);

	void Enable();
	void Disable();

	static void UpdateList(const GameContext & context);

private:
	struct IdleEntity
	{
		D3DXVECTOR3 Position;
		float Timer;
	};

	ColissionCollector(void);

	bool IsValid(const D3DXVECTOR3 & pos);
	bool GenerateIdleEntityIfInvalid(const D3DXVECTOR3 & pos);

	void RemovePhysicsCube(PhysicsCube * pCube, bool mark_for_delete = true);

	static ColissionCollector* m_pInstance;
	static const int START_VALUE = 9999;

	static const UINT MAX_CHECK_COUNT = 2000;
	UINT m_CheckCounter;
	bool m_ThreadAvailable;

	bool m_IsInitialized, m_RefreshAllowed;
	bool m_Enabled;

	std::vector<D3DXVECTOR3> m_SleepList;
	std::vector<IdleEntity>  m_IdleList;
	std::vector<PhysicsCube*> m_ActiveList;
	std::vector<ColissionEntity*> m_UserVec;

	shared_ptr<Level> m_pLevel;
	GameScreen * m_pGameScene;

	int m_CurrentCheckNumber;
	UINT m_FrontBatch;

	// Disabling default copy constructor and default assignment operator.
	ColissionCollector(const ColissionCollector& t);
	ColissionCollector& operator=(const ColissionCollector& t);
};

