//============================= INCLUDES ==========================
#include "Hero.h"
#include "Helpers\GeneralStructs.h"
#include "../Lib/GlobalParameters.h"
//=================================================================

Hero::Hero()
	: Lemming ( _T("player_d.png"))
{

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
	 float speed(GlobalParameters::GetParameters()->GetParameter<float>(_T("HERO_SPEED")));
	 D3DXVECTOR3 move(0,0,0);
	 move.z = context.Input->IsKeyboardKeyDown('W')?1.0f:0.0f;
	 if(move.z == 0) move.z = -(context.Input->IsKeyboardKeyDown('S')?1.0f:0.0f);
	 if(move.z == 0) move.z = context.Input->GetThumbstickPosition().y;

	 move.x = context.Input->IsKeyboardKeyDown('D')?1.0f:0.0f;
	 if(move.x == 0) move.x = -(context.Input->IsKeyboardKeyDown('A')?1.0f:0.0f);

	 D3DXVECTOR3 pos(GetTranslation());
	 pos += move * speed;
	 Translate(pos);
	 
	 Lemming::UpdateControl(context);
 }