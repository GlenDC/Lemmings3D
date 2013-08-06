#pragma once

//====================== #INCLUDES ===================================
#include "Helpers/stdafx.h"
#include "Helpers/D3DUtil.h"
#include "Helpers/GeneralStructs.h"
#include "Components/CameraComponent.h"
#include "Managers/InputManager.h"
#include "Graphics/SpriteBatch.h"
#include <vector>
//====================================================================

//====================== BaseCursor Class ============================
// Description:
//		Basic cursor logic.
// Last Modification: July 2013
// Glen De Cauwsemaecker
// www.glendc.com
//====================================================================

class BaseCursor
{
public:
	enum CursorStates
    {
        cursor_normal,
        cursor_menu
    };

	BaseCursor();	//Default constructor
	~BaseCursor();	//Default destructor

	virtual void Initialize();
	virtual void Update(const GameContext & context);
	virtual void Draw(const GameContext & context);
	
	void SetState(const CursorStates state);
	void SetPosition(const D3DXVECTOR2 & pos);
	bool InMenu() const { return m_CursorState == CursorStates::cursor_menu; }

	D3DXVECTOR2 GetCursorPosition() const { return m_Position; }
	D3DXVECTOR2 GetPreviousCursorPosition() const { return m_OldCursorPosition; }

protected:
	D3DXVECTOR2 m_Position, m_OldCursorPosition;
	CursorStates m_CursorState;

	bool m_LeftClicked;

	float m_MouseSpeed;
	int m_MouseCursorBorderScreen;

	SpriteInfo m_NormalTexture;

private:
	BaseCursor(const BaseCursor& yRef);									
	BaseCursor& operator=(const BaseCursor& yRef);
};