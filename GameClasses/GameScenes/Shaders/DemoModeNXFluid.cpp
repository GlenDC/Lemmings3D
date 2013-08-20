//=========================== INCLUDES =================================
#include "DemoModeNXFluid.h"
//----------------------------------------------------------------------
#include "Scenegraph/GameScene.h"
#include "../../GameObjects/WaterObject.h"
//======================================================================

DemoModeNXFluid::DemoModeNXFluid(GameScene * scene)
	: DemoModeBase(scene, _T("NXFluid Testzone"), _T("Testing the implementation of the Fluid system in PhysX"))
	, m_pFluids(nullptr)
{

}

DemoModeNXFluid::~DemoModeNXFluid(void)
{
}

void DemoModeNXFluid::Initialize()
{

}

void DemoModeNXFluid::Update(const GameContext& context)
{
	DemoModeBase::Update(context);
}

void DemoModeNXFluid::Draw(const GameContext& context)
{

}

void DemoModeNXFluid::Draw2D(const GameContext& context)
{
	DemoModeBase::Draw2D(context);
}

void DemoModeNXFluid::Activate()
{
	m_pFluids = new WaterObject();
	m_pScene->AddSceneObject(m_pFluids);

	DemoModeBase::Activate();
}

void DemoModeNXFluid::Deactivate()
{
	m_pScene->RemoveSceneObject(m_pFluids);
	m_pFluids = nullptr;

	DemoModeBase::Deactivate();
}