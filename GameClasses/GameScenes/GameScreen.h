#pragma once

//====================== #INCLUDES ===================================
#include "BaseScreen.h"
//--------------------------------------------------------------------
#include "Graphics/SpriteBatch.h"
#include "Helpers/SpriteFont.h"
//--------------------------------------------------------------------
#include "../Entities/Level.h"
#include "../Managers/StateManager.h"
//--------------------------------------------------------------------
#include <memory>
//====================================================================

//====================== GameScreen Class ============================
// Description:
//		Main screen for the game (Lemmings 3D)
// Last Modification: July 2013
// Glen De Cauwsemaecker
// www.glendc.com
//====================================================================

class ColissionEntity;
class BaseCamera;
class GameEntity;
class Player;
class StatusReport;
class TimeManager;
class UIDockInterface;

class GameScreen : public BaseScreen
{
public:
	explicit GameScreen(const tstring & level_file, UINT level_id);
	virtual ~GameScreen(void);

	virtual void Initialize();
	virtual void Update(const GameContext& context);
	virtual void Draw(const GameContext& context);

	virtual void BeginControl();
	virtual void EndControl();

	virtual void Activated();
	virtual void Deactivated();

	void PauseGame(const bool paused);

	bool IsPaused() const;

	void BroadCast(const tstring & status);
	void ReportStatus(const tstring & status);

	shared_ptr<Level> GetLevel() const { return m_pLevel; }
	Player * GetPlayer() const { return m_pPlayer; }
	void SetState(const tstring & name_state);
	void SetPreviousState();
	void SetGameUIDisabled(bool disabled);

	void SetActiveCamera(BaseCamera * pCamera) { m_pActiveCameraObject = pCamera; }

	float GetCameraFOV() const { return m_CameraFOV; }

	void SaveLemming();

private:
	enum class AppMode : byte 
	{
		Game = 0,
		Pause = 1,
		Editor = 2
	};

	void SwitchMode(AppMode mode);
	void AddHeaderMenuElements();
	void AddMainMenuElements();
	void StartGame();
	void QuitGame();
	void SetGameSpeedTxtField();
	void SetGameHUD();
	void SetEditorHUD();
	void SaveAll();

	shared_ptr<Level> m_pLevel;

	UIDockInterface *m_pHeaderMenu;
	UIDockInterface *m_pGameMenu;

	shared_ptr<SpriteFont> m_pDefaultFont;

	Player * m_pPlayer;

	StatusReport * m_pStatusReport;

	BaseCamera * m_pActiveCameraObject;

	AppMode m_AppMode, m_PreviousAppMode;
	StateManager m_StateMachine;

	bool	m_RefreshLevelTimer,
			m_BuildModePosRefresh;

	UINT m_LevelID, m_LemmingsSaved;

	//Camera info
	float m_CameraFOV, m_CameraZoom, m_CameraSpeed;
	
	ID3D10ShaderResourceView *m_pCameraRotationTexture;
	SpriteInfo m_CameraRotationSprite;

	tstring m_LevelFile;

	friend class TimeManager;

	// Disabling default copy constructor and default assignment operator.
	GameScreen(const GameScreen& yRef);									
	GameScreen& operator=(const GameScreen& yRef);
};