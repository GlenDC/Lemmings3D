//=========================== INCLUDES =================================
#include "DemoMode2.h"
//----------------------------------------------------------------------
#include "Scenegraph/GameScene.h"
#include "../../GameObjects/EditorCamera.h"
//======================================================================

DemoMode2::DemoMode2(GameScene * scene)
	: DemoModeBase(scene, _T("Merged cubes"))
{

}

DemoMode2::~DemoMode2(void)
{
}

void DemoMode2::Initialize()
{
	DemoModeBase::Initialize();
	m_pCamera->SetCanControl(false);
}

void DemoMode2::Update(const GameContext& context)
{
	DemoModeBase::Update(context);
}

void DemoMode2::Draw(const GameContext& context)
{

}

void DemoMode2::Draw2D(const GameContext& context)
{
	DemoModeBase::Draw2D(context);
}

void DemoMode2::Activate()
{
	DemoModeBase::Activate();
}

void DemoMode2::Deactivate()
{
	DemoModeBase::Deactivate();
}