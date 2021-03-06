#pragma once

//====================== #INCLUDES ===================================
#include "IManager.h"
#include <memory>
//====================================================================

//====================== ScreenManager Class =========================
// Description:
//		Based on the original SceneManager Overlord class.
//		Reason for making a new class is to allow multiple "scenes"
//		or in my terms "screens" to be active at the same time.
//		being active mens that it will be drawn and updated every cpu tick!
// Last Modification: July 2013
// Glen De Cauwsemaecker
// www.glendc.com
//====================================================================

class BaseCursor;
class Game;

enum class InputControls : int
{
	MOUSE_LEFT_PRESSED = 0,
	MOUSE_LEFT_DOWN,
	MOUSE_RIGHT_PRESSED,
	MOUSE_RIGHT_DOWN,
	KB_ESCAPE_PRESSED,
	KB_F10_PRESSED,
	KB_F11_PRESSED,
	KB_F12_PRESSED,
	KB_ALT_DOWN,
	KB_CTRL_DOWN,
	KB_SHIFT_DOWN,
	KB_RETURN_PRESSED,
	KB_O_PRESSED,
	KB_P_PRESSED
};

// Ancillary class, implementing the Singleton Design pattern
class ScreenManager : public IManager
{
public:
	~ScreenManager(void);

	static ScreenManager* GetInstance();

	void AddScreen(BaseScreen* screen);
	void RemoveScreen(BaseScreen* screen);
	void RemoveScreen(const tstring & name);

	bool AddActiveScreen(const tstring & name);
	bool RemoveActiveScreen(const tstring & name);

	bool SetControlScreen(const tstring & name);

	void Initialize();
	void InitializeContent();
	void Update(GameContext& context);
	void Draw(GameContext& context);
	void DrawCursor(const GameContext & context);

	void TogglePhysicsDisable() { m_PhysicsDisabled = !m_PhysicsDisabled; }

	D3DXVECTOR2 GetCursorPosition() const;
	bool LeftMouseButtonPressed() const;
	bool RightMouseButtonPressed() const;
	bool LeftMouseButtonDown() const;
	bool RightMouseButtonDown() const;

	bool CanDrawPhysics() const { return m_EnablePhysicsRendering; }

	void SetPhysicsDrawEnabled(const bool enable);
	void SetPreviousPhysicsDrawEnabled();

	void SetGame(Game * game) { m_MainGame = game; }
	InputManager * GetInputManager() { return m_pInputManager; }
	Game * GetGame() const { return m_MainGame; }

	void QuitGame();

private:
	static const int NUM_SCREENS = 0;

	ScreenManager(void);

	Game* m_MainGame;
	vector<BaseScreen*> m_Screens;
	vector<BaseScreen*> m_ActiveScreens;
	vector<BaseScreen*> m_GarbageScreens;

	BaseScreen* m_pControlScreen;

	static ScreenManager* m_pInstance;
	
	bool	m_IsInitialized,
			m_Simulated,
			m_Fetched,
			m_PhysicsDisabled,
			m_EnablePhysicsRendering,
			m_PreviousEnablePhyicsRendering,
			m_LMBP,
			m_LMBD,
			m_RMBP,
			m_RMBD;

	double m_TimeCounter;

	shared_ptr<BaseCursor> m_pDefaultCursor, m_pCurrentCursor;

	InputManager * m_pInputManager;

	friend class BaseScreen;

	// Disabling default copy constructor and default assignment operator.
	ScreenManager(const ScreenManager& t);
	ScreenManager& operator=(const ScreenManager& t);
};