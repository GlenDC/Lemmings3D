//=========================== INCLUDES =================================
#include "DemoModeController.h"
//----------------------------------------------------------------------
#include "Scenegraph/GameScene.h"
//======================================================================

DemoModeController::DemoModeController(GameScene * scene)
	: DemoModeBase(scene, _T("Char. Controller Test Zone"), _T("Testing out the character controller, physics and animations."))
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
}

void DemoModeController::Deactivate()
{
	DemoModeBase::Deactivate();
}