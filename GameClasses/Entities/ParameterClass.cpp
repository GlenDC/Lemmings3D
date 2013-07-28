//====================== #INCLUDES ===================================
#include "ParameterClass.h"
//====================================================================

ParameterClass::ParameterClass(tstring file)
{
	//ToDo: Write Constructor
	m_pParser = new XMLParser(file);
}

ParameterClass::~ParameterClass() //Default Destructor
{
	//ToDo: Write Destructor
}

void ParameterClass::Refresh()
{
	m_pParser->Reload();
}

void ParameterClass::Save()
{
	m_pParser->Save();
}