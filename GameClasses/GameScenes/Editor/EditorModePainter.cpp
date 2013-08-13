//====================== #INCLUDES ===================================
#include "EditorModePainter.h"
//--------------------------------------------------------------------
#include "../GameScreen.h"
#include "../../Entities/EditorBuilder.h"
#include "../../GameScenes/EditModeScreen.h"
#include "../../Lib/GlobalParameters.h"
#include "../../Lib/LemmingsHelpers.h"
#include "../../Managers/ScreenManager.h"
#include "../../UserInterface/UIDockInterface.h"
//====================================================================

EditorModePainter::EditorModePainter (EditorBuilder * pEditor)
	: IEditMode(pEditor)
	, m_PaintMode(PaintMode::rock)
{
	m_pPaintMenu = new UIDockInterface(0,0,500,500,nullptr,nullptr);
	m_pPaintMenu->AddImage(0, 0, _T("BACKGROUND"), _T("BG_EditorSubMenu.png"));
	m_pPaintMenu->AddButton(5,65,_T("Abtn_paint_recheck"), _T("painter_button_recheck.png"), [&] () 
	{ 
		//important todo : make this work again
		//m_pEditor->m_pGame->RecheckEnvironment();
	}, false, false);
	m_pPaintMenu->AddButton(55,65,_T("Abtn_paint_rock"), _T("painter_button_0_rock.png"), [&] () 
	{ 
		m_pPaintMenu->ToggleElement(_T("Abtn_paint_rock"));
		m_PaintMode = PaintMode::rock;
	}, false, true);
	m_pPaintMenu->AddButton(105,65,_T("Abtn_paint_grass"), _T("painter_button_1_grass.png"), [&] () 
	{ 
		m_pPaintMenu->ToggleElement(_T("Abtn_paint_grass"));
		m_PaintMode = PaintMode::grass;
	}, false, false);
	m_pPaintMenu->AddButton(155,65,_T("Abtn_paint_trunk"), _T("painter_button_2_trunk.png"), [&] () 
	{ 
		m_pPaintMenu->ToggleElement(_T("Abtn_paint_trunk"));
		m_PaintMode = PaintMode::trunk;
	}, false, false);
	m_pPaintMenu->Initialize();
}

EditorModePainter::~EditorModePainter()
{
	delete m_pPaintMenu;
}

void EditorModePainter::Update(const GameContext & context)
{
	m_pPaintMenu->Update(context);
	if(context.Input->IsActionTriggered((int)InputControls::MOUSE_RIGHT_PRESSED))
	{
		int newID = (int)m_PaintMode;
		float size = GlobalParameters::GetParameters()->GetParameter<float>(_T("GRID_SIZE"));
		LemmingsHelpers::SnapPositionXYZ(m_pEditor->m_Position, size);
		m_pEditor->GetEditScreen()->PaintEnvironmentCube(m_pEditor->m_Position, newID);
	}
}

void EditorModePainter::Draw(const GameContext & context)
{
}

void EditorModePainter::DrawMenu(const GameContext & context)
{
	m_pPaintMenu->Draw(context);
}