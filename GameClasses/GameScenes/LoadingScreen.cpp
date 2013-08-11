//====================== #INCLUDES ===================================
#include "LoadingScreen.h"
//--------------------------------------------------------------------
#include "../Managers/ScreenManager.h"
#include "../Managers/SpritefontManager.h"
#include "../UserInterface/UIDockInterface.h"
#include "../GameScenes/MainMenuScreen.h"
//--------------------------------------------------------------------
#include "Graphics/GraphicsDevice.h"
#include "Helpers/GeneralStructs.h"
#include "Managers/ContentManager.h"
#include "OverlordComponents.h"
#include "Scenegraph/GameObject.h"
//====================================================================

LoadingScreen::LoadingScreen(const tstring & previousScreen)
	: BaseScreen(_T("LoadingScreen"), _T("Lemmings3D Loading..."), false)
	, m_pSpriteFont(nullptr)
	, m_LoadTime(0)
	, m_RemovedPrevious(false)
	, m_PreviousScreenName(previousScreen)
{
}


LoadingScreen::~LoadingScreen(void)
{
}

void LoadingScreen::Initialize()
{
	m_pSpriteFont = SpritefontManager::GetInstance()->CreateOrGet(_T("GameOver"), 35);

	BaseScreen::Initialize();
}

void LoadingScreen::Update(const GameContext& context)
{
	m_LoadTime += context.GameTime.ElapsedSeconds();
	if(!m_RemovedPrevious)
	{
		m_RemovedPrevious = true;
		ScreenManager::GetInstance()->RemoveScreen(m_PreviousScreenName);
	}
	BaseScreen::Update(context);
}

void LoadingScreen::Draw(const GameContext& context)
{
	UINT dotTime = UINT(m_LoadTime) % MAX_DOTS;
	++dotTime;
	tstringstream strstr;
	strstr << _T("Loading");
	for(unsigned int i = 0 ; i < dotTime ; ++i)
	{
		strstr << _T(".");
	}
	SpriteBatch::DrawTextW(m_pSpriteFont.get(), strstr.str(), D3DXVECTOR2(1150, 675), D3DXCOLOR(1,1,1,1));
	BaseScreen::Draw(context);
}

void LoadingScreen::BeginControl()
{

}

void LoadingScreen::EndControl()
{

}

void LoadingScreen::Activated()
{
}

void LoadingScreen::Deactivated()
{
}