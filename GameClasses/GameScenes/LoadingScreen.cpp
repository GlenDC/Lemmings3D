//====================== #INCLUDES ===================================
#include "LoadingScreen.h"
//--------------------------------------------------------------------
#include "../Managers/ScreenManager.h"
#include "../Managers/SpritefontManager.h"
#include "../UserInterface/UIDockInterface.h"
#include "../GameScenes/MainMenuScreen.h"
#include "../GameObjects/GameEntity.h"
#include "../UserInterface/UIDockInterface.h"
#include "../Managers/ParameterManager.h"
#include "../Entities/ParameterClass.h"
#include "../XML/XMLConverter.h"
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
	, m_LoadingDescription()
	, m_TipID()
	, m_pUIDock(nullptr)
{
	auto & container =  ParameterManager::GetInstance()->CreateOrGet(_T("Tips"));
	UINT tips_count = container.GetParameter<UINT>(_T("COUNT"));
	UINT random_tip_id = rand() % tips_count;
	m_TipID = XMLConverter::ConvertToTString(random_tip_id);
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
	SpriteBatch::DrawTextW(m_pSpriteFont.get(), strstr.str(), D3DXVECTOR2(1150, 675), D3DXCOLOR(1,1,1,1));
	UINT hor_offset = m_pSpriteFont->GetMetric('A').Width * m_LoadingDescription.size();
	float center(660.0f);
	SpriteBatch::DrawTextW(m_pSpriteFont.get(), m_LoadingDescription, D3DXVECTOR2(center - ( hor_offset / 2 ), 365), D3DXCOLOR(1,1,0,1));
	
	strstr.str(_T(""));
	auto & container =  ParameterManager::GetInstance()->CreateOrGet(_T("Tips"));
	strstr << _T("tip: ") << container.GetParameter<tstring>(m_TipID);
	UINT hor_tip_offset = m_pSpriteFont->GetMetric('h').Width * strstr.str().size();
	SpriteBatch::DrawTextW(m_pSpriteFont.get(), strstr.str(), D3DXVECTOR2(center - ( hor_tip_offset / 2 ), 395), D3DXCOLOR(1,1,0,0.5f));

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

void LoadingScreen::SetLoadingDescription(const tstring & description)
{
	m_LoadingDescription = description;
}