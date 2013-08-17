#pragma once

//====================== #INCLUDES ===================================
#include "helpers/stdafx.h"
#include "helpers/d3dutil.h"
#include "helpers/generalstructs.h"
#include <memory>
//====================================================================

class IEditMode;
class EditModeScreen;
class PreviewObject;
class UIDockInterface;
class EditorModePainter;
class EditorModeBuilder;
class EditorModePlacer;
class EditorModeEraser;
class GameEntity;

//====================== EditorBuilder Class =========================
// Description:
//		Core Logic of editor!
// Last Modification: August 2013
// Glen De Cauwsemaecker
// www.glendc.com
//====================================================================

class EditorBuilder
{
public:
	explicit EditorBuilder(EditModeScreen * pEditor);
	~EditorBuilder(void);

	void Draw(const GameContext & context);
	void DrawSubMenu(const GameContext & context);
	void Update(const GameContext & context);

	void SetSnapPosition(const GameContext & context, const D3DXVECTOR3 & pos);
	void CalculatePositionFromEnvironment(const GameContext & context, const std::vector<D3DXVECTOR3> & posVec, 
		UINT length, const int accurary = 5, const UINT extraDistance = 350, const float distanceScalar = 1.0f);
	void CalculatePositionFromEnvironment(const GameContext & context);

	EditModeScreen * GetEditScreen() const { return m_pEditor; }

	void SetSettings();

private:
	enum class EditorMode : char 
	{
		build = 0,
		placing = 1,
		erase = 2,
		paint = 3
	};

	static const int EDITOR_MODE_COUNTER = 4;

	IEditMode * m_pModeArr[EDITOR_MODE_COUNTER];

	PreviewObject * m_pPreviewObject;
	GameEntity * m_pLocalFloor;
	D3DXVECTOR3 m_Position;
	std::vector<D3DXVECTOR3> m_SearchVec;

	EditModeScreen *m_pEditor;
	std::shared_ptr<UIDockInterface> m_pMainMenu;

	EditorMode m_EditorMode;

	friend class IEditMode;
	friend class EditorModePainter;
	friend class EditorModePlacer;
	friend class EditorModeBuilder;
	friend class EditorModeEraser;

	// Disabling default copy constructor and default assignment operator.
	EditorBuilder(const EditorBuilder& yRef);									
	EditorBuilder& operator=(const EditorBuilder& yRef);
};