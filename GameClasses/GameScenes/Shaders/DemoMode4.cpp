//=========================== INCLUDES =================================
#include "DemoMode4.h"
//----------------------------------------------------------------------
#include "Scenegraph/GameScene.h"
#include "../../GameObjects/GameEntity.h"
#include "../../GameObjects/EditorCamera.h"
//======================================================================

DemoMode4::DemoMode4(GameScene * scene)
	: DemoModeBase(scene, _T("A primitive representation of water"))
{
}

DemoMode4::~DemoMode4(void)
{
}

void DemoMode4::Initialize()
{
	DemoModeBase::Initialize();

	m_pDemoObject = new GameEntity(MaterialType::MatSpikey);
	m_pScene->AddSceneObject(m_pDemoObject);
	m_ContentActive = false;
	m_pDemoObject->Translate(9999,9999,9999);

	m_pCamera->SetCanControl(false);
}

void DemoMode4::Update(const GameContext& context)
{
	DemoModeBase::Update(context);
}

void DemoMode4::Draw(const GameContext& context)
{
}

void DemoMode4::Draw2D(const GameContext& context)
{
	DemoModeBase::Draw2D(context);
}

void DemoMode4::Activate()
{
	DemoModeBase::Activate();
}

void DemoMode4::Deactivate()
{
	DemoModeBase::Deactivate();
}