//========================================= INCLUDES ==========================================
#include "DemoModeBase.h"
//---------------------------------------------------------------------------------------------
#include "..\..\Managers\SpritefontManager.h"
#include "..\..\UserInterface\UIDockInterface.h"
//=============================================================================================

DemoModeBase::DemoModeBase(const tstring & title, const tstring & description)
	: State()
	, m_pDescriptionDock(nullptr)
	, m_pDefaultFont(nullptr)
{
	m_pDefaultFont = SpritefontManager::GetInstance()->CreateOrGet(_T("GameOver"));

	m_pDescriptionDock = new UIDockInterface(180, 100, 1000, 100, m_pDefaultFont, nullptr);
	m_pDescriptionDock->AddTextField(5,5,1000,25, _T("txt_title"), title, D3DXCOLOR(1,1,0,1));
	m_pDescriptionDock->AddTextField(5,30,1000,50, _T("txt_description"), description, D3DXCOLOR(0.65f,0.65f,0.65f,1));
	m_pDescriptionDock->Initialize();
}

DemoModeBase::~DemoModeBase(void)
{
	SafeDelete(m_pDescriptionDock);
}

void DemoModeBase::Update(const GameContext& context)
{
	m_pDescriptionDock->Update(context);
}

void DemoModeBase::Draw2D(const GameContext& context)
{
	m_pDescriptionDock->Draw(context);
}