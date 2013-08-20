//====================== #INCLUDES ===================================
#include "ShaderScreen.h"
//--------------------------------------------------------------------
#include "../Managers/ScreenManager.h"
#include "../Managers/SpritefontManager.h"
#include "../Managers/ParameterManager.h"
#include "../Managers/AudioManager.h"
#include "../Entities/ParameterClass.h"
#include "../Lib/LemmingsHelpers.h"
#include "../UserInterface/UIDockInterface.h"
#include "../GameScenes/GameLoadingScreen.h"
#include "GameScreen.h"
//--------------------------------------------------------------------
#include <thread>
//--------------------------------------------------------------------
#include "Graphics/GraphicsDevice.h"
#include "Helpers/GeneralStructs.h"
#include "Managers/ContentManager.h"
#include "OverlordComponents.h"
#include "Scenegraph/GameObject.h"
#include "MainMenuScreen.h"
#include "../Managers/Stopwatch.h"
#include "Shaders/DemoMode1.h"
#include "Shaders/DemoMode2.h"
#include "Shaders/DemoMode3.h"
#include "Shaders/DemoMode4.h"
#include "Shaders/DemoModeController.h"
#include "Shaders/DemoModeNXJoint.h"
#include "../Entities/WorldBroadCast.h"
#include "../GameObjects/SkyBox.h"
//====================================================================

ShaderScreen::ShaderScreen(void)
	: BaseScreen(_T("ShaderScreen"), _T("Lemmings3D Main Menu"), true)
	, m_pSpriteFont(nullptr)
	, m_pDemoDock(nullptr)
	, m_pMenuDock(nullptr)
	, m_pStates(nullptr)
{
	m_pStates = new StateManager();
	m_pStates->Initialize();

	auto state_1 = new DemoMode1(this);
	state_1->Initialize();
	m_pStates->AddState(_T("Demo1"),state_1);

	auto state_2 = new DemoMode2(this);
	state_2->Initialize();
	m_pStates->AddState(_T("Demo2"),state_2);

	auto state_3 = new DemoMode3(this);
	state_3->Initialize();
	m_pStates->AddState(_T("Demo3"),state_3);

	auto state_4 = new DemoMode4(this);
	state_4->Initialize();
	m_pStates->AddState(_T("Demo4"),state_4);

	auto state_controller = new DemoModeController(this);
	state_controller->Initialize();
	m_pStates->AddState(_T("DemoCharacter"),state_controller);

	auto state_nxjoint = new DemoModeNXJoint(this);
	state_nxjoint->Initialize();
	m_pStates->AddState(_T("DemoNXJoint"),state_nxjoint);

	m_pStates->SetState(_T("Demo1"));

	m_pSpriteFont = SpritefontManager::GetInstance()->CreateOrGet(_T("GameOver"));
	
	m_pDemoDock = new UIDockInterface(0, 0, 1280, 720, m_pSpriteFont, nullptr);
	m_pDemoDock->AddImage(0, 0, _T("bg_menu"), _T("BG_ShaderDemos_BG.png"));
	int but_demo_y(90), start_x(260), offset(260);
	m_pDemoDock->AddButton(start_x, but_demo_y, _T("btn_exp_1"), _T("shaders_btn_exp_1.png"), [&] ()
	{
		m_pDemoDock->ToggleElement(_T("btn_exp_1"));
		m_pStates->SetState(_T("Demo1"));
		WorldBroadCast::GetInstance()->Send(_T("Switched to Experiment 1..."));
	}, false, true);
	start_x += offset;
	m_pDemoDock->AddButton(start_x, but_demo_y, _T("btn_exp_2"), _T("shaders_btn_exp_2.png"), [&] ()
	{
		m_pDemoDock->ToggleElement(_T("btn_exp_2"));
		m_pStates->SetState(_T("Demo2"));
		WorldBroadCast::GetInstance()->Send(_T("Switched to Experiment 2..."));
	}, false, false);
	start_x += offset;
	m_pDemoDock->AddButton(start_x, but_demo_y, _T("btn_exp_3"), _T("shaders_btn_exp_3.png"), [&] ()
	{
		m_pDemoDock->ToggleElement(_T("btn_exp_3"));
		m_pStates->SetState(_T("Demo3"));
		WorldBroadCast::GetInstance()->Send(_T("Switched to Experiment 3..."));
	}, false, false);
	start_x += offset;
	m_pDemoDock->AddButton(start_x, but_demo_y, _T("btn_exp_4"), _T("shaders_btn_exp_4.png"), [&] ()
	{
		m_pDemoDock->ToggleElement(_T("btn_exp_4"));
		m_pStates->SetState(_T("Demo4"));
		WorldBroadCast::GetInstance()->Send(_T("Switched to Experiment 4..."));
	}, false, false);

	start_x += offset;
	m_pDemoDock->AddButton(start_x, but_demo_y, _T("btn_test_character"), _T("shaders_btn_shader_controller.png"), [&] ()
	{
		m_pStates->SetState(_T("DemoCharacter"));
		m_pDemoDock->ToggleElement(_T("btn_test_character"));
		WorldBroadCast::GetInstance()->Send(_T("Switched to Character Controller Test Zone.."));
	}, false, false);
	start_x += offset;
	m_pDemoDock->AddButton(start_x, but_demo_y, _T("btn_nxjoint"), _T("shaders_btn_shader_nxjoint.png"), [&] ()
	{
		m_pDemoDock->ToggleElement(_T("btn_nxjoint"));
		m_pStates->SetState(_T("DemoNXJoint"));
		WorldBroadCast::GetInstance()->Send(_T("Switched to nx joint test zone..."));
	}, false, false);

	m_pDemoDock->Initialize();

	int x_quit(1695), x_vol(1865), y_but(10);
	m_pMenuDock = new UIDockInterface(0, 678, 1280, 720, m_pSpriteFont, nullptr);
	m_pMenuDock->AddButton(x_quit, y_but, _T("btn_quit"), _T("shaders_btn_quit.png"), [&] ()
	{
		WorldBroadCast::GetInstance()->Clear();
		ScreenManager::GetInstance()->AddScreen(new MainMenuScreen());
		ScreenManager::GetInstance()->AddActiveScreen(_T("MainMenuScreen"));	
		ScreenManager::GetInstance()->SetControlScreen(_T("MainMenuScreen"));
		ScreenManager::GetInstance()->RemoveActiveScreen(_T("ShaderScreen"));
		ScreenManager::GetInstance()->RemoveScreen(_T("ShaderScreen"));
		ScreenManager::GetInstance()->SetPhysicsDrawEnabled(false);
	});
	m_pMenuDock->AddButton(x_vol,y_but + 1, _T("ABtn_Mute"), _T("Main_Volume_Mute.png"), [&] () 
	{ 
		Stopwatch::GetInstance()->CreateTimer(_T("MuteVolume"), 0.05f, false, false, [&] () 
		{
			m_pMenuDock->SetElementVisible(_T("ABtn_Mute"), false);
			m_pMenuDock->SetElementDisabled(_T("ABtn_Mute"), true);
			m_pMenuDock->SetElementVisible(_T("ABtn_UnMute"), true);
			m_pMenuDock->SetElementDisabled(_T("ABtn_UnMute"), false);
			AudioManager::GetInstance()->SetIsMuted(true);
			WorldBroadCast::GetInstance()->Send(_T("Master volume muted... silence follows!"));
		});
	});
	m_pMenuDock->AddButton(x_vol,y_but + 1, _T("ABtn_UnMute"), _T("Main_Volume_Unmute.png"), [&] () 
	{
		Stopwatch::GetInstance()->CreateTimer(_T("UnmuteVolume"), 0.05f, false, false, [&] () 
		{
			m_pMenuDock->SetElementVisible(_T("ABtn_Mute"), true);
			m_pMenuDock->SetElementDisabled(_T("ABtn_Mute"), false);
			m_pMenuDock->SetElementVisible(_T("ABtn_UnMute"), false);
			m_pMenuDock->SetElementDisabled(_T("ABtn_UnMute"), true);
			AudioManager::GetInstance()->SetIsMuted(false);
			WorldBroadCast::GetInstance()->Send(_T("Master volume unmuted... enjoy the music!"));
		});
	});
	bool masterVolumeMuted = GlobalParameters::GetParameters()->GetParameter<bool>(_T("MUTE_MASTER_SOUND"));
	AudioManager::GetInstance()->SetIsMuted(masterVolumeMuted);
	if(masterVolumeMuted)
	{
		m_pMenuDock->SetElementVisible(_T("ABtn_Mute"), false);
		m_pMenuDock->SetElementDisabled(_T("ABtn_Mute"), true);
	}
	else
	{
		m_pMenuDock->SetElementVisible(_T("ABtn_UnMute"), false);
		m_pMenuDock->SetElementDisabled(_T("ABtn_UnMute"), true);
	}

	m_pMenuDock->Initialize();
}


ShaderScreen::~ShaderScreen(void)
{
	SafeDelete(m_pDemoDock);
	SafeDelete(m_pMenuDock);
	SafeDelete(m_pStates);
}

void ShaderScreen::Initialize()
{
	BaseScreen::Initialize();

	/*auto skybox = new SkyBox();
	skybox->Scale(50,50,50);
	AddSceneObject(skybox);*/
}

void ShaderScreen::Update(const GameContext& context)
{
	m_pDemoDock->Update(context);
	m_pMenuDock->Update(context);
	m_pStates->Update(context);

	BaseScreen::Update(context);
}

void ShaderScreen::Draw(const GameContext& context)
{
	m_pDemoDock->Draw(context);
	m_pMenuDock->Draw(context);
	m_pStates->Draw(context);
	m_pStates->Draw2D(context);

	ScreenManager::GetInstance()->DrawCursor(context);
	BaseScreen::Draw(context);
}

void ShaderScreen::BeginControl()
{

}

void ShaderScreen::EndControl()
{

}

void ShaderScreen::Activated()
{
	WorldBroadCast::GetInstance()->SetOrigin(D3DXVECTOR2(10, 140));
	WorldBroadCast::GetInstance()->Send(_T("Make sure to keep the paper next to you while testing these demos..."));
	WorldBroadCast::GetInstance()->Send(_T("Use the good old mouse to control the UI!"));
	WorldBroadCast::GetInstance()->Send(_T("Use the WASDQE keys to rotate the object (Querty)"));
	WorldBroadCast::GetInstance()->Send(_T("Welcome in the Shader Demo part of this project!"));
}

void ShaderScreen::Deactivated()
{
}