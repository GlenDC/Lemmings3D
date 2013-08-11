//====================== #INCLUDES ===================================
#include "ParameterClass.h"
//====================================================================

ParameterClass::ParameterClass()
	: m_EmptyNode()
	, m_pParser(nullptr)
{

}

ParameterClass::ParameterClass(const tstring & file)
	: m_EmptyNode()
{
	//ToDo: Write Constructor
	m_pParser = new XMLParser(file);
}

ParameterClass::~ParameterClass() //Default Destructor
{
	//ToDo: Write Destructor
}

ParameterClass::ParameterClass(const ParameterClass& yRef)
	: m_EmptyNode()
	, m_pParser(m_pParser)
{

}

ParameterClass& ParameterClass::operator=(const ParameterClass& yRef)
{
	m_EmptyNode = yRef.m_EmptyNode;
	m_pParser = yRef.m_pParser;
	return *this;
}

void ParameterClass::Refresh()
{
	m_pParser->Reload();
}

void ParameterClass::Save()
{
	m_pParser->Save();
}

const pugi::xml_node & ParameterClass::GetChild(const tstring & parameter_name) const
{
	pugi::xml_node root = m_pParser->GetRoot();
	for(pugi::xml_node & child : root.children())
	{
		if(GetAttribueValue<tstring>(child, _T("name")) == parameter_name)
		{
			return child;
		}
	}
	return m_EmptyNode;
}