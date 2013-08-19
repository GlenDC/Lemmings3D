//====================== #INCLUDES ===================================
#include "ColissionCollector.h"
#include "Game.h"
#include "Stopwatch.h"
//--------------------------------------------------------------------
#include "OverlordComponents.h"
#include "../Entities/Level.h"
#include "../GameScenes/GameScreen.h"
#include "../GameObjects/PhysicsCube.h"
#include "../GameObjects/ColissionEntity.h"
#include "../Lib/GlobalParameters.h"
#include <future>
//====================================================================

ColissionCollector* ColissionCollector::m_pInstance = nullptr;

ColissionCollector::ColissionCollector(void)
	: m_CheckCounter(0)
	, m_IsInitialized(false)
	, m_RefreshAllowed(true)
	, m_Enabled(true)
	, m_ActiveList()
	, m_IdleList()
	, m_pLevel(nullptr)
	, m_pGameScene(nullptr)
	, m_CurrentCheckNumber(0)
	, m_FrontBatch(0)
	, m_ThreadAvailable(true)
	, m_SleepList(0)
{
}

ColissionCollector::~ColissionCollector(void)
{
	ClearEnvironment();
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
	for(UINT i = 0 ; i < m_ActiveList.size() ; ++i)
	{
		auto cube = m_ActiveList[i];
		if(!GenerateIdleEntityIfInvalid(cube->GetTranslation()))
		{
			RemovePhysicsCube(cube);
			m_ActiveList.erase(m_ActiveList.begin() + i);
		}
		else
		{
			++i;
		}
	}
	if(m_ThreadAvailable)
	{
		std::async(std::launch::async, UpdateList, context);
	}
}

// nothing to draw
void ColissionCollector::Draw(GameContext& context) {}

void ColissionCollector::AddUser(ColissionEntity * pUser)
{
	m_UserVec.push_back(pUser);
}

bool ColissionCollector::RemoveUser(ColissionEntity * pUser)
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
	if (m_pLevel && m_Enabled)
	{
		float size = GlobalParameters::GetParameters()->GetParameter<float>(_T("GRID_SIZE"));
		for(UINT i = 0 ; i < m_ActiveList.size() ; )
		{
			auto cube = m_ActiveList[i];
			if(!GenerateIdleEntityIfInvalid(cube->GetTranslation()))
			{
				RemovePhysicsCube(cube, false);
				m_ActiveList.erase(m_ActiveList.begin() + i);
			}
			else
			{
				++i;
			}
		}
	}
}

void ColissionCollector::RefreshCollection(const GameContext & context)
{
	RefreshColissionList(context);
}

void ColissionCollector::CopyEnvironment()
{
	const vector<D3DXVECTOR3> & vecPos = m_pLevel->GetEnvironment();
	for(auto & pos : vecPos)
	{
		AddEnvironment(pos);
	}
}

void ColissionCollector::ClearEnvironment()
{
	m_ActiveList.clear();
	m_IdleList.clear();
	m_SleepList.clear();
}

void ColissionCollector::UpdateIdleList(const GameContext & context)
{
	m_ThreadAvailable = false;
	for(UINT i = 0 ; i < m_IdleList.size() ; )
	{
		auto & entity = m_IdleList[i];
		entity.Timer -= context.GameTime.ElapsedSpeedGameTime;
		if(entity.Timer < 0)
		{
			AddEnvironment(entity.Position);
			m_IdleList.erase(m_IdleList.begin());
		}
		else
		{
			++i;
		}
	}
	m_ThreadAvailable = true;
}

void ColissionCollector::AddEnvironment(const D3DXVECTOR3 & pos)
{
	D3DXVECTOR3 min_col = GlobalParameters::GetParameters()->GetParameter<D3DXVECTOR3>(_T("AUTO_COLLISION_MIN"));
	D3DXVECTOR3 max_col = GlobalParameters::GetParameters()->GetParameter<D3DXVECTOR3>(_T("AUTO_COLLISION_MAX"));
	if(pos.x > min_col.x && pos.y > min_col.y && pos.z > min_col.z
		&& pos.x < max_col.x && pos.y < max_col.y && pos.z < max_col.z)
	{
		if(GenerateIdleEntityIfInvalid(pos))
		{
			float size = GlobalParameters::GetParameters()->GetParameter<float>(_T("GRID_SIZE"));
			PhysicsCube * pCube = new PhysicsCube(pos, size);
			m_pGameScene->AddObject(pCube);
			m_ActiveList.push_back(pCube);
		}
	}
	else
	{
		auto it = std::find(m_SleepList.begin(), m_SleepList.end(), pos);
		if(it == m_SleepList.end())
		{
			m_SleepList.push_back(pos);
		}
	}
}

void ColissionCollector::RemoveEnvironment(const D3DXVECTOR3 & pos)
{
	auto it = std::find_if(m_ActiveList.begin(), m_ActiveList.end(), [&] (const PhysicsCube * cube) 
	{
		return cube->GetTranslation() == pos;
	});
	if(it != m_ActiveList.end())
	{
		m_ActiveList.erase(it);
		RemovePhysicsCube(*it);
		return;
	}
	auto itIdle = std::find_if(m_IdleList.begin(), m_IdleList.end(), [&] (const IdleEntity & entity) 
	{
		return entity.Position == pos;
	});
	if(itIdle != m_IdleList.end())
	{
		m_IdleList.erase(itIdle);
		return;
	}
	auto itSleep = std::find_if(m_SleepList.begin(), m_SleepList.end(), [&] (const D3DXVECTOR3 & position)
	{
		return position == pos;
	});
	if(itSleep != m_SleepList.end())
	{
		m_SleepList.erase(itSleep);
	}
}

void ColissionCollector::Enable()
{
	m_Enabled = true;
	for(auto cube : m_ActiveList)
	{
		m_pGameScene->AddSceneObject(cube);
	}
}

void ColissionCollector::Disable()
{
	m_Enabled = false;
	for(auto cube : m_ActiveList)
	{
		RemovePhysicsCube(cube, false);
	}
}

void ColissionCollector::UpdateList(const GameContext & context)
{
	GetInstance()->UpdateIdleList(context);
}

bool ColissionCollector::IsValid(const D3DXVECTOR3 & pos)
{
	for(UINT u = 0 ; u < m_UserVec.size() ; ++u)
	{
		auto user = m_UserVec[u];
		D3DXVECTOR3 lengthVec = pos - user->GetTranslation();
		float length(D3DXVec3Length(&lengthVec));
		if(length < user->GetCollectionRange())
		{
			return true;
		}
	}
	return false;
}

bool ColissionCollector::GenerateIdleEntityIfInvalid(const D3DXVECTOR3 & pos)
{
	bool found(false);
	float size = GlobalParameters::GetParameters()->GetParameter<float>(_T("GRID_SIZE"));
	float min_2d_dis((float)START_VALUE), min_y_dis((float)START_VALUE), bonus_height(0); 
	D3DXVECTOR3 lengthVec(0,0,0), lengthVecY(0,0,0), lengthVec2D(0,0,0);
	for(UINT u = 0 ; u < m_UserVec.size() ; ++u)
	{
		auto user = m_UserVec[u];
		lengthVec = pos - user->GetTranslation();
		float length(D3DXVec3Length(&lengthVec));
		lengthVecY.y = lengthVec.y;
		float lengthY(D3DXVec3Length(&lengthVecY));
		if(!(length < user->GetCollectionRange() && lengthY < size))
		{
			// check for 2d_dis
			lengthVec2D = lengthVec;
			float length2D(D3DXVec3Length(&lengthVec2D));
			if(length2D < min_2d_dis)
			{
				min_2d_dis = length2D;
				min_y_dis = lengthY;
				if(user->GetTranslation().y < pos.y)
				{
					bonus_height = (min_y_dis / size) * 4;
				}
				else
				{
					bonus_height = 0;
				}
			}
		}
		else
		{
			found = true;
			break;
		}
	}
	if(!found)
	{
		IdleEntity entity;
		entity.Position = pos;
		if(min_y_dis > size || min_2d_dis > size * 6)
		{
			float time_2d(min_2d_dis / size), time_y(min_y_dis / size);
			if(time_2d > 5)
				bonus_height *= (time_2d / 5) * 2;
			entity.Timer = ( time_2d * 0.5f + time_y * 0.65f ) * bonus_height;
		}
		else
		{
			entity.Timer = 0;
		}
		m_IdleList.push_back(entity);
	}
	return found;
}

void ColissionCollector::RemovePhysicsCube(PhysicsCube * pCube, bool mark_for_delete)
{
	if(mark_for_delete)
	{
		m_pGameScene->RemoveObject(pCube);
	}
	else
	{
		m_pGameScene->ClearObject(pCube);
	}
	/*if(mark_for_delete)
	{	
		pCube->MarkForDelete();
	}*/
}