//=========================== INCLUDES =================================
#include "DemoMode2.h"
//======================================================================

DemoMode2::DemoMode2()
	: DemoModeBase(_T("Merged cubes"))
{

}

DemoMode2::~DemoMode2(void)
{
}

void DemoMode2::Initialize()
{

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