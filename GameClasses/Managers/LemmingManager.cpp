//====================== #INCLUDES ===================================
#include "LemmingManager.h"
#include "Game.h"
#include "../GameObjects/LemmingAI.h"
#include "Scenegraph/GameScene.h"
//--------------------------------------------------------------------
#include <algorithm>
#include "ColissionCollector.h"
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

void LemmingManager::DeleteLemming(LemmingAI* lemming)
{
	auto it = std::find(m_Lemmings.begin(), m_Lemmings.end(), lemming);
	if(it != m_Lemmings.end())
	{
		m_Lemmings.erase(it);
		ColissionCollector::GetInstance()->RemoveUser(lemming);
		lemming->Translate(-9999,-9999,-9999);
		//todo delete...
		//m_pGameScene->RemoveSceneObject(lemming);
	}
}