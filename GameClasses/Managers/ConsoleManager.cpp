#include "ConsoleManager.h"
#include "Game.h"
#include <algorithm>

ConsoleManager* ConsoleManager::m_pInstance = nullptr;

ConsoleManager::ConsoleManager(void)
	: m_IsInitialized(false)
{
}

ConsoleManager::~ConsoleManager(void)
{
}

void ConsoleManager::Initialize()
{
	m_IsInitialized = true;
}

void ConsoleManager::Update(GameContext& context)
{
	/*tstring input;
	if(tcin.)
	{
		tcin >> input;
		OutputDebugString(input.append(_T("\n")).c_str());
	}*/
}

void ConsoleManager::Draw(GameContext& context)
{
	//nothing to draw
}

//template <typename R, typename O>
//void ConsoleManager::Add_Function_0<R, O>(R (*functionPtr)(O* sourcePtr))
//{
//
//}