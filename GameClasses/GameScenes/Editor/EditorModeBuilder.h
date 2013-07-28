#pragma once

//====================== #INCLUDES ===================================
#include "../../Interfaces/IEditMode.h"
//====================================================================

//====================== EditorModeBuilder Class =======================
// Description:
//		Builder Mode class (edit feature)
// Last Modification: 09/06/2013
// Copyright Glen De Cauwsemaecker
// www.glendc.com
//====================================================================

class EditorModeBuilder : public IEditMode
{
public:
	explicit EditorModeBuilder (EditorBuilder * pEditor);
	virtual ~EditorModeBuilder();

	virtual void Update(const GameContext & context);
	virtual void Draw(const GameContext & context);
	virtual void DrawMenu(const GameContext & context) {}

private:
	// -------------------------
	// Disabling default copy constructor and default 
	// assignment operator.
	// -------------------------
	EditorModeBuilder(const EditorModeBuilder& yRef);									
	EditorModeBuilder& operator=(const EditorModeBuilder& yRef);
};