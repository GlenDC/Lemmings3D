#pragma once

//====================== #INCLUDES ===================================
//====================================================================

//====================== Action Interface ============================
// Description:
//		Interface for all actions
// Last Modification: 01/04/2013
// Copyright Glen De Cauwsemaecker
// www.glendc.com
//====================================================================

class IAction
{
public:
    virtual ~IAction() {}
    virtual void Forward() = 0;
    virtual void Reverse() = 0;
};