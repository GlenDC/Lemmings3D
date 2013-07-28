#include "GlobalParameters.h"

ParameterClass * GlobalParameters::m_pParameters = nullptr;

const ParameterClass * GlobalParameters::GetParameters()
{
	if(m_pParameters == nullptr)
	{
		LoadParameters();
	}
	return m_pParameters;
}

void GlobalParameters::Refresh()
{
	if(m_pParameters == nullptr)
	{
		LoadParameters();
	}
	m_pParameters->Refresh();
}

void GlobalParameters::LoadParameters()
{
	m_pParameters = new ParameterClass(_T("GlobalParameters"));
}