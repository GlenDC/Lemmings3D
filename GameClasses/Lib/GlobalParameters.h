#pragma once

//====================== #INCLUDES ===================================
#include "../Entities/ParameterClass.h"
//====================================================================

//====================== (static) GlobalParameter Class ==============
// Description:
//		Collects all the global static parameters. (defined in xml)
// Last Modification: July 2013
// Glen De Cauwsemaecker
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

	// Disabling default copy constructor and default assignment operator.
	GlobalParameters(const GlobalParameters& yRef);									
	GlobalParameters& operator=(const GlobalParameters& yRef);
};