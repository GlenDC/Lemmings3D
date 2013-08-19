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
	m_TargetSpeed = D3DXVECTOR3(speed, speed, speed);
	m_Direction = D3DXVECTOR3(0,0,-1);

	ColissionCollector::GetInstance()->AddUser(this);
}

LemmingAI::~LemmingAI()
{
	ColissionCollector::GetInstance()->RemoveUser(this);
}

void LemmingAI::Update(const GameContext & context)
{
	Lemming::Update(context);
	Move(context);
}

void LemmingAI::UpdateControl(const GameContext & context)
{
}