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

#include "GameScenes\MainMenuScreen.h"
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
	ScreenManager::GetInstance()->AddScreen(new MainMenuScreen());
	ScreenManager::GetInstance()->AddActiveScreen(_T("MainMenuScreen"));
}
