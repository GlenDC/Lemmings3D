#pragma once
//====================== #INCLUDES ===================================
#include "GameEntity.h"
//====================================================================

//====================== Decal Class =============================
// Description:
//		Decal object ( request for Graphics Programming #1 )
// Last Modification: August 2013
// Glen De Cauwsemaecker
// www.glendc.com
//====================================================================

class Decal : public GameEntity
{
public:
	Decal(UINT id);
	virtual ~Decal();

private:
	// Disabling default copy constructor and default assignment operator.
	Decal(const Decal& yRef);									
	Decal& operator=(const Decal& yRef);
};
