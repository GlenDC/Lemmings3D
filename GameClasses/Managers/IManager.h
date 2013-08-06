#pragma once

//====================== #INCLUDES ===================================
#include "Helpers/stdafx.h"
#include "Helpers/D3DUtil.h"
#include "SceneGraph/GameScene.h"

#include "../GameScenes/BaseScreen.h"

#include <vector>
//====================================================================

//====================== IManager Class =================================
// Description:
//		Abstract class to define the interface of all the ManagerClasses
// Last Modification: July 2013
// Glen De Cauwsemaecker
// www.glendc.com
//====================================================================

// Policy class
class IManager
{
public:
	virtual void Initialize() = 0;
	virtual void Update(GameContext& context) = 0;
	virtual void Draw(GameContext& context) = 0;
};