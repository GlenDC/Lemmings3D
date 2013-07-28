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

#include "EditModeScreen.h"
#include "OverlordComponents.h"
#include "Scenegraph/GameObject.h"
#include "Graphics/GraphicsDevice.h"
#include "OverlordComponents.h"
#include "Helpers/GeneralStructs.h"
#include "../GameObjects/GameEntity.h"
#include "../GameObjects/ColissionEntity.h"
#include "../Managers/ScreenManager.h"
#include "../Managers/Stopwatch.h"
#include "../Entities/ParameterClass.h"
#include "helpers/D3DUtil.h"
#include "GameScreen.h"

EditModeScreen::EditModeScreen(GameScreen * parent, InputManager *inputManager)
	:BaseModeScreen(parent, inputManager)
{
}


EditModeScreen::~EditModeScreen(void)
{
}

void EditModeScreen::Initialize()
{
	/*m_pDeveloperZone->AddButton(D3DXVECTOR2(35,35), _T("PlayTheLevel"), [&] {
		m_pParentScreen->SetGameMode(true);
	}, _T("L3D_ui_PlayLevelButton_n.png"), _T("L3D_ui_PlayLevelButton_h.png")
		,_T("L3D_ui_PlayLevelButton_c.png"));*/
	BaseModeScreen::Initialize();
}

void EditModeScreen::Update(const GameContext& context)
{
	BaseModeScreen::Update(context);
}

void EditModeScreen::Draw(const GameContext& context)
{
	BaseModeScreen::Draw(context);
}