//=========================== INCLUDES =================================
#include "DemoModeController.h"
//----------------------------------------------------------------------
#include "OverlordComponents.h"
#include "Scenegraph/GameScene.h"
#include "SceneGraph/GameObject.h"
#include "../../GameObjects/Hero.h"
//======================================================================

DemoModeController::DemoModeController(GameScene * scene)
	: DemoModeBase(scene, _T("Char. Controller Test Zone"), _T("Testing out the character controller, physics and animations."))
	, m_pFloor(nullptr)
	, m_pPlayer(nullptr)
{

}

DemoModeController::~DemoModeController(void)
{
}

void DemoModeController::Initialize()
{

}

void DemoModeController::Update(const GameContext& context)
{
	DemoModeBase::Update(context);
}

void DemoModeController::Draw(const GameContext& context)
{

}

void DemoModeController::Draw2D(const GameContext& context)
{
	DemoModeBase::Draw2D(context);
}

void DemoModeController::Activate()
{
	DemoModeBase::Activate();

	// ===== FLOOR

	m_pFloor = new GameObject();
	m_pScene->AddSceneObject(m_pFloor);

	auto rbody = new RigidBodyComponent();
	rbody->SetStatic(true);
	m_pFloor->AddComponent(rbody);
	
	auto plane = new PlaneColliderComponent(0.0f);
	m_pFloor->AddComponent(plane);

	// ===== PLAYER CHARACTER

	m_pPlayer = new Hero();
	m_pScene->AddSceneObject(m_pPlayer);
	m_pPlayer->SetControlled(true);
}

void DemoModeController::Deactivate()
{
	m_pScene->RemoveSceneObject(m_pFloor);
	m_pFloor = nullptr;
	m_pScene->RemoveSceneObject(m_pPlayer);
	m_pPlayer = nullptr;

	DemoModeBase::Deactivate();
}