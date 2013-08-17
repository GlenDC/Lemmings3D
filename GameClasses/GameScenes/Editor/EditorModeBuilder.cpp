//====================== #INCLUDES ===================================
#include "EditorModeBuilder.h"
//--------------------------------------------------------------------
#include "../GameScreen.h"
#include "../../Entities/EditorBuilder.h"
#include "../../GameScenes/EditModeScreen.h"
#include "../../Lib/GlobalParameters.h"
#include "../../Lib/LemmingsHelpers.h"
#include "../../Managers/ScreenManager.h"
//====================================================================

EditorModeBuilder::EditorModeBuilder (EditorBuilder * pEditor)
	: IEditMode(pEditor)
{

}

EditorModeBuilder::~EditorModeBuilder()
{

}

void EditorModeBuilder::Update(const GameContext & context)
{
	if(context.Input->IsActionTriggered((int)InputControls::MOUSE_RIGHT_PRESSED))
	{
		float size = GlobalParameters::GetParameters()->GetParameter<float>(_T("GRID_SIZE"));
		LemmingsHelpers::SnapPositionXYZ(m_pEditor->m_Position, size);
		if(m_pEditor->GetEditScreen()->GetCurrentLevel()->IsLegalToBuild(m_pEditor->m_Position))
		{
			m_pEditor->GetEditScreen()->AddEnvironmentCube(m_pEditor->m_Position,0);
		}
	}
}

void EditorModeBuilder::Draw(const GameContext & context)
{

}