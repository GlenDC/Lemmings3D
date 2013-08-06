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

#include "Lemmings3D.h"

//Engine Includes
#include "OverlordComponents.h"
#include "Graphics/GraphicsDevice.h"
#include "Graphics/Material.h"
#include "Helpers/D3DUtil.h"
#include "Graphics/MeshFilter.h"
#include "Helpers/BinaryReader.h"

#include "GameScenes\MenuScreen.h"
#include "GameScenes\GameScreen.h"
#include "GameScenes\Labs\Week1.h"	//Lab Week1 (Pong)
#include "GameScenes\Labs\Week2.h"	//Lab Week2 (Character)
#include "GameScenes\Labs\Week4.h"	//Lab Week4 (Bones)
#include "GameScenes\Labs\Week5.h"	//Lab Week5 (Animations)
#include "GameScenes\Labs\Week6.h"	//Lab Week6 (GeometryShader)
#include "GameScenes\Labs\Week6_picking.h"	//Lab Week6 (Picking)
#include "Managers\ScreenManager.h"
#include "Managers\Stopwatch.h"

Lemmings3D::Lemmings3D(void) 
{
}


Lemmings3D::~Lemmings3D(void)
{

}

void Lemmings3D::OnWindowActivated()
{
}

void Lemmings3D::OnWindowDeactivated()
{
}

void Lemmings3D::Initialize()
{
	ScreenManager::GetInstance()->InitializeContent();

	//Lemmings3D
	ScreenManager::GetInstance()->AddScreen(new GameScreen());
	ScreenManager::GetInstance()->AddScreen(new MenuScreen());
	ScreenManager::GetInstance()->AddActiveScreen(_T("GameScreen"));
	
	////Lab Week1
	//ScreenManager::GetInstance()->AddScreen(new Week1());
	////ScreenManager::GetInstance()->AddActiveScreen(L"Week1");
	////Lab Week2
	//ScreenManager::GetInstance()->AddScreen(new Week2());
	////ScreenManager::GetInstance()->AddActiveScreen(L"Week2");
	////Lab Week4
	//ScreenManager::GetInstance()->AddScreen(new Week4());
	////ScreenManager::GetInstance()->AddActiveScreen(L"Week4");
	////Lab Week5
	/*ScreenManager::GetInstance()->AddScreen(new Week5());
	ScreenManager::GetInstance()->AddActiveScreen(L"Week5");*/
	////Lab Week6
	//ScreenManager::GetInstance()->AddScreen(new Week6());
	////ScreenManager::GetInstance()->AddActiveScreen(L"Week6");
	////Lab Week6 Picking
	/*ScreenManager::GetInstance()->AddScreen(new Week6_picking());
	ScreenManager::GetInstance()->AddActiveScreen(L"Week6_picking");*/
}
