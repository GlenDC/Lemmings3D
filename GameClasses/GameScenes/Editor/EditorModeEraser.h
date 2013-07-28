#pragma once

//====================== #INCLUDES ===================================
#include "../../Interfaces/IEditMode.h"
//====================================================================

//====================== EditorModeEraser Class =======================
// Description:
//		Eraser Mode class (edit feature)
// Last Modification: 09/06/2013
// Copyright Glen De Cauwsemaecker
// www.glendc.com
//====================================================================

class EditorModeEraser : public IEditMode
{
public:
	explicit EditorModeEraser (EditorBuilder * pEditor);
	virtual ~EditorModeEraser();

	virtual void Update(const GameContext & context);
	virtual void Draw(const GameContext & context);
	virtual void DrawMenu(const GameContext & context) {}

private:
	// -------------------------
	// Disabling default copy constructor and default 
	// assignment operator.
	// -------------------------
	EditorModeEraser(const EditorModeEraser& yRef);									
	EditorModeEraser& operator=(const EditorModeEraser& yRef);
};