//====================== #INCLUDES ===================================
#include "EditModeScreen.h"
//--------------------------------------------------------------------
#include "GameScreen.h"
#include "Graphics/GraphicsDevice.h"
#include "Helpers/D3DUtil.h"
#include "Helpers/GeneralStructs.h"
#include "OverlordComponents.h"
#include "Scenegraph/GameObject.h"
//--------------------------------------------------------------------
#include "../Entities/ParameterClass.h"
#include "../Entities/Player.h"
#include "../Lib/GlobalParameters.h"
#include "../Lib/LemmingsHelpers.h"
#include "../Entities/EditorBuilder.h"
#include "../GameObjects/GameEntity.h"
#include "../GameObjects/ColissionEntity.h"
#include "../GameObjects/PhysicsCube.h"
#include "../GameObjects/EditorCamera.h"
#include "../Managers/ScreenManager.h"
#include "../Managers/Stopwatch.h"
//--------------------------------------------------------------------
#include <cmath>
//====================================================================

EditModeScreen::EditModeScreen(GameScreen * parent, InputManager *inputManager)
	:BaseModeScreen(parent, inputManager)
	, m_EditorCubeVec()
	, m_pBuilder(nullptr)
	, m_pCamera(nullptr)
{
}

EditModeScreen::~EditModeScreen(void)
{
	SafeDelete(m_pBuilder);
}

void EditModeScreen::Initialize()
{
	m_pBuilder = new EditorBuilder(this);

	InputAction editLowerLayer((int)InputControls::KB_O_PRESSED,Pressed,'O');
	ScreenManager::GetInstance()->GetInputManager()->AddInputAction(editLowerLayer);

	InputAction editHigherLayer((int)InputControls::KB_P_PRESSED,Pressed,'P');
	ScreenManager::GetInstance()->GetInputManager()->AddInputAction(editHigherLayer);

	m_pCamera = new EditorCamera();
	m_pParentScreen->AddSceneObject(m_pCamera);
	m_pCamera->GetComponent<CameraComponent>()->SetFieldOfView(LemmingsHelpers::ToRad(m_pParentScreen->GetPlayer()->GetSetting<float>(_T("EDITOR_CAMERA_FOV"))));
	m_pCamera->SetInformation(m_pParentScreen->GetPlayer()->GetSetting<D3DXVECTOR3>(_T("EDITOR_CAMERA_POS")),
									m_pParentScreen->GetPlayer()->GetSetting<float>(_T("EDITOR_CAMERA_YAW")),
									m_pParentScreen->GetPlayer()->GetSetting<float>(_T("EDITOR_CAMERA_PITCH")),
									m_pParentScreen->GetPlayer()->GetSetting<float>(_T("EDITOR_CAMERA_SPEED")),
									m_pParentScreen->GetPlayer()->GetSetting<float>(_T("EDITOR_CAMERA_ROT_SPEED")));
}

void EditModeScreen::Update(const GameContext& context)
{
	if(context.Input->IsActionTriggered((int)InputControls::KB_ESCAPE_PRESSED))
	{
		m_pParentScreen->SetState(_T("menu"));
	}
	m_pBuilder->Update(context);
	m_pCamera->AllowCameraControls(true);
	
	if(context.Input->IsActionTriggered((int)InputControls::KB_O_PRESSED))
	{
		m_pParentScreen->GetLevel()->GetLowerDepth();
		CalculateEditorCollision();
	}
	else if(context.Input->IsActionTriggered((int)InputControls::KB_P_PRESSED))
	{
		m_pParentScreen->GetLevel()->GetHigherDepth();
		CalculateEditorCollision();
	}

	auto object = m_pParentScreen->GetPlayer()->GetPickComponent()->Pick(context, context.Input->GetMousePosition(), D3DXVECTOR2(1280,720));
	if(object != nullptr)
	{
		auto position = object->GetComponent<TransformComponent>()->GetWorldPosition();
		m_pBuilder->SetSnapPosition(context, position);
	}
}

void EditModeScreen::Draw(const GameContext& context)
{
	m_pBuilder->Draw(context);
}

void EditModeScreen::Draw2D(const GameContext& context)
{
	m_pBuilder->DrawSubMenu(context);
}

void EditModeScreen::Activate()
{
	m_pCamera->GetComponent<CameraComponent>()->SetActive();
	m_pParentScreen->SetActiveCamera(m_pCamera);
	m_pParentScreen->PauseGame(true);

	CalculateEditorCollision();
	m_pBuilder->SetSettings();

	BaseModeScreen::Activate();
}

void EditModeScreen::Deactivate()
{
	m_pParentScreen->PauseGame(false);

	BaseModeScreen::Deactivate();
}

void EditModeScreen::AddEnvironmentCube(const D3DXVECTOR3 & pos, int id)
{
	auto environment = m_pParentScreen->GetLevel()->GetEnvironment();
	auto it_found = std::find_if(environment.begin(), environment.end(), [&pos] (const D3DXVECTOR3 & test_pos)
	{
		return test_pos == pos;
	});
	if(it_found == environment.end())
	{
		m_pParentScreen->GetLevel()->AddEnvironmentCube(pos, id);
		float size = GlobalParameters::GetParameters()->GetParameter<float>(_T("GRID_SIZE"));
		if(pos.y == m_pParentScreen->GetLevel()->GetCurrentDepth())
		{
			CreateAndAddPhysicsCube(pos, size);
		}
	}
}

bool EditModeScreen::RemoveEnvironmentCube(const D3DXVECTOR3 & pos)
{
	return m_pParentScreen->GetLevel()->RemoveEnvironmentCube(pos);
	RemovePhysicsCube(pos);
}

bool EditModeScreen::PaintEnvironmentCube(const D3DXVECTOR3 & pos, int id)
{
	return m_pParentScreen->GetLevel()->PaintEnvironmentCube(pos, id);
}

void EditModeScreen::RecheckEnvironment()
{
	m_pParentScreen->GetLevel()->RecheckEnvironment();
}

std::shared_ptr<Level> EditModeScreen::GetCurrentLevel() const
{
	return m_pParentScreen->GetLevel();
}

void EditModeScreen::CalculateEditorCollision()
{
	ClearCollectionList();
	float size = GlobalParameters::GetParameters()->GetParameter<float>(_T("GRID_SIZE"));
	const auto & vec = m_pParentScreen->GetLevel()->GetEnvironment();
	// fill new list
	for(const auto & pos : vec)
	{
		if(pos.y == m_pParentScreen->GetLevel()->GetCurrentDepth())
		{
			CreateAndAddPhysicsCube(pos, size);
		}
	}
}

void EditModeScreen::ClearCollectionList()
{
	for(UINT i = 0 ; i < m_EditorCubeVec.size() ; ++i)
	{
		m_pParentScreen->RemoveSceneObject(m_EditorCubeVec[i]);
	}
	m_EditorCubeVec.clear();
}

void EditModeScreen::CreateAndAddPhysicsCube(const D3DXVECTOR3 & pos, float size)
{
	PhysicsCube * cube = new PhysicsCube(pos, size);
	m_pParentScreen->AddSceneObject(cube);
	cube->Initialize();
	m_EditorCubeVec.push_back(cube);
}

void EditModeScreen::RemovePhysicsCube(const D3DXVECTOR3 & pos)
{
	float size = GlobalParameters::GetParameters()->GetParameter<float>(_T("GRID_SIZE"));
	std::remove_if(m_EditorCubeVec.begin(), m_EditorCubeVec.end(), [&size, &pos] ( PhysicsCube * cube )
	{
		D3DXVECTOR3 pos = cube->GetComponent<TransformComponent>()->GetWorldPosition() - pos;
		return D3DXVec3Length(&pos) < size;
	});
}