#pragma once

//====================== #INCLUDES ===================================
#include "Helpers/stdafx.h"
#include "Helpers/D3DUtil.h"
#include "SceneGraph/GameScene.h"
#include "../GameScenes/BaseScreen.h"
#include <vector>
//====================================================================

//====================== ManagerInterface Class =================================
// Description:
//		Abstract class to define the interface of all the ManagerClasses
// Last Modification: 04/03/2013
// Copyright Glen De Cauwsemaecker
// www.glendc.com
//====================================================================


class ManagerInterface
{
public:
	virtual void Initialize() = 0;
	virtual void Update(GameContext& context) = 0;
	virtual void Draw(GameContext& context) = 0;
};