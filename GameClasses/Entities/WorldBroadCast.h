#pragma once

//====================== #INCLUDES ===================================
#include "Helpers/stdafx.h" 
#include "Helpers/D3DUtil.h"
#include <queue>
#include <map>
#include "Helpers/GeneralStructs.h"
#include <memory>
//====================================================================

class SpriteFont;

//====================== WorldBroadCast Class ==========================
// Description:
//		broadcast messages on screen
// Last Modification: August 2013
// Glen De Cauwsemaecker
// www.glendc.com
//====================================================================

class WorldBroadCast
{
public:
	static WorldBroadCast * GetInstance();
	~WorldBroadCast();

	void Update(const GameContext & context);
	void Draw(const GameContext & context);
	void Send(const tstring & status);

	void SetOrigin(const D3DXVECTOR2 & origin);
	void Clear();

private:
	WorldBroadCast();
	static WorldBroadCast * m_pBroadCast;
	static const float BROADCAST_TIME;
	static const float TEXT_OFFSET;
	static const UINT MAX_MESSAGES = 10;

	D3DXVECTOR2 m_Origin;

	struct BroadCast
	{
		tstring Text;
		float Time;
		float Alpha;
	};

	std::vector<BroadCast> m_Broadcasts;
	std::shared_ptr<SpriteFont> m_Font;

	// Disabling default copy constructor and default assignment operator.
	WorldBroadCast(const WorldBroadCast& t);
	WorldBroadCast& operator=(const WorldBroadCast& t);
};