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

	InputAction editLowerLayer((int)InputControls::KB_O_PRESSED,Pressed,'o');
	ScreenManager::GetInstance()->GetInputManager()->AddInputAction(editLowerLayer);

	InputAction editHigherLayer((int)InputControls::KB_P_PRESSED,Pressed,'p');
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
	}
	else if(context.Input->IsActionTriggered((int)InputControls::KB_P_PRESSED))
	{
		m_pParentScreen->GetLevel()->GetHigherDepth();
	}

	//D3DXVECTOR3 mouseWorldPos;
	////LemmingsHelpers::ScreenToWorld(context, D3DXVECTOR2((float)mousePointPos.x, (float)mousePointPos.y), mouseWorldPos);
	//LemmingsHelpers::GetNearPosition(context, mouseWorldPos);
	//D3DXVECTOR3 closestBuildPos = m_pLevel->GetSnapPosition(mouseWorldPos);
	//m_pBuilder->SetSnapPosition(context, closestBuildPos);
	//if(m_BuildModePosRefresh)
	//if(context.Input->IsActionTriggered((int)InputControls::KB_ALT_DOWN) && m_BuildModePosRefresh)
	//{
		//m_pBuilder->CalculatePositionFromEnvironment(context, m_pLevel->GetEnvironment(), m_pLevel->getSizeXYZ(),2,0,0.2f);
		//m_BuildModePosRefresh = false;
	//}
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
}

void EditModeScreen::Deactivate()
{
	m_pParentScreen->PauseGame(false);
}

void EditModeScreen::AddEnvironmentCube(const D3DXVECTOR3 & pos, int id)
{
	m_pParentScreen->GetLevel()->AddEnvironmentCube(pos, id);
}

bool EditModeScreen::RemoveEnvironmentCube(const D3DXVECTOR3 & pos)
{
	return m_pParentScreen->GetLevel()->RemoveEnvironmentCube(pos);
}

bool EditModeScreen::PaintEnvironmentCube(const D3DXVECTOR3 & pos, int id)
{
	return m_pParentScreen->GetLevel()->PaintEnvironmentCube(pos, id);
}

void EditModeScreen::RecheckEnvironment()
{
	m_pParentScreen->GetLevel()->RecheckEnvironment();
}

void EditModeScreen::CalculateEditorCollision()
{
	float size = GlobalParameters::GetParameters()->GetParameter<float>(_T("GRID_SIZE"));
	const auto & vec = m_pParentScreen->GetLevel()->GetEnvironment();
	// clear old list
	for(UINT i = 0 ; i < m_EditorCubeVec.size() ; ++i)
	{
		m_pParentScreen->RemoveSceneObject(m_EditorCubeVec[i]);
	}
	// fill new list
	for(const auto & pos : vec)
	{
		if(pos.z == m_pParentScreen->GetLevel()->GetCurrentDepth())
		{
			PhysicsCube * cube = new PhysicsCube(pos, size);
			m_pParentScreen->AddSceneObject(cube);
			cube->Initialize();
			m_EditorCubeVec.push_back(cube);
		}
	}
}