#pragma once

//====================== #INCLUDES ===================================
#include "../../Interfaces/IEditMode.h"
//====================================================================

class UIDockInterface;

//====================== EditModePainter Class =======================
// Description:
//		Painter Mode class (edit feature)
// Last Modification: July 2013
// Glen De Cauwsemaecker
// www.glendc.com
//====================================================================

class EditorModePainter : public IEditMode
{
public:
	explicit EditorModePainter (EditorBuilder * pEditor);
	virtual ~EditorModePainter();

	virtual void Update(const GameContext & context);
	virtual void Draw(const GameContext & context);
	virtual void DrawMenu(const GameContext & context);

private:
	enum class PaintMode : char 
	{
		rock = 0,
		grass = 1,
		trunk = 2
	};

	static const int PaintModes = 3;

	PaintMode m_PaintMode;

	UIDockInterface *m_pPaintMenu;

	// Disabling default copy constructor and default assignment operator.
	EditorModePainter(const EditorModePainter& yRef);									
	EditorModePainter& operator=(const EditorModePainter& yRef);
};