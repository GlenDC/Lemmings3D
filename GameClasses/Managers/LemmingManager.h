#pragma once

//====================== #INCLUDES ===================================
#include "IManager.h"
#include <vector>
//====================================================================

class LemmingAI;
class GameScene;

//====================== LemmingManager Class =========================
// Description:
//		Manages the Lemmings controlled by AI.
// Last Modification: August 2013
// Glen De Cauwsemaecker
// www.glendc.com
//====================================================================

class Game;

// Ancillary class, implementing the Singleton Design pattern
class LemmingManager : public IManager
{
public:
	~LemmingManager(void);

	static LemmingManager* GetInstance();

	void Initialize();
	void Update(GameContext& context);
	void Draw(GameContext& context);

	void CreateLemming(const D3DXVECTOR3 & pos);
	void SetGameScene(GameScene * scene) { m_pGameScene = scene; }

private:
	LemmingManager(void);
	static LemmingManager* m_pInstance;

	GameScene * m_pGameScene;
	std::vector<LemmingAI*> m_Lemmings;

	bool m_IsInitialized;

	// Disabling default copy constructor and default assignment operator.
	LemmingManager(const LemmingManager& t);
	LemmingManager& operator=(const LemmingManager& t);
};

