//--------------------------------------------------------------------------------------
//   _____     _______ ____  _     ___  ____  ____    _____ _   _  ____ ___ _   _ _____ 
//  / _ \ \   / / ____|  _ \| |   / _ \|  _ \|  _ \  | ____| \ | |/ ___|_ _| \ | | ____|
// | | | \ \ / /|  _| | |_) | |  | | | | |_) | | | | |  _| |  \| | |  _ | ||  \| |  _|  
// | |_| |\ V / | |___|  _ <| |__| |_| |  _ <| |_| | | |___| |\  | |_| || || |\  | |___ 
//  \___/  \_/  |_____|_| \_\_____\___/|_| \_\____/  |_____|_| \_|\____|___|_| \_|_____|
//
// Overlord Engine v0.44
// Copyright Overlord Brecht Kets & Overlord Thomas Goussaert
// http://www.digitalartsandentertainment.com/
//--------------------------------------------------------------------------------------

#include "Helpers/stdafx.h"
#include "crtdbg.h"
#include "Main.h"
#include "Lemmings3D.h"

#pragma comment(lib, "PhysXLoader.lib")
#pragma comment(lib, "NxCharacter.lib")

int wmain(int argc, wchar_t* argv[])
{
	wWinMain(GetModuleHandle(0),0,0,SW_SHOW);
}

int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE prevInstance,
				   wchar_t* cmdLine, int showCmd)
{

	//notify user if heap is corrupt
	HeapSetInformation(NULL, HeapEnableTerminationOnCorruption, NULL,0);

	// Enable run-time memory leak check for debug builds.
	//#if defined(DEBUG) | defined(_DEBUG)
	//	_CrtSetDbgFlag( _CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF );
	//	#define new new(_NORMAL_BLOCK, __FILE__, __LINE__)
	//	//_crtBreakAlloc = 414;
	//#endif

	Lemmings3D *gamePtr = new Lemmings3D(); 
	
	gamePtr->RunGame(hInstance);
	delete gamePtr;
}
