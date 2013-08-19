//========================================= INCLUDES ==================================
#include "WorldBroadCast.h"
//-------------------------------------------------------------------------------------
#include "..\Managers\SpritefontManager.h"
//-------------------------------------------------------------------------------------
#include "Graphics\SpriteBatch.h"
//=====================================================================================

WorldBroadCast * WorldBroadCast::m_pBroadCast = nullptr;
const float WorldBroadCast::BROADCAST_TIME = 10.0f;
const float WorldBroadCast::TEXT_OFFSET = 25.0f;

WorldBroadCast * WorldBroadCast::GetInstance()
{
	if(m_pBroadCast == nullptr)
	{
		m_pBroadCast = new WorldBroadCast();
	}
	return m_pBroadCast;
}

WorldBroadCast::WorldBroadCast()
	: m_Origin (0,0)
	, m_Broadcasts (0)
{
	m_Font = SpritefontManager::GetInstance()->CreateOrGet(_T("GameOver"));
}

WorldBroadCast::~WorldBroadCast()
{

}

void WorldBroadCast::Update(const GameContext & context)
{
	for(UINT i = 0 ; i < m_Broadcasts.size() ; )
	{
		auto & broadcast = m_Broadcasts[i];
		broadcast.Time -= context.GameTime.ElapsedSeconds();
		if(broadcast.Time < 0)
		{
			broadcast.Alpha -= context.GameTime.ElapsedSeconds() * 2;
			if(broadcast.Alpha < 0)
			{
				m_Broadcasts.erase(m_Broadcasts.begin() + i);
			}
			else
			{
				++i;
			}
		}
		++i;
	}
}

void WorldBroadCast::Draw(const GameContext & context)
{
	D3DXVECTOR2 origin = m_Origin;
	origin.y += m_Broadcasts.size() * TEXT_OFFSET;
	for(UINT i = 0 ; i < m_Broadcasts.size() ; ++i)
	{
		auto & broadcast = m_Broadcasts[i];
		SpriteBatch::DrawText(
			m_Font.get(),
			broadcast.Text,
			origin - D3DXVECTOR2(0, i * TEXT_OFFSET),
			D3DXCOLOR(1,1,1,broadcast.Alpha)
			);
	}
}

void WorldBroadCast::Send(const tstring & status)
{
	BroadCast broad_cast;
	broad_cast.Time = BROADCAST_TIME;
	broad_cast.Alpha = 1.0f;
	broad_cast.Text = status;
	m_Broadcasts.push_back(broad_cast);
	if(m_Broadcasts.size() > MAX_MESSAGES)
	{
		m_Broadcasts.erase(m_Broadcasts.begin());
	}
}

void WorldBroadCast::SetOrigin(const D3DXVECTOR2 & origin)
{
	m_Origin = origin;
}

void WorldBroadCast::Clear()
{
	m_Broadcasts.clear();
}