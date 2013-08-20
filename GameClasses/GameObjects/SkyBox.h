#pragma once

//====================== #INCLUDES ===================================
#include "Helpers/stdafx.h"
#include "Helpers/D3DUtil.h"
#include "Helpers/GeneralStructs.h"
#include "GameEntity.h"
//====================================================================

//====================== SkyBox Class =======================
// Description:
//		SkyBox model object class (using a cube map)
// Last Modification: August 2013
// Glen De Cauwsemaecker
// www.glendc.com
//====================================================================

class SkyBox : public GameEntity
{
public:
	SkyBox();
	virtual ~SkyBox(void);
	virtual void Initialize();

private:
	// Disabling default copy constructor and default assignment operator.
	SkyBox(const SkyBox& yRef);									
	SkyBox& operator=(const SkyBox& yRef);
};