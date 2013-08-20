#pragma once
//====================== #INCLUDES ===================================
#include "Lemming.h"
//====================================================================

//====================== Hero Class =============================
// Description:
//		Hero (Character) Object
// Last Modification: August 2013
// Glen De Cauwsemaecker
// www.glendc.com
//====================================================================

class ThirdPersonCamera;

class Hero : public Lemming
{
private:

public:
	Hero();
	virtual ~Hero();
	
	virtual void Initialize();
	virtual void Update(const GameContext & context);
	virtual void UpdateControl(const GameContext & context);

	void SetControlled(bool control_character);

private:
	bool m_Controlled;
	ThirdPersonCamera *m_pCamera;

	// Disabling default copy constructor and default assignment operator.
	Hero(const Hero& yRef);									
	Hero& operator=(const Hero& yRef);
};