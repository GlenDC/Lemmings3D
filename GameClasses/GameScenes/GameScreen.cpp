//====================== #INCLUDES ===================================
#include "GameScreen.h"
//--------------------------------------------------------------------
#include "GameModeScreen.h"
#include "EditModeScreen.h"
#include "Game.h"
#include "OverlordComponents.h"
#include "Scenegraph/GameObject.h"
#include "Graphics/SpriteBatch.h"
#include "helpers/D3DUtil.h"
#include "Helpers/SpriteFont.h"
#include "helpers/DebugRenderer.h"
#include "Helpers/GeneralStructs.h"
#include "Managers/ContentManager.h"
#include "Diagnostics/FPS.h"
//--------------------------------------------------------------------
#include "../Entities/ParameterClass.h"
#include "../Entities/Level.h"
#include "../Entities/Player.h"
#include "../Entities/StatusReport.h"
#include "../Entities/RisingWater.h"
#include "../GameObjects/GameEntity.h"
#include "../GameObjects/ColissionEntity.h"
#include "../GameObjects/EditorCamera.h"
#include "../GameObjects/LemmingCharacter.h"
#include "../GameObjects/PhysicsCube.h" 
#include "../Helpers/HeightmapParser.h"
#include "../Lib/GlobalParameters.h" 
#include "../Lib/LemmingsHelpers.h"
#include "../Managers/ScreenManager.h"
#include "../Managers/TimeManager.h"
#include "../Managers/Stopwatch.h"
#include "../Managers/SpritefontManager.h"
#include "../Managers/ColissionCollector.h"
#include "../UserInterface/UIDockInterface.h"
#include "../XML/XMLConverter.h"
//====================================================================

GameScreen::GameScreen(void)
	:BaseScreen(_T("GameScreen"), _T("Play Lemmings3D"), true)
	,m_pLevel(nullptr)
	,m_pHeaderMenu(nullptr)
	,m_pGameMenu(nullptr)
	,m_pDefaultFont(nullptr)
	,m_pPlayer(nullptr)
	,m_pLemmingsCharacter(nullptr)
	,m_pLemmingsCharacter1(nullptr)
	,m_pLemmingsCharacter2(nullptr)
	,m_pStatusReport(nullptr)
	,m_AppMode(AppMode::Game)
	,m_PreviousAppMode(AppMode::Game)
	,m_StateMachine()
	,m_pRisingWater(nullptr)
	,m_RefreshLevelTimer(true)
	,m_BuildModePosRefresh(false)
	,m_CameraFOV(70.0f)
	,m_CameraSpeed(1.0f)
	,m_CameraZoom(0)
	,m_pCameraRotationTexture(nullptr)
	,m_CameraRotationSprite()
{
	TimeManager::GetInstance()->SetGameScreen(this);
}


GameScreen::~GameScreen(void)
{
	SafeDelete(m_pStatusReport);
	//Unset the camera component of the scene?!
	SafeDelete(m_pPlayer);

	TimeManager::GetInstance()->SetGameScreen(nullptr);
}

void GameScreen::Initialize()
{
	ColissionCollector::GetInstance()->Initialize();

	InputAction pauseGame((int)InputControls::KB_ESCAPE_PRESSED,Pressed,VK_ESCAPE);
	ScreenManager::GetInstance()->GetInputManager()->AddInputAction(pauseGame);

	InputAction switchMode((int)InputControls::KB_F10_PRESSED,Pressed,VK_F10);
	ScreenManager::GetInstance()->GetInputManager()->AddInputAction(switchMode);

	m_pStatusReport = new StatusReport(this, GlobalParameters::GetParameters()->GetParameter<bool>(_T("ALLOW_STATUS_LOG")));

	m_pDefaultFont = SpritefontManager::GetInstance()->CreateOrGet(_T("8BitFont"));

	m_pPlayer = new Player(GlobalParameters::GetParameters()->GetParameter<tstring>(_T("DEFAULT_PLAYER")),this);

	m_pHeaderMenu = new UIDockInterface(0, 0, 1280, 39, m_pDefaultFont, nullptr);
	AddHeaderMenuElements();
	m_pHeaderMenu->Initialize();

	m_pGameMenu = new UIDockInterface(0, 536, 1280, 184, m_pDefaultFont, nullptr);
	AddMainMenuElements();
	m_pGameMenu->Initialize();

	auto gameMode = new GameModeScreen(this, ScreenManager::GetInstance()->GetInputManager());
	gameMode->Initialize();
	m_StateMachine.AddState(_T("game"), gameMode);

	auto editorMode = new EditModeScreen(this, ScreenManager::GetInstance()->GetInputManager());
	editorMode->Initialize();
	m_StateMachine.AddState(_T("editor"), editorMode);

	m_pLevel = shared_ptr<Level>(new Level(_T("TestLevel"), this));
	m_pLevel->Initialize();

	//m_pRisingWater = new RisingWater(m_pLevel->GetMinDepth(), m_pLevel->GetMaxDepth());
	/*D3DXVECTOR3 offset = m_pLevel->Getoffset();
	float size = GlobalParameters::GetParameters()->GetParameter<float>(_T("GRID_SIZE"));
	for(UINT row = 0 ; row < m_pLevel->GetHeight() ; row += 30)
	{
		for(UINT col = 0 ; col < m_pLevel->Getwidth() ; col += 30)
		{
			D3DXVECTOR3 pos(col * size, 0, row * size);
			pos += offset;
			LemmingsHelpers::SnapPositionXYZ(pos, size);
			pos.x -= 0.25f;
			pos.z -= 0.25f;
			pos.y -= 15 * size;
			m_pRisingWater->AddInstance(pos);
		}
	}
	m_pRisingWater->Initialize();*/
	
	//ID3D10ShaderResourceView *m_pCameraRotationTexture;
	//SpriteInfo m_CameraRotationSprite;

	m_pCameraRotationTexture = ContentManager::Load<ID3D10ShaderResourceView>(_T("./Resources/Lemmings3D/ui/Main_MiniMap_CameraRotation.png"));

	m_CameraRotationSprite.pTexture = m_pCameraRotationTexture;
	m_CameraRotationSprite.Color = D3DXCOLOR(1,1,1,1);

	BaseScreen::Initialize();

	StartGame();
}

void GameScreen::Update(const GameContext& context)
{
	if(context.Input->IsActionTriggered((int)InputControls::KB_ESCAPE_PRESSED))
	{
		ScreenManager::GetInstance()->AddActiveScreen(_T("MenuScreen"));
		ScreenManager::GetInstance()->SetControlScreen(_T("MenuScreen"));
	}

	//control if player can control the camera or not!
	bool allowCameraMovement(true);
	//if(m_AppMode != AppMode::Editor) allowEditorCameraMovement = false;
	POINT mousePointPos = context.Input->GetMousePosition();
	if(context.Input->IsActionTriggered((int)InputControls::MOUSE_LEFT_DOWN))
	{
		D3DXVECTOR2 mousePos((float)mousePointPos.x, (float)mousePointPos.y);
		if(m_pHeaderMenu->CursorInZone(mousePos) || m_pGameMenu->CursorInZone(mousePos))
		{
			allowCameraMovement = false;
		}
	}
	//m_pCamera->AllowCameraControls(allowCameraMovement);

	m_pStatusReport->Update(context);
	m_pHeaderMenu->Update(context);
	m_pGameMenu->Update(context);

	m_StateMachine.Update(context);

	if(m_AppMode != AppMode::Pause)
	{
		m_pLevel->Update(context);
		TimeManager::GetInstance()->Update(const_cast<GameContext&>(context));
		BaseScreen::Update(context);
	}

	//Update Timer
	/*if(m_RefreshLevelTimer)
	{*/
		//Refresh Clock!
		int minutes(0);
		minutes = TimeManager::GetInstance()->GetTimeMinutes();
		tstring minutesString(_T(""));
		minutesString += XMLConverter::ConvertToTString<int>(minutes);
		if(minutes < 10)	minutesString = _T("0") + minutesString;
		m_pGameMenu->SetTextField(_T("Main_TextField_Clock_Minuts"), minutesString);
		int seconds(0);
		seconds = TimeManager::GetInstance()->GetTimeSeconds();
		tstring secondsString(_T(""));
		secondsString += XMLConverter::ConvertToTString<int>(seconds);
		if(seconds < 10)	secondsString = _T("0") + secondsString;
		m_pGameMenu->SetTextField(_T("Main_TextField_Clock_Seconds"), secondsString);

		//Set Camera Info
		D3DXVECTOR3 cameraPos = m_pActiveCamera->GetTransform()->GetWorldPosition();
		tstringstream strstrCamera;
		strstrCamera << _T("POS(X=") << cameraPos.x << _T(" Y=") << cameraPos.y << _T(" Z=") << cameraPos.z << _T(")");
		m_pGameMenu->SetTextField(_T("Main_TextField_Info_Pos"), strstrCamera.str());

		//Reset!
		//m_RefreshLevelTimer = false;
	//}

		//miniMap Sprite!
		/*D3DXQUATERNION rotation = m_pActiveCamera->GetTransform()->GetWorldRotation();
		float yaw = LemmingsHelpers::GetYaw(rotation);
		if(yaw < 0)
			yaw += (float)D3DX_PI / 2;*/
		/*m_CameraRotationSprite.Transform = LemmingsHelpers::MatrixTranslation(-40, -47,0) *
										LemmingsHelpers::MatrixRotation(0, 0, m_pCamera->GetYaw()) *
										LemmingsHelpers::MatrixTranslation(40, 47,0) *
										LemmingsHelpers::MatrixTranslation(1045,580,0.005f);*/

	m_pHeaderMenu->SetTextField(_T("ATxt_FPS"), XMLConverter::ConvertToTString<int>(FPS::GetInstance()->GetFPS()));
}

void GameScreen::Draw(const GameContext& context)
{
	//m_pRisingWater->Draw(context);
	//m_pRisingWater->Draw2D(context);

	m_StateMachine.Draw(context);

	m_pLevel->Draw(context);

	//for(int i = 0 ; i < 11; ++i)
	//{
	//	//Horizontal grid
	//	DebugRenderer::DrawLine(D3DXVECTOR3(10, 0, (float)(10 + i * 10)), D3DXVECTOR3(110, 0, (float)(10 + i * 10)), D3DXCOLOR(1,1,1,1));
	//	DebugRenderer::DrawLine(D3DXVECTOR3((float)(10 + i * 10), 0, 10), D3DXVECTOR3((float)(10 + i * 10), 0, 110), D3DXCOLOR(1,1,1,1));
	//	//vertical grid Y
	//	DebugRenderer::DrawLine(D3DXVECTOR3(60, -50, (float)(10 + i * 10)), D3DXVECTOR3(60, 50, (float)(10 + i * 10)), D3DXCOLOR(1,1,1,0.25f));
	//	DebugRenderer::DrawLine(D3DXVECTOR3(60, (float)(-50 + i * 10), 10), D3DXVECTOR3(60, (float)(-50 + i * 10), 110), D3DXCOLOR(1,1,1,0.25f));
	//	//vertical grid X
	//	DebugRenderer::DrawLine(D3DXVECTOR3((float)(10 + i * 10), -50, 60), D3DXVECTOR3((float)(10 + i * 10), 50, 60), D3DXCOLOR(1,1,1,0.25f));
	//	DebugRenderer::DrawLine(D3DXVECTOR3(10, (float)(-50 + i * 10), 60), D3DXVECTOR3(110, (float)(-50 + i * 10), 60), D3DXCOLOR(1,1,1,0.25f));
	//}

	if(m_AppMode != AppMode::Pause)
	{
		m_pHeaderMenu->Draw(context);
		m_pGameMenu->Draw(context);

		m_StateMachine.Draw2D(context);

		SpriteBatch::Draw(m_CameraRotationSprite);
		ScreenManager::GetInstance()->DrawCursor(context);
	}

	BaseScreen::Draw(context);
}

void GameScreen::BeginControl()
{
	PauseGame(false);
}

void GameScreen::EndControl()
{
	PauseGame(true);
}

void GameScreen::Activated()
{
}

void GameScreen::Deactivated()
{
	QuitGame();
}

void GameScreen::PauseGame(bool paused)
{
	if(paused)
	{
		m_pHeaderMenu->SetElementVisible(_T("ABtn_Play"), true);
		m_pHeaderMenu->SetElementVisible(_T("ABtn_Pause"), false);
		//delay so that it happens in another frame, 
		//if you would not do this, it will do both buttons
		Stopwatch::GetInstance()->CreateTimer(_T("delay_toggle_disable"), 0.05f, false, false, [&] () 
		{
			m_pHeaderMenu->SetElementDisabled(_T("ABtn_Play"), false);
			m_pHeaderMenu->SetElementDisabled(_T("ABtn_Pause"), true);
		});
		SwitchMode(AppMode::Pause);
	}
	else
	{
		m_pHeaderMenu->SetElementVisible(_T("ABtn_Play"), false);
		m_pHeaderMenu->SetElementVisible(_T("ABtn_Pause"), true);
		//delay so that it happens in another frame, 
		//if you would not do this, it will do both buttons
		Stopwatch::GetInstance()->CreateTimer(_T("delay_toggle_disable"), 0.05f, false, false, [&] () 
		{
			m_pHeaderMenu->SetElementDisabled(_T("ABtn_Play"), true);
			m_pHeaderMenu->SetElementDisabled(_T("ABtn_Pause"), false);
		});
		SwitchMode(m_PreviousAppMode);
	}
}

bool GameScreen::IsPaused() const
{
	return m_AppMode == AppMode::Pause;
}

void GameScreen::BroadCast(const tstring & status)
{
	m_pGameMenu->SetTextField(_T("Main_TextField_Status"), status);
}

void GameScreen::ReportStatus(const tstring & status)
{
	m_pStatusReport->ReportStatus(status);
}

void GameScreen::SwitchMode(AppMode mode)
{
	m_PreviousAppMode = m_AppMode;
	m_AppMode = mode;
	switch(m_AppMode)
	{
	case AppMode::Editor:
		m_pHeaderMenu->SetTextField(_T("NMode_Name"), _T("EDITOR"));
		SetGameSpeedTxtField();
		SetEditorHUD();
		m_StateMachine.SetState(_T("game"));
		break;
	case AppMode::Game:
		m_pHeaderMenu->SetTextField(_T("NMode_Name"), _T("PLAYING"));
		SetGameSpeedTxtField();
		SetGameHUD();
		m_StateMachine.SetState(_T("editor"));
		break;
	case AppMode::Pause:
		m_pHeaderMenu->SetTextField(_T("NMode_Name"), _T("PAUSED"));
		m_pHeaderMenu->SetTextField(_T("ATxt_GameSpeed"), _T("x0"));
		break;
	}
}

void GameScreen::AddHeaderMenuElements()
{
	m_pHeaderMenu->AddImage(0, 0, _T("Zheader_bg"), _T("Header_Background.png"));
	m_pHeaderMenu->AddTextField(900, 15, 200, 30, _T("NMode_Name"), _T("GLHF"), D3DXCOLOR(0.329f,0.251f,0.812f,1));
	m_pHeaderMenu->AddButton(1870,5, _T("ABtn_Quit"), _T("Header_Btn_Small_Shutdown.png"), [&] () 
	{ 
		QuitGame();
		ScreenManager::GetInstance()->QuitGame();
	});
	//fullscreen / windowed
	m_pHeaderMenu->AddButton(1820,5, _T("ABtn_FullScreen"), _T("Main_Button_Fullscreen.png"), [&] () 
	{ 
		Stopwatch::GetInstance()->CreateTimer(_T("GoFullScreen"), 0.05f, false, false, [&] () 
		{
			ScreenManager::GetInstance()->GetGame()->MaximizeWindow(true);
			m_pHeaderMenu->SetElementVisible(_T("ABtn_FullScreen"), false);
			m_pHeaderMenu->SetElementDisabled(_T("ABtn_FullScreen"), true);
			m_pHeaderMenu->SetElementVisible(_T("ABtn_Windowed"), true);
			m_pHeaderMenu->SetElementDisabled(_T("ABtn_Windowed"), false);
			ReportStatus(_T("Game is now fullScreen!"));
		});
	});
	m_pHeaderMenu->AddButton(1820,5, _T("ABtn_Windowed"), _T("Main_Button_Windowed.png"), [&] () 
	{
		Stopwatch::GetInstance()->CreateTimer(_T("GoWindowed"), 0.05f, false, false, [&] () 
		{
			ScreenManager::GetInstance()->GetGame()->MaximizeWindow(false);
			m_pHeaderMenu->SetElementVisible(_T("ABtn_FullScreen"), true);
			m_pHeaderMenu->SetElementDisabled(_T("ABtn_FullScreen"), false);
			m_pHeaderMenu->SetElementVisible(_T("ABtn_Windowed"), false);
			m_pHeaderMenu->SetElementDisabled(_T("ABtn_Windowed"), true);
			ReportStatus(_T("Game is now windowed!"));
		});
	});
	m_pHeaderMenu->SetElementVisible(_T("ABtn_Windowed"), false);
	m_pHeaderMenu->SetElementDisabled(_T("ABtn_Windowed"), true);
	//save
	m_pHeaderMenu->AddButton(1770,5, _T("ABtn_Save"), _T("Header_Btn_Small_Save.png"), [&] () 
	{ 
		SaveAll();
	});
	//Pause/Play
	m_pHeaderMenu->AddButton(1720,5, _T("ABtn_Pause"), _T("Header_Btn_Small_Pause.png"), [&] () { PauseGame(true); });
	m_pHeaderMenu->AddButton(1720,5, _T("ABtn_Play"), _T("Header_Btn_Small_Play.png"), [&] () { PauseGame(false); });
	m_pHeaderMenu->SetElementVisible(_T("ABtn_Play"), false);
	m_pHeaderMenu->SetElementDisabled(_T("ABtn_Play"), true);
	//Mute/Unmute
	m_pHeaderMenu->AddButton(1670,5, _T("ABtn_Mute"), _T("Main_Volume_Mute.png"), [&] () 
	{ 
		Stopwatch::GetInstance()->CreateTimer(_T("MuteVolume"), 0.05f, false, false, [&] () 
		{
			m_pHeaderMenu->SetElementVisible(_T("ABtn_Mute"), false);
			m_pHeaderMenu->SetElementDisabled(_T("ABtn_Mute"), true);
			m_pHeaderMenu->SetElementVisible(_T("ABtn_UnMute"), true);
			m_pHeaderMenu->SetElementDisabled(_T("ABtn_UnMute"), false);
			ReportStatus(_T("Master Volume muted!"));
			m_pPlayer->SetSetting(_T("MUTE_MASTER_VOLUME"), true);
		});
	});
	m_pHeaderMenu->AddButton(1670,5, _T("ABtn_UnMute"), _T("Main_Volume_Unmute.png"), [&] () 
	{
		Stopwatch::GetInstance()->CreateTimer(_T("UnmuteVolume"), 0.05f, false, false, [&] () 
		{
			m_pHeaderMenu->SetElementVisible(_T("ABtn_Mute"), true);
			m_pHeaderMenu->SetElementDisabled(_T("ABtn_Mute"), false);
			m_pHeaderMenu->SetElementVisible(_T("ABtn_UnMute"), false);
			m_pHeaderMenu->SetElementDisabled(_T("ABtn_UnMute"), true);
			ReportStatus(_T("Master Volume unmuted!"));
			m_pPlayer->SetSetting(_T("MUTE_MASTER_VOLUME"), false);
		});
	});
	bool masterVolumeMuted = m_pPlayer->GetSetting<bool>(_T("MUTE_MASTER_VOLUME"));
	if(masterVolumeMuted)
	{
		m_pHeaderMenu->SetElementVisible(_T("ABtn_Mute"), false);
		m_pHeaderMenu->SetElementDisabled(_T("ABtn_Mute"), true);
	}
	else
	{
		m_pHeaderMenu->SetElementVisible(_T("ABtn_UnMute"), false);
		m_pHeaderMenu->SetElementDisabled(_T("ABtn_UnMute"), true);
	}

	//todo: add master volume slider!

	//debug rendering buttons
	m_pHeaderMenu->AddButton(715,5, _T("ABtn_EnableRendering"), _T("Header_Btn_Rect_EnableDebugRendering.png"), [&] () 
	{
		Stopwatch::GetInstance()->CreateTimer(_T("RenderingRefresh"), 0.05f, false, false, [&] () 
		{
			m_pHeaderMenu->SetElementVisible(_T("ABtn_EnableRendering"), false);
			m_pHeaderMenu->SetElementDisabled(_T("ABtn_EnableRendering"), true);
			m_pHeaderMenu->SetElementVisible(_T("ABtn_DisableRendering"), true);
			m_pHeaderMenu->SetElementDisabled(_T("ABtn_DisableRendering"), false);
			ScreenManager::GetInstance()->SetPhysicsDrawEnabled(true);
			ReportStatus(_T("Physics Debug Rendering enabled!"));
		});
	});
	m_pHeaderMenu->AddButton(715,5, _T("ABtn_DisableRendering"), _T("Header_Btn_Rect_DisableDebugRendering.png"), [&] () 
	{ 
		Stopwatch::GetInstance()->CreateTimer(_T("RenderingRefresh"), 0.05f, false, false, [&] () 
		{
			m_pHeaderMenu->SetElementVisible(_T("ABtn_DisableRendering"), false);
			m_pHeaderMenu->SetElementDisabled(_T("ABtn_DisableRendering"), true);
			m_pHeaderMenu->SetElementVisible(_T("ABtn_EnableRendering"), true);
			m_pHeaderMenu->SetElementDisabled(_T("ABtn_EnableRendering"), false);
			ScreenManager::GetInstance()->SetPhysicsDrawEnabled(false);
			ReportStatus(_T("Physics Debug Rendering disabled!"));
		});
	});
	m_pHeaderMenu->SetElementVisible(_T("ABtn_EnableRendering"), false);
	m_pHeaderMenu->SetElementDisabled(_T("ABtn_EnableRendering"), true);
	//Reset Camera Transformation
	m_pHeaderMenu->AddButton(435,5, _T("ABtn_ResetCamera"), _T("Header_Btn_Rect_ResetCamera.png"), [&] () 
	{ 
			//m_pCamera->ResetTransformation();
			ReportStatus(_T("Editor camera has been reset!"));
	});
	m_pHeaderMenu->SetElementVisible(_T("ABtn_ResetCamera"), false);
	m_pHeaderMenu->SetElementDisabled(_T("ABtn_ResetCamera"), true);
	//Switch Between game and editor
	m_pHeaderMenu->AddButton(595,5, _T("ABtn_ModeGoToGame"), _T("Main_Button_Mode_Editor.png"), [&] () 
	{ 
		Stopwatch::GetInstance()->CreateTimer(_T("ModeSwitch"), 0.05f, false, false, [&] () 
		{
			ReportStatus(_T("Switched to game mode!"));
			m_pHeaderMenu->SetElementVisible(_T("ABtn_ModeGoToGame"), false);
			m_pHeaderMenu->SetElementDisabled(_T("ABtn_ModeGoToGame"), true);
			m_pHeaderMenu->SetElementVisible(_T("ABtn_ModeGoToEditor"), true);
			m_pHeaderMenu->SetElementDisabled(_T("ABtn_ModeGoToEditor"), false);
			SwitchMode(AppMode::Game);
		});
	});
	m_pHeaderMenu->AddButton(595,5, _T("ABtn_ModeGoToEditor"), _T("Main_Button_Mode_Game.png"), [&] () 
	{ 
		Stopwatch::GetInstance()->CreateTimer(_T("ModeSwitch"), 0.05f, false, false, [&] () 
		{
			ReportStatus(_T("Switched to editor mode!"));
			m_pHeaderMenu->SetElementVisible(_T("ABtn_ModeGoToGame"), true);
			m_pHeaderMenu->SetElementDisabled(_T("ABtn_ModeGoToGame"), false);
			m_pHeaderMenu->SetElementVisible(_T("ABtn_ModeGoToEditor"), false);
			m_pHeaderMenu->SetElementDisabled(_T("ABtn_ModeGoToEditor"), true);
			SwitchMode(AppMode::Editor);
		});
	});
	
	auto pFont35 = SpritefontManager::GetInstance()->CreateOrGet(_T("GameOver"), 35);
	m_pHeaderMenu->AddTextField(5,-5,100,30,_T("ATxt_FPS"), _T("60"), D3DXCOLOR(1,1,0,1), pFont35);

	//GameSpeed
	m_pHeaderMenu->AddImage(1062, 8, _T("AIcon_Clock"), _T("Header_Icon_Clock.png"));
	m_pHeaderMenu->AddTextField(1120,-5,100,30,_T("ATxt_GameSpeed"), _T("x1"), D3DXCOLOR(0.329f,0.251f,0.812f,1), pFont35);
	m_pHeaderMenu->AddTextField(1200,20,100,30,_T("ATxt_PlayerName"), m_pPlayer->GetName(), D3DXCOLOR(0.8f, 0.8f, 0.6f,1));
}

void GameScreen::AddMainMenuElements()
{
	m_pGameMenu->AddImage(0, 0, _T("Main_bg"), _T("GameMenu_Background.png"));
	m_pGameMenu->AddImage(655, 120, _T("Main_Icon_hearth"), _T("Main_Icon_Hearth.png"));
	m_pGameMenu->AddTextField(700, 130, 50, 30, _T("Main_TextField_Alive"), _T("00"), D3DXCOLOR(0.85f, 0.85f, 0.85f, 1.0f));
	m_pGameMenu->AddImage(745, 120, _T("Main_Icon_skull"), _T("Main_Icon_Skull.png"));
	m_pGameMenu->AddTextField(790, 130, 50, 30, _T("Main_TextField_Dead"), _T("00"), D3DXCOLOR(0.85f, 0.85f, 0.85f, 1.0f));
	m_pGameMenu->AddTextField(850, 130, 200, 30, _T("Main_TextField_Level"), _T("LevelName"), D3DXCOLOR(0.329f,0.251f,0.812f,1));

	//Status Bar
	auto pFont = SpritefontManager::GetInstance()->CreateOrGet(_T("GameOver"));
	m_pGameMenu->AddTextField(5, 120, 200, 30, _T("Main_TextField_Status"), _T("[00:00] TO DO CREATE STATUS SYSTEM!"), D3DXCOLOR(0.184f,0.565f,0.22f,1),pFont);

	//Counter Clock
	auto pFont35 = SpritefontManager::GetInstance()->CreateOrGet(_T("GameOver"), 35);
	m_pGameMenu->AddTextField(500, 109, 200, 30, _T("Main_TextField_Clock_Minuts"), _T("55"), D3DXCOLOR(0.85f, 0.85f, 0.85f, 1.0f),pFont35);
	m_pGameMenu->AddTextField(576, 109, 200, 30, _T("Main_TextField_Clock_Seconds"), _T("55"), D3DXCOLOR(0.85f, 0.85f, 0.85f, 1.0f),pFont35);

	//Big Square Buttons
	int bigBtnY(168);
	m_pGameMenu->AddAmountButton(0,bigBtnY,_T("Main_Button_Amount_A"), _T("Main_Btn_Sqrt_Big_A.png"), 0, [&] () { /* DO NOTHING IN THA BODY */ });
	m_pGameMenu->AddAmountButton(110,bigBtnY,_T("Main_Button_Amount_B"), _T("Main_Btn_Sqrt_Big_B.png"), 0, [&] () { /* DO NOTHING IN THA BODY */ });
	m_pGameMenu->AddAmountButton(220,bigBtnY,_T("Main_Button_Amount_C"), _T("Main_Btn_Sqrt_Big_C.png"), 0, [&] () { /* DO NOTHING IN THA BODY */ });
	// Unused button placeholders...
	//m_pGameMenu->AddAmountButton(330,bigBtnY,_T("Main_Button_Amount_D"), _T("Main_Btn_Sqrt_Big_D.png"), 0, [&] () { /* DO NOTHING IN THA BODY */ });
	//m_pGameMenu->AddAmountButton(440,bigBtnY,_T("Main_Button_Amount_E"), _T("Main_Btn_Sqrt_Big_E.png"), 0, [&] () { /* DO NOTHING IN THA BODY */ });
	//m_pGameMenu->AddAmountButton(550,bigBtnY,_T("Main_Button_Amount_F"), _T("Main_Btn_Sqrt_Big_F.png"), 0, [&] () { /* DO NOTHING IN THA BODY */ });
	//m_pGameMenu->AddAmountButton(660,bigBtnY,_T("Main_Button_Amount_G"), _T("Main_Btn_Sqrt_Big_G.png"), 0, [&] () { /* DO NOTHING IN THA BODY */ });
	//m_pGameMenu->AddAmountButton(770,bigBtnY,_T("Main_Button_Amount_H"), _T("Main_Btn_Sqrt_Big_H.png"), 0, [&] () { /* DO NOTHING IN THA BODY */ });
	//m_pGameMenu->AddAmountButton(880,bigBtnY,_T("Main_Button_Amount_I"), _T("Main_Btn_Sqrt_Big_I.png"), 0, [&] () { /* DO NOTHING IN THA BODY */ });
	//m_pGameMenu->AddAmountButton(990,bigBtnY,_T("Main_Button_Amount_J"), _T("Main_Btn_Sqrt_Big_J.png"), 0, [&] () { /* DO NOTHING IN THA BODY */ });

	//Big Rect Buttons
	m_pGameMenu->AddButton(1102,118,_T("Main_Button_Rect_A"), _T("Main_Btn_Rect_Big_A.png"), [&] () { /* DO NOTHING IN THA BODY */ });
	m_pGameMenu->AddButton(1204,118,_T("Main_Button_Rect_B"), _T("Main_Btn_Rect_Big_B.png"), [&] () { /* DO NOTHING IN THA BODY */ });
	m_pGameMenu->AddButton(1306,118,_T("Main_Button_Rect_C"), _T("Main_Btn_Rect_Big_C.png"), [&] () 
	{ 
		TimeManager::GetInstance()->IncreaseGameSpeed();
		SetGameSpeedTxtField();
	});
	m_pGameMenu->AddButton(1102,168,_T("Main_Button_Rect_D"), _T("Main_Btn_Rect_Big_D.png"), [&] () { /* DO NOTHING IN THA BODY */ });
	m_pGameMenu->AddButton(1204,168,_T("Main_Button_Rect_E"), _T("Main_Btn_Rect_Big_E.png"), [&] () { /* DO NOTHING IN THA BODY */ });
	m_pGameMenu->AddButton(1306,168,_T("Main_Button_Rect_F"), _T("Main_Btn_Rect_Big_F.png"), [&] () 
	{ 
		TimeManager::GetInstance()->ResetGameSpeed();
		SetGameSpeedTxtField();
	});
	m_pGameMenu->AddButton(1102,218,_T("Main_Button_Rect_G"), _T("Main_Btn_Rect_Big_G.png"), [&] () { /* DO NOTHING IN THA BODY */ });
	m_pGameMenu->AddButton(1204,218,_T("Main_Button_Rect_H"), _T("Main_Btn_Rect_Big_H.png"), [&] () { /* DO NOTHING IN THA BODY */ });
	m_pGameMenu->AddButton(1306,218,_T("Main_Button_Rect_I"), _T("Main_Btn_Rect_Big_I.png"), [&] () 
	{ 
		TimeManager::GetInstance()->DecreaseGameSpeed();
		SetGameSpeedTxtField();
	});

	//Camera information
	auto pBMFont = SpritefontManager::GetInstance()->CreateOrGet(_T("BitmapFont"), 8);
	m_pGameMenu->AddTextField(1425,245,350, 35, _T("Main_TextField_Info_Pos"), _T("POS(X=300.0 Y=10.0 Z=500.0)"), D3DXCOLOR(1,1,1,1), pBMFont);

	//Camera User Manipulation
	m_pGameMenu->AddTextField(1820,10,350, 35, _T("Main_TextField_Camera_RotSpeed"), 
		_T("rspd:") + m_pPlayer->GetSetting<tstring>(_T("EDITOR_CAMERA_ROT_SPEED")), D3DXCOLOR(0.184f,0.565f,0.22f,1), pBMFont);
	m_pGameMenu->AddButton(1818,40,_T("Main_Btn_Rspeed_n"), _T("Main_Btn_Sqrt_Mini_Minus.png"), [&] ()
	{
		/*m_pCamera->DecreaseRotSpeed();
		tstring speedString = XMLConverter::ConvertToTString(m_pCamera->GetRotSpeed());
		m_pGameMenu->SetTextField(_T("Main_TextField_Camera_RotSpeed"), _T("rspd:") + speedString);
		ReportStatus(_T("Changed camera rot. speed to ") + speedString + _T("."));*/
	});
	m_pGameMenu->AddButton(1865,40,_T("Main_Btn_Rspeed_p"), _T("Main_Btn_Sqrt_Mini_Plus.png"), [&] ()
	{
		/*m_pCamera->IncreaseRotSpeed();
		tstring speedString = XMLConverter::ConvertToTString(m_pCamera->GetRotSpeed());
		m_pGameMenu->SetTextField(_T("Main_TextField_Camera_RotSpeed"), _T("rspd:") + speedString);
		ReportStatus(_T("Changed camera rot. speed to ") + speedString + _T("."));*/
	});

	m_pGameMenu->AddTextField(1820,90,350, 35, _T("Main_TextField_Camera_FOV"), _T("FOV:") + m_pPlayer->GetSetting<tstring>(_T("EDITOR_CAMERA_FOV")), D3DXCOLOR(0.184f,0.565f,0.22f,1), pBMFont);
	m_pGameMenu->AddButton(1818,120,_T("Main_Btn_Fov_n"), _T("Main_Btn_Sqrt_Mini_Minus.png"), [&] () 
	{ 
		m_CameraFOV -= 5.0f;
		if(m_CameraFOV < 5.0f)
			m_CameraFOV = 5.0f;
		m_pActiveCamera->SetFieldOfView(LemmingsHelpers::ToRad(m_CameraFOV));
		tstring fovString = XMLConverter::ConvertToTString<float>(m_CameraFOV);
		m_pGameMenu->SetTextField(_T("Main_TextField_Camera_FOV"), _T("FOV:") + fovString);
		ReportStatus(_T("Changed camera FOV to ") + fovString + _T("."));
	});
	m_pGameMenu->AddButton(1865,120,_T("Main_Btn_Fov_p"), _T("Main_Btn_Sqrt_Mini_Plus.png"), [&] () 
	{ 
		m_CameraFOV += 5.0f;
		if(m_CameraFOV > 135.0f)
			m_CameraFOV = 135.0f;
		m_pActiveCamera->SetFieldOfView(LemmingsHelpers::ToRad(m_CameraFOV));
		tstring fovString = XMLConverter::ConvertToTString<float>(m_CameraFOV);
		m_pGameMenu->SetTextField(_T("Main_TextField_Camera_FOV"), _T("FOV:") + fovString);
		ReportStatus(_T("Changed camera FOV to ") + fovString + _T("."));
	});


	m_pGameMenu->AddTextField(1820,170,350, 35, _T("Main_TextField_Camera_Speed"), 
		_T("spd:") + m_pPlayer->GetSetting<tstring>(_T("EDITOR_CAMERA_SPEED")), D3DXCOLOR(0.184f,0.565f,0.22f,1), pBMFont);
	m_pGameMenu->AddButton(1818,200,_T("Main_Btn_Speed_n"), _T("Main_Btn_Sqrt_Mini_Minus.png"), [&] ()
	{
		//m_pCamera->DecreaseSpeed();
		/*tstring speedString =  XMLConverter::ConvertToTString(m_pCamera->GetMoveSpeed());
		m_pGameMenu->SetTextField(_T("Main_TextField_Camera_Speed"), _T("spd:") + speedString);
		ReportStatus(_T("Changed camera mov. speed to ") + speedString + _T("."));*/
	});
	m_pGameMenu->AddButton(1865,200,_T("Main_Btn_Speed_p"), _T("Main_Btn_Sqrt_Mini_Plus.png"), [&] ()
	{
		//m_pCamera->IncreaseSpeed();
		/*tstring speedString =  XMLConverter::ConvertToTString(m_pCamera->GetMoveSpeed());
		m_pGameMenu->SetTextField(_T("Main_TextField_Camera_Speed"), _T("spd:") + XMLConverter::ConvertToTString(m_pCamera->GetMoveSpeed()));
		ReportStatus(_T("Changed camera mov. speed to ") + speedString + _T("."));*/
	});
}

void GameScreen::StartGame()
{
	//Set Level Info
	m_pGameMenu->SetTextField(_T("Main_TextField_Level"), m_pLevel->GetLevelname());

	TimeManager::GetInstance()->StartTimer();
	//Stopwatch::GetInstance()->CreateTimer(_T("RefreshLevelTImer"), 1.0f, false, true, [&] () { m_RefreshLevelTimer = true; });

	ColissionCollector::GetInstance()->SetLevel(m_pLevel);
	ColissionCollector::GetInstance()->SetGameScreen(this);

	/*Stopwatch::GetInstance()->CreateTimer(_T("SpawnFirstEnemy"), 2.0f, false, false, [&] () { 
		m_pLemmingsCharacter = new LemmingCharacter(D3DXVECTOR3(305,340,350));
		AddSceneObject(m_pLemmingsCharacter);
		m_pLemmingsCharacter->Initialize();

		m_pLemmingsCharacter1 = new LemmingCharacter(D3DXVECTOR3(315,340,345));
		AddSceneObject(m_pLemmingsCharacter1);
		m_pLemmingsCharacter1->Initialize();

		m_pLemmingsCharacter2 = new LemmingCharacter(D3DXVECTOR3(325,340,340));
		AddSceneObject(m_pLemmingsCharacter2);
		m_pLemmingsCharacter2->Initialize();
	});*/

	ReportStatus(_T("Welcome in the Lemmings3D World ") + m_pPlayer->GetName() + _T("...")); 
	Stopwatch::GetInstance()->CreateTimer(_T("GLHF"), 5.0f, false, false, 
		[&] () {
			ReportStatus(_T("Good Luck and Have Fun!"));
	});


	
	Stopwatch::GetInstance()->CreateTimer(_T("EditorRefreshPositionTimer"), 0.5f, false, true, [&] () { m_BuildModePosRefresh = true; });
}

void GameScreen::QuitGame()
{
	ReportStatus(_T("Goodbye ") + m_pPlayer->GetName() + _T("!")); 
}

void GameScreen::SetGameSpeedTxtField()
{
	m_pHeaderMenu->SetTextField(_T("ATxt_GameSpeed"), _T("x") + XMLConverter::ConvertToTString<float>(TimeManager::GetInstance()->GetGameSpeed()));
}

void GameScreen::SetGameHUD()
{
	m_pHeaderMenu->SetElementVisible(_T("ABtn_ResetCamera"), false);
	m_pHeaderMenu->SetElementDisabled(_T("ABtn_ResetCamera"), true);
}

void GameScreen::SetEditorHUD()
{
	m_pHeaderMenu->SetElementVisible(_T("ABtn_ResetCamera"), true);
	m_pHeaderMenu->SetElementDisabled(_T("ABtn_ResetCamera"), false);
}

void GameScreen::SaveAll()
{
	/*auto transform = m_pCamera->GetComponent<TransformComponent>();
	m_pPlayer->SetSetting<D3DXVECTOR3>(_T("EDITOR_CAMERA_POS"), transform->GetWorldPosition());
	m_pPlayer->SetSetting<float>(_T("EDITOR_CAMERA_YAW"), m_pCamera->GetYaw());
	m_pPlayer->SetSetting<float>(_T("EDITOR_CAMERA_PITCH"), m_pCamera->GetPitch());
	m_pPlayer->SetSetting<float>(_T("EDITOR_CAMERA_FOV"), m_CameraFOV);
	m_pPlayer->SetSetting<int>(_T("EDITOR_CAMERA_SPEED"), m_pCamera->GetMoveSpeed());
	m_pPlayer->SetSetting<float>(_T("EDITOR_CAMERA_ROT_SPEED"), m_pCamera->GetRotSpeed());
	m_pPlayer->Save(); 
	m_pLevel->Save();
	ReportStatus(_T("Settings and level Saved for ") + m_pPlayer->GetName() + _T("."));*/
}