#pragma once
//====================== #INCLUDES ===================================
#include "Lemming.h"
//====================================================================

//====================== LemmingAI Class =============================
// Description:
//		A normal Lemming character controlled by the AI
// Last Modificatsion: August 2013
// Glen De Cauwsemaecker
// www.glendc.com
//====================================================================

class LemmingAI : public Lemming
{
private:

public:
	LemmingAI();
	virtual ~LemmingAI();

	virtual void Update(const GameContext & context);
	virtual void UpdateControl(const GameContext & context);

private:

	// Disabling default copy constructor and default assignment operator.
	LemmingAI(const LemmingAI& yRef);									
	LemmingAI& operator=(const LemmingAI& yRef);
};