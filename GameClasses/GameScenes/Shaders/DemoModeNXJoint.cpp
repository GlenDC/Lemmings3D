//=========================== INCLUDES =================================
#include "DemoModeNXJoint.h"
//----------------------------------------------------------------------
#include "Scenegraph/GameScene.h"
//======================================================================

DemoModeNXJoint::DemoModeNXJoint(GameScene * scene)
	: DemoModeBase(scene, _T("NX Joint Test Zones"), _T("Testing out the different implementations of NXJoints."))
{

}

DemoModeNXJoint::~DemoModeNXJoint(void)
{
}

void DemoModeNXJoint::Initialize()
{

}

void DemoModeNXJoint::Update(const GameContext& context)
{
	DemoModeBase::Update(context);
}

void DemoModeNXJoint::Draw(const GameContext& context)
{

}

void DemoModeNXJoint::Draw2D(const GameContext& context)
{
	DemoModeBase::Draw2D(context);
}

void DemoModeNXJoint::Activate()
{
	DemoModeBase::Activate();
}

void DemoModeNXJoint::Deactivate()
{
	DemoModeBase::Deactivate();
}