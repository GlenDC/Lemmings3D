//====================== #INCLUDES ===================================
#include "UILevelButton.h" 
#include "../Managers/SpritefontManager.h"
#include "../Lib/LemmingsHelpers.h"
#include "../UserInterface/UIDockInterface.h"
//====================================================================

UILevelButton::UILevelButton(const int x, const int y, const tstring & name, const UIDockInterface * pParrent,
		const tstring & level_name, const tstring & button_image, const UINT level_id, const UINT highscore, const UINT best_time, function<void()> select_function)
    : UIElement(x, y, 327, 255, name, pParrent)
	, m_LevelName(level_name)
	, m_LevelID(level_id)
	, m_Highscore(highscore)
	, m_BestTime(best_time)
{

	m_pDock = new UIDockInterface(x, y, 327, 315, m_pParrentDock->GetDefaultFont());
	m_pDock->AddButton(0,25,_T("Btn_Image"), button_image, select_function);
	//m_pDock->AddTextField(0,0,327,25,_T("Txt_Name"), level_name, D3DXCOLOR(1,1,1,1));
	tstringstream strstr;
	strstr  << highscore;
	//m_pDock->AddTextField(0, 285, 327, 25, _T("Txt_HighScore"), strstr.str(), D3DXCOLOR(1,1,1,1));
	//m_pDock->AddTextField(305, 285, 327, 25, _T("Txt_Time"), LemmingsHelpers::GetTimeStringFromSecondsValue(best_time), D3DXCOLOR(1,1,1,1));
	m_pDock->Initialize();
}

UILevelButton::~UILevelButton() //default destructor
{
	SafeDelete(m_pDock);
}

void UILevelButton::Draw(const GameContext & context) const
{
	m_pDock->Draw(context);
}

void UILevelButton::Update(const GameContext &context)
{
	m_pDock->Update(context);
}

void UILevelButton::SetDisabled(bool disabled)
{
	UIElement::SetDisabled(disabled);
	m_pDock->SetElementDisabled(_T("Btn_Image"), disabled);
}