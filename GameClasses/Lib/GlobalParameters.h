#pragma once

//====================== #INCLUDES ===================================
#include "../Entities/ParameterClass.h"
//====================================================================

//====================== (static) GlobalParameter Class ==============
// Description:
//		Collects all the global static parameters. (defined in xml)
// Last Modification: 22/03/2013
// Copyright Glen De Cauwsemaecker
// www.glendc.com
//====================================================================

class GlobalParameters
{
public:
	static const ParameterClass * GetParameters();
	static void Refresh();

	~GlobalParameters(){}

private:
	GlobalParameters(){}
	static ParameterClass * m_pParameters;
	static void LoadParameters();
};