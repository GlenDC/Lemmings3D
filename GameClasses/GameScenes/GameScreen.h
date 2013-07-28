#pragma once
#include "BaseScreen.h"
#include "Graphics/SpriteBatch.h"

class GameEntity;
class ColissionEntity;
class GameModeScreen;
class EditorBuilder;
class Level;
class EditorCamera;
class UIDockInterface;
class SpriteFont;
class TimeManager;
class Player;
class StatusReport;
class RisingWater;
class LemmingCharacter;

class GameScreen: public BaseScreen
{
public:
	GameScreen();
	virtual ~GameScreen(void);

	virtual void Initialize();
	virtual void Update(const GameContext& context);
	virtual void Draw(const GameContext& context);

	virtual void Activated();
	virtual void Deactivated();

	void PauseGame(bool paused);

	bool IsPaused() const;

	void BroadCast(const tstring & status);
	void ReportStatus(const tstring & status);

	void AddEnvironmentCube(const D3DXVECTOR3 & pos, int id);
	bool RemoveEnvironmentCube(const D3DXVECTOR3 & pos);
	bool PaintEnvironmentCube(const D3DXVECTOR3 & pos, int id);
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
	Level * m_pLevel;
	EditorCamera *m_pCamera;

	UIDockInterface *m_pHeaderMenu;
	UIDockInterface *m_pGameMenu;

	SpriteFont *m_pDefaultFont;

	Player * m_pPlayer;

	LemmingCharacter * m_pLemmingsCharacter, *m_pLemmingsCharacter1, *m_pLemmingsCharacter2;

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

};

