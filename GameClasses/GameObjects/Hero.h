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

class Hero : public Lemming
{
private:

public:
	Hero();
	virtual ~Hero();

	virtual void Update(const GameContext & context);
	virtual void UpdateControl(const GameContext & context);

private:

	// Disabling default copy constructor and default assignment operator.
	Hero(const Hero& yRef);									
	Hero& operator=(const Hero& yRef);
};