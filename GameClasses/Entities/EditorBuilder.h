#pragma once

//====================== #INCLUDES ===================================
#include "helpers/stdafx.h"
#include "helpers/d3dutil.h"
#include "helpers/generalstructs.h"
#include <memory>
//====================================================================

class IEditMode;
class BuildModeScreen;
class PreviewObject;
class UIDockInterface;
class EditorModePainter;
class EditorModeBuilder;
class EditorModeEraser;

//====================== EditorBuilder Class =========================
// Description:
//		Building Logic of editor!
// Last Modification: July 2013
// Glen De Cauwsemaecker
// www.glendc.com
//====================================================================

class EditorBuilder
{
public:
	explicit EditorBuilder(BuildModeScreen * pEditor);
	~EditorBuilder(void);

	void Draw(const GameContext & context);
	void DrawSubMenu(const GameContext & context);
	void Update(const GameContext & context);

	void SetSnapPosition(const GameContext & context, const D3DXVECTOR3 & pos);
	void CalculatePositionFromEnvironment(const GameContext & context, const std::vector<D3DXVECTOR3> & posVec, 
		UINT length, const int accurary = 5, const UINT extraDistance = 350, const float distanceScalar = 1.0f);
	void CalculatePositionFromEnvironment(const GameContext & context);

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

	BuildModeScreen *m_pEditor;
	std::shared_ptr<UIDockInterface> m_pMainMenu;

	EditorMode m_EditorMode;

	friend class IEditMode;
	friend class EditorModePainter;
	friend class EditorModeBuilder;
	friend class EditorModeEraser;

	// Disabling default copy constructor and default assignment operator.
	EditorBuilder(const EditorBuilder& yRef);									
	EditorBuilder& operator=(const EditorBuilder& yRef);
};