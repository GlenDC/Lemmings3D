//============================= INCLUDES ==========================
#include "Hero.h"
#include "Helpers\GeneralStructs.h"
#include "../Lib/GlobalParameters.h"
//=================================================================

Hero::Hero()
	: Lemming ( _T("player_d.png"))
{
	float speed(GlobalParameters::GetParameters()->GetParameter<float>(_T("HERO_SPEED")));
	m_TargetSpeed = D3DXVECTOR3(speed, speed, speed);
}

 Hero::~Hero()
 {

 }

 void Hero::Update(const GameContext & context)
 {
	 Lemming::Update(context);
 }
 
 void Hero::UpdateControl(const GameContext & context)
 {
	 m_Direction = D3DXVECTOR3(0,0,0);
	 m_Direction.z = context.Input->IsKeyboardKeyDown('W')?1.0f:0.0f;
	 if(m_Direction.z == 0) m_Direction.z = -(context.Input->IsKeyboardKeyDown('S')?1.0f:0.0f);
	 if(m_Direction.z == 0) m_Direction.z = context.Input->GetThumbstickPosition().y;

	 m_Direction.x = context.Input->IsKeyboardKeyDown('D')?1.0f:0.0f;
	 if(m_Direction.x == 0) m_Direction.x = -(context.Input->IsKeyboardKeyDown('A')?1.0f:0.0f);

	 Move(context);
	 
	 Lemming::UpdateControl(context);
 }