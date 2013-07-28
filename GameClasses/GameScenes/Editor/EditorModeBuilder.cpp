#include "EditorModeBuilder.h"
#include "../../Entities/EditorBuilder.h"
#include "../GameScreen.h"

#include "../../Managers/ScreenManager.h"
#include "../../Lib/GlobalParameters.h"
#include "../../Lib/LemmingsHelpers.h"

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
		m_pEditor->m_pGame->AddEnvironmentCube(m_pEditor->m_Position,0);
	}
}

void EditorModeBuilder::Draw(const GameContext & context)
{

}