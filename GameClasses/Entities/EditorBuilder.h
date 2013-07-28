#pragma once

//====================== #INCLUDES ===================================
#include "helpers/stdafx.h"
#include "helpers/d3dutil.h"
#include "helpers/generalstructs.h"
#include <memory>
//====================================================================

class PreviewObject;
class GameScreen;
class UIDockInterface;
class IEditMode;
class EditorModePainter;
class EditorModeBuilder;
class EditorModeEraser;

//====================== EditorBuilder Class =========================
// Description:
//		Building Logic of editor!
// Last Modification: 30/05/2013
// Copyright Glen De Cauwsemaecker
// www.glendc.com
//====================================================================

class EditorBuilder
{
public:
	explicit EditorBuilder(GameScreen * pGame);
	~EditorBuilder(void);

	void Draw(const GameContext & context);
	void DrawSubMenu(const GameContext & context);
	void Update(const GameContext & context);

	void SetSnapPosition(const GameContext & context, const D3DXVECTOR3 & pos);
	void CalculatePositionFromEnvironment(const GameContext & context, const std::vector<D3DXVECTOR3> & posVec, 
		UINT length, int accurary = 5, UINT extraDistance = 350, float distanceScalar = 1.0f);

private:
	enum class EditorMode : char 
	{
		build = 0,
		erase = 1,
		paint = 2
	};

	static const int EDITOR_MODE_COUNTER = 3;

	IEditMode * m_pModeArr[EDITOR_MODE_COUNTER];

	PreviewObject * m_pPreviewObject;
	D3DXVECTOR3 m_Position;
	std::vector<D3DXVECTOR3> m_SearchVec;

	GameScreen *m_pGame;
	UIDockInterface *m_pMainMenu;

	EditorMode m_EditorMode;

	friend class IEditMode;
	friend class EditorModePainter;
	friend class EditorModeBuilder;
	friend class EditorModeEraser;

	// -------------------------
	// Disabling default copy constructor and default 
	// assignment operator.
	// -------------------------
	EditorBuilder(const EditorBuilder& yRef);									
	EditorBuilder& operator=(const EditorBuilder& yRef);
};