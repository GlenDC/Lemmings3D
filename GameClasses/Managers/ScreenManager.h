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

enum class InputControls : char
{
	MOUSE_LEFT_PRESSED = 0,
	MOUSE_LEFT_DOWN = 1,
	MOUSE_RIGHT_PRESSED = 2,
	MOUSE_RIGHT_DOWN = 3,
	KB_ESCAPE_PRESSED = 4,
	KB_F10_PRESSED = 5,
	KB_F11_PRESSED = 6,
	KB_F12_PRESSED = 7,
	KB_ALT_DOWN = 8,
	KB_CTRL_DOWN = 9,
	KB_SHIFT_DOWN = 10
};

// Ancillary class, implementing the Singleton Design pattern
class ScreenManager : public IManager
{
public:
	~ScreenManager(void);

	static ScreenManager* GetInstance();

	void AddScreen(BaseScreen* screen);
	void RemoveScreen(BaseScreen* screen);

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

	void SetGame(Game * game) { m_MainGame = game; }
	InputManager * GetInputManager() { return m_pInputManager; }
	Game * GetGame() const { return m_MainGame; }

private:
	static const int NUM_SCREENS = 0;

	ScreenManager(void);

	Game* m_MainGame;
	vector<BaseScreen*> m_Screens;
	vector<BaseScreen*> m_ActiveScreens;

	BaseScreen* m_pControlScreen;

	static ScreenManager* m_pInstance;
	
	bool m_IsInitialized;
	bool m_Simulated;
	bool m_Fetched;
	bool m_PhysicsDisabled;
	bool m_EnablePhysicsRendering;
	bool m_LMBP, m_LMBD, m_RMBP, m_RMBD;

	shared_ptr<BaseCursor> m_pDefaultCursor, m_pCurrentCursor;

	InputManager * m_pInputManager;

	friend class BaseScreen;

	// Disabling default copy constructor and default assignment operator.
	ScreenManager(const ScreenManager& t);
	ScreenManager& operator=(const ScreenManager& t);
};