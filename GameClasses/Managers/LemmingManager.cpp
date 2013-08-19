//====================== #INCLUDES ===================================
#include "LemmingManager.h"
#include "Game.h"
#include "../GameObjects/LemmingAI.h"
#include "Scenegraph/GameScene.h"
//--------------------------------------------------------------------
#include <algorithm>
//====================================================================

LemmingManager* LemmingManager::m_pInstance = nullptr;

// private constructor
LemmingManager::LemmingManager(void)
	: m_IsInitialized(false)
	, m_pGameScene(nullptr)
	, m_Lemmings(0)
{
}

// public destructor
LemmingManager::~LemmingManager(void)
{
}

// receive a poiner to the object, 
// and create it first if the object isn't created yet.
LemmingManager* LemmingManager::GetInstance()
{
	if (m_pInstance == nullptr)
	{
		m_pInstance = new LemmingManager();
	}

	return m_pInstance;
}

// initialize the console manager only once per session.
void LemmingManager::Initialize()
{
	if(!m_IsInitialized) 
	{
		// initialize nothing
		m_IsInitialized = true;
	}
}

// update nothing
void LemmingManager::Update(GameContext& context) {}

// draw nothing
void LemmingManager::Draw(GameContext& context) {}

void LemmingManager::CreateLemming(const D3DXVECTOR3 & pos)
{
	ASSERT(m_pGameScene != nullptr, _T("Set the correct gamescene before spawning a lemming."));
	LemmingAI * lemming = new LemmingAI();
	lemming->Translate(pos);
	m_pGameScene->AddSceneObject(lemming);
	lemming->Initialize();
	m_Lemmings.push_back(lemming);
}