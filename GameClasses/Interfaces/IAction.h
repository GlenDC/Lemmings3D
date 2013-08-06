#pragma once

//====================== #INCLUDES ===================================
//====================================================================

//====================== Action Interface ============================
// Description:
//		Interface for all actions
// Last Modification: July 2013
// Glen De Cauwsemaecker
// www.glendc.com
//====================================================================

//Policy class
class IAction
{
public:
    virtual ~IAction() {}
    virtual void Forward() = 0;
    virtual void Reverse() = 0;
};