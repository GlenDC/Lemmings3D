//========================================= INCLUDES ==========================================
#include "DemoModeBase.h"
//---------------------------------------------------------------------------------------------
#include "..\..\Managers\SpritefontManager.h"
#include "..\..\UserInterface\UIDockInterface.h"
#include "../../GameObjects/GameEntity.h"
#include "OverlordComponents.h"
//=============================================================================================

const float DemoModeBase::ROTATION_SPEED = 2.0f;

DemoModeBase::DemoModeBase(GameScene * scene, const tstring & title, const tstring & description)
	: State()
	, m_pDescriptionDock(nullptr)
	, m_pDefaultFont(nullptr)
	, m_pScene(scene)
	, m_ContentActive(false)
	, m_pDemoObject(nullptr)
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


void DemoModeBase::Initialize()
{
	auto object = new GameObject();
	m_pScene->AddSceneObject(object);

	auto camera = new CameraComponent();
	object->AddComponent(camera);
	camera->Initialize();
	camera->GetTransform()->Translate(0,0,-50.0f);
	camera->SetActive();

	object->Initialize();
}

void DemoModeBase::Update(const GameContext& context)
{
	m_pDescriptionDock->Update(context);
	if(m_pDemoObject != nullptr)
	{
		D3DXVECTOR3 rotation = D3DXVECTOR3(0,0,0);
		rotation.y = context.Input->IsKeyboardKeyDown('W')?ROTATION_SPEED:0.0f;
		if(rotation.y == 0) rotation.y = -(context.Input->IsKeyboardKeyDown('S')?ROTATION_SPEED:0.0f);
		rotation.x = context.Input->IsKeyboardKeyDown('A')?ROTATION_SPEED:0.0f;
		if(rotation.x == 0) rotation.x = -(context.Input->IsKeyboardKeyDown('D')?ROTATION_SPEED:0.0f);
		rotation.z = context.Input->IsKeyboardKeyDown('Q')?ROTATION_SPEED:0.0f;
		if(rotation.z == 0) rotation.z = -(context.Input->IsKeyboardKeyDown('E')?ROTATION_SPEED:0.0f);

		rotation *= context.GameTime.ElapsedSeconds();

		D3DXMATRIX rotMatrix, newRotMatrix;
		D3DXMatrixRotationQuaternion(&rotMatrix, &m_pDemoObject->GetRotation());
		D3DXMatrixRotationYawPitchRoll(&newRotMatrix, rotation.x, rotation.y, rotation.z);
		rotMatrix *= newRotMatrix;
		D3DXQUATERNION rot;
		D3DXVECTOR3 dum;
		D3DXMatrixDecompose(&dum, &rot, &dum, &rotMatrix);
		m_pDemoObject->Rotate(rot);
	}
}

void DemoModeBase::Draw2D(const GameContext& context)
{
	m_pDescriptionDock->Draw(context);
}

void DemoModeBase::Activate()
{ 
	State::Activate();
	if(!m_ContentActive && m_pDemoObject)
	{
		m_pDemoObject->Translate(0,0,0);
	}
	m_ContentActive = true;
}

void DemoModeBase::Deactivate()
{
	State::Deactivate();
	if(m_ContentActive && m_pDemoObject)
	{
		m_pDemoObject->Translate(9999,9999,9999);
	}
	m_ContentActive = false;
}