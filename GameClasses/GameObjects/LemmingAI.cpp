//============================= INCLUDES ==========================
#include "LemmingAI.h"
#include "Helpers\GeneralStructs.h"
#include "../Lib/GlobalParameters.h"
#include "../Managers/ColissionCollector.h"
//=================================================================

LemmingAI::LemmingAI()
	: Lemming ( _T("lemmings_d.png"))
{
	float speed(GlobalParameters::GetParameters()->GetParameter<float>(_T("LEMMING_SPEED")));

	ColissionCollector::GetInstance()->AddUser(this);
}

LemmingAI::~LemmingAI()
{
	ColissionCollector::GetInstance()->RemoveUser(this);
}

void LemmingAI::Update(const GameContext & context)
{
	Lemming::Update(context);
}

void LemmingAI::UpdateControl(const GameContext & context)
{
}