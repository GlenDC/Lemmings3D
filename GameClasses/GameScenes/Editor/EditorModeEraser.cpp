#include "EditorModeEraser.h"
#include "../../Entities/EditorBuilder.h"
#include "../GameScreen.h"

#include "../../Managers/ScreenManager.h"
#include "../../Lib/GlobalParameters.h"
#include "../../Lib/LemmingsHelpers.h"

EditorModeEraser::EditorModeEraser (EditorBuilder * pEditor)
	: IEditMode(pEditor)
{

}

EditorModeEraser::~EditorModeEraser()
{

}

void EditorModeEraser::Update(const GameContext & context)
{
	if(context.Input->IsActionTriggered((int)InputControls::MOUSE_RIGHT_PRESSED))
	{
		float size = GlobalParameters::GetParameters()->GetParameter<float>(_T("GRID_SIZE"));
		LemmingsHelpers::SnapPositionXYZ(m_pEditor->m_Position, size);
		m_pEditor->m_pGame->RemoveEnvironmentCube(m_pEditor->m_Position);
	}
}

void EditorModeEraser::Draw(const GameContext & context)
{

}