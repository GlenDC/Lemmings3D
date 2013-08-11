//====================== #INCLUDES ===================================
#include "LoadingScreen.h"
//--------------------------------------------------------------------
#include "../Managers/ScreenManager.h"
#include "../Managers/SpritefontManager.h"
#include "../UserInterface/UIDockInterface.h"
#include "../GameScenes/MainMenuScreen.h"
#include "../GameObjects/GameEntity.h"
#include "../UserInterface/UIDockInterface.h"
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
	, m_pUIDock(nullptr)
{
}


LoadingScreen::~LoadingScreen(void)
{
}

void LoadingScreen::Initialize()
{
	m_pSpriteFont = SpritefontManager::GetInstance()->CreateOrGet(_T("GameOver"), 35);

	m_pUIDock = new UIDockInterface(0, 0, 1400, 720, m_pSpriteFont, nullptr);
	m_pUIDock->AddSpritesheet(925, 485, _T("spritesheet_running"), _T("Spritesheet_running.png"), 6, 5, 1.0f);
	m_pUIDock->Initialize();

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
	m_pUIDock->Update(context);
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
	m_pUIDock->Draw(context);
	//SpriteBatch::DrawTextW(m_pSpriteFont.get(), strstr.str(), D3DXVECTOR2(1150, 675), D3DXCOLOR(1,1,1,1));
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