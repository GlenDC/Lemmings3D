//====================== #INCLUDES ===================================
#include "ParameterManager.h"
#include "../Entities/ParameterClass.h"
#include "../Lib/LemmingsHelpers.h"
//====================================================================

ParameterManager * ParameterManager::m_pInstance = nullptr;

ParameterManager::ParameterManager(void)
{

}

ParameterManager::~ParameterManager(void)
{
	m_Parameters.clear();
}

ParameterManager* ParameterManager::GetInstance()
{
	if (m_pInstance == nullptr)
	{
		m_pInstance = new ParameterManager();
	}

	return m_pInstance;
}

void ParameterManager::Initialize()
{

}

void ParameterManager::Update(GameContext& context)
{

}

void ParameterManager::Draw(GameContext& context)
{

}

ParameterClass & ParameterManager::CreateOrGet(const tstring & collection)
{
	UINT identifier = LemmingsHelpers::GenerateHash(collection);
	auto it = m_Parameters.find(identifier);
	if(it == m_Parameters.end())
	{
		ParameterClass newParameters(collection);
		m_Parameters[identifier] = newParameters;
	}
	return m_Parameters[identifier];
}