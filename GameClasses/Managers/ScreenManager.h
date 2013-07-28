#pragma once

//====================== #INCLUDES ===================================
#include "ManagerInterface.h"
//====================================================================

//====================== ScreenManager Class =========================
// Description:
//		Based on the original SceneManager Overlord class.
//		Reason for making a new class is to allow multiple "scenes"
//		or in my terms "screens" to be active at the same time.
//		being active mens that it will be drawn and updated every cpu tick!
// Last Modification: 04/03/2013
// Copyright Glen De Cauwsemaecker
// www.glendc.com
//====================================================================

class Game;
class BaseCursor;

enum class InputControls : int
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

class ScreenManager : public ManagerInterface
{
public:
	~ScreenManager(void);

	static ScreenManager* GetInstance()
	{
		if (m_pInstance == nullptr)
			m_pInstance = new ScreenManager();

		return m_pInstance;
	}

	void AddScreen(BaseScreen* screen);
	void RemoveScreen(BaseScreen* screen);

	bool AddActiveScreen(wstring name);
	bool RemoveActiveScreen(wstring name);

	bool SetControlScreen(wstring name);/*

	bool AddPhysicsDebugScreen(wstring name);
	bool RemovePhysicsDebugScreen(wstring name);*/

	virtual void Initialize();
	void InitializeContent();
	virtual void Update(GameContext& context);
	virtual void Draw(GameContext& context);
	void DrawCursor(const GameContext & context);

	void TogglePhysicsDisable() { m_PhysicsDisabled = !m_PhysicsDisabled; }

	D3DXVECTOR2 GetCursorPosition() const;
	bool LeftMouseButtonPressed() const;
	bool RightMouseButtonPressed() const;
	bool LeftMouseButtonDown() const;
	bool RightMouseButtonDown() const;

	bool CanDrawPhysics() const { return m_EnablePhysicsRendering; }

	void SetPhysicsDrawEnabled(bool enable);

	void SetGame(Game * game) { m_MainGame = game; }

	InputManager * GetInputManager() { return m_pInputManager; }

	Game * GetGame() const { return m_MainGame; }

private:

	ScreenManager(void);

	Game* m_MainGame;
	vector<BaseScreen*> m_Screens;
	vector<BaseScreen*> m_ActiveScreens;
/*
	vector<BaseScreen*> m_sPhysicsDebugScreens;*/

	BaseScreen * m_pControlScreen;

	static ScreenManager* m_pInstance;
	
	bool m_IsInitialized;
	friend class BaseScreen;
	bool m_Simulated;
	bool m_Fetched;
	bool m_PhysicsDisabled;
	bool m_EnablePhysicsRendering;
	bool m_LMBP, m_LMBD, m_RMBP, m_RMBD;

	BaseCursor *m_pDefaultCursor, *m_pCurrentCursor;

	InputManager * m_pInputManager;

private:
	friend class BaseScreen;

	// -------------------------
	// Disabling default copy constructor and default 
	// assignment operator.
	// -------------------------
	ScreenManager(const ScreenManager& t);
	ScreenManager& operator=(const ScreenManager& t);
};

