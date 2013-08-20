//=========================== INCLUDES =================================
#include "DemoMode3.h"
//----------------------------------------------------------------------
#include "Scenegraph/GameScene.h"
#include "../../GameObjects/EditorCamera.h"
//======================================================================

DemoMode3::DemoMode3(GameScene * scene)
	: DemoModeBase(scene, _T("A primitive representation of nature"))
{

}

DemoMode3::~DemoMode3(void)
{
}

void DemoMode3::Initialize()
{
	DemoModeBase::Initialize();
	m_pCamera->SetCanControl(false);
}

void DemoMode3::Update(const GameContext& context)
{
	DemoModeBase::Update(context);
}

void DemoMode3::Draw(const GameContext& context)
{

}

void DemoMode3::Draw2D(const GameContext& context)
{
	DemoModeBase::Draw2D(context);
}

void DemoMode3::Activate()
{
	DemoModeBase::Activate();
}

void DemoMode3::Deactivate()
{
	DemoModeBase::Deactivate();
}