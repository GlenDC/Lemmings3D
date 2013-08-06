#pragma once

//====================== #INCLUDES ===================================
#include "Helpers/stdafx.h"
#include "Helpers/D3DUtil.h"
//====================================================================

//====================== ColissionUser Interface ============================
// Description:
//		Interface for a user of colissionObjects
//		Around this Object colission components will be created
// Last Modification: July 2013
// Glen De Cauwsemaecker
// www.glendc.com
//====================================================================

// Policy Class
class IColissionUser
{
public:
    virtual ~IColissionUser() {}
    virtual const D3DXVECTOR3 & GetCUPosition() const = 0;
    virtual float GetCURange() const = 0;
};