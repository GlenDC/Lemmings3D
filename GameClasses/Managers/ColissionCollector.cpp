//====================== #INCLUDES ===================================
#include "ColissionCollector.h"
#include "Game.h"
#include "Stopwatch.h"
//--------------------------------------------------------------------
#include "../Entities/Level.h"
#include "../GameScenes/GameScreen.h"
#include "../GameObjects/PhysicsCube.h"
#include "../Interfaces/IColissionUser.h"
#include "../Lib/GlobalParameters.h"
//====================================================================

ColissionCollector* ColissionCollector::m_pInstance = nullptr;

ColissionCollector::ColissionCollector(void)
	: m_IsInitialized(false)
	, m_RefreshAllowed(true)
	, m_pLevel(nullptr)
	, m_pGameScene(nullptr)
	, m_CurrentCheckNumber(0)
	, m_FrontBatch(0)
{
}

ColissionCollector::~ColissionCollector(void)
{
}

ColissionCollector* ColissionCollector::GetInstance()
{
	if (m_pInstance == nullptr)
	{
		m_pInstance = new ColissionCollector();
	}

	return m_pInstance;
}

void ColissionCollector::Initialize()
{
	if(m_IsInitialized == false)
	{
		m_IsInitialized = true;
	}
}

void ColissionCollector::Update(GameContext& context)
{
	for(UINT i = 0 ; i < m_CubeVec[0].size() ; ++i)
	{
		m_CubeVec[0][i]->Update(context);
	}
}

// nothing to draw
void ColissionCollector::Draw(GameContext& context) {}

void ColissionCollector::AddUser(IColissionUser * pUser)
{
	m_UserVec.push_back(pUser);
}

bool ColissionCollector::RemoveUser(IColissionUser * pUser)
{
	for(UINT i = 0 ; i < m_UserVec.size() ; ++i)
	{
		if(m_UserVec[i] == pUser)
		{
			m_UserVec.erase(m_UserVec.begin() + i);
			return true;
		}
	}
	return false;
}

void ColissionCollector::RefreshColissionList(const GameContext & context)
{
	/*if(m_RefreshAllowed)
	{*/
		float size = GlobalParameters::GetParameters()->GetParameter<float>(_T("GRID_SIZE"));
		if(m_CurrentCheckNumber == 0)
		{
			for(UINT i = 0 ; i < m_CubeVec[0].size() ; ++i)
			{
				m_pGameScene->RemoveSceneObject(m_CubeVec[0][i]);
			}
			m_CubeVec[0].resize(0);
			for(UINT i = 0 ; i < m_CubeVec[1].size() ; ++i)
			{
				m_CubeVec[0].push_back(m_CubeVec[1][i]);
			}
			m_CubeVec[1].resize(0);
		}

		if (m_pLevel)
		{
			const vector<D3DXVECTOR3> & vecPos = m_pLevel->GetEnvironment();
	
			int newBatch = (int)(vecPos.size() * (context.GameTime.ElapsedSeconds() / 4.0f));

			for(int i = m_CurrentCheckNumber ; i < m_CurrentCheckNumber + newBatch && (UINT)i < vecPos.size() ; ++i)
			{
				for(UINT u = 0 ; u < m_UserVec.size() ; ++u)
				{
					D3DXVECTOR3 lengthVec = vecPos[i] - m_UserVec[u]->GetCUPosition();
					float length(D3DXVec3Length(&lengthVec));
					if(length < m_UserVec[u]->GetCURange())
					{
						PhysicsCube * cube = new PhysicsCube(vecPos[i], size);
						m_pGameScene->AddSceneObject(cube);
						cube->Initialize();
						m_CubeVec[1].push_back(cube);
						break;
					}
				}
			}

			m_CurrentCheckNumber += newBatch;
			if((UINT)m_CurrentCheckNumber > vecPos.size())
				m_CurrentCheckNumber = 0;
		}
		/*m_RefreshAllowed = false;
	}*/
}

void ColissionCollector::RefreshCollection(const GameContext & context)
{
	RefreshColissionList(context);
}