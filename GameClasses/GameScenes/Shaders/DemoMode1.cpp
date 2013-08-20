//=========================== INCLUDES =================================
#include "DemoMode1.h"
//----------------------------------------------------------------------
#include "Scenegraph/GameScene.h"
#include "../../GameObjects/EditorCamera.h"
//======================================================================

DemoMode1::DemoMode1(GameScene * scene)
	: DemoModeBase(scene, _T("Cubes breakdown"))
{
}

DemoMode1::~DemoMode1(void)
{

}

void DemoMode1::Initialize()
{
	DemoModeBase::Initialize();
	m_pCamera->SetCanControl(false);
}

void DemoMode1::Update(const GameContext& context)
{
	DemoModeBase::Update(context);
}

void DemoMode1::Draw(const GameContext& context)
{

}

void DemoMode1::Draw2D(const GameContext& context)
{
	DemoModeBase::Draw2D(context);
}

void DemoMode1::Activate()
{
	DemoModeBase::Activate();
}

void DemoMode1::Deactivate()
{
	DemoModeBase::Deactivate();
}