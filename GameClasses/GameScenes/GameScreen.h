#pragma once

//====================== #INCLUDES ===================================
#include "BaseScreen.h"
#include "Graphics/SpriteBatch.h"
#include "Helpers/SpriteFont.h"
#include "../Entities/Level.h"

#include <memory>
//====================================================================

//====================== GameScreen Class =========================
// Description:
//		Main screen for the game (Lemmings 3D)
// Last Modification: July 2013
// Glen De Cauwsemaecker
// www.glendc.com
//====================================================================

class ColissionEntity;
class EditorCamera;
class EditorBuilder;
class GameEntity;
class GameModeScreen;
class LemmingCharacter;
class Player;
class RisingWater;
class StatusReport;
class TimeManager;
class UIDockInterface;

class GameScreen : public BaseScreen
{
public:
	GameScreen();
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

	void AddEnvironmentCube(const D3DXVECTOR3 & pos, const int id);
	bool RemoveEnvironmentCube(const D3DXVECTOR3 & pos);
	bool PaintEnvironmentCube(const D3DXVECTOR3 & pos, const int id);
	void RecheckEnvironment();

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

	GameModeScreen *m_pGame;
	EditorBuilder *m_pBuilder;
	shared_ptr<Level> m_pLevel;
	EditorCamera *m_pCamera;

	UIDockInterface *m_pHeaderMenu;
	UIDockInterface *m_pGameMenu;

	shared_ptr<SpriteFont> m_pDefaultFont;

	Player * m_pPlayer;

	LemmingCharacter	*m_pLemmingsCharacter, 
						*m_pLemmingsCharacter1, 
						*m_pLemmingsCharacter2;

	StatusReport * m_pStatusReport;

	AppMode m_AppMode, m_PreviousAppMode;

	RisingWater *m_pRisingWater;

	bool m_RefreshLevelTimer;
	bool m_BuildModePosRefresh;

	//Camera info
	float m_CameraFOV, m_CameraZoom, m_CameraSpeed;
	
	ID3D10ShaderResourceView *m_pCameraRotationTexture;
	SpriteInfo m_CameraRotationSprite;

	friend class TimeManager;

	// Disabling default copy constructor and default assignment operator.
	GameScreen(const GameScreen& yRef);									
	GameScreen& operator=(const GameScreen& yRef);
};