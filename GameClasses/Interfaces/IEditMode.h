#pragma once

//====================== #INCLUDES ===================================
#include "Helpers/stdafx.h"
#include "Helpers/D3DUtil.h"
#include "Helpers/GeneralStructs.h"
//====================================================================

class EditorBuilder;

//====================== EditMode Interface ============================
// Description:
//		Interface for all EditorModes
// Last Modification: July 2013
// Glen De Cauwsemaecker
// www.glendc.com
//====================================================================

// Base Class
class IEditMode
{
public:
	virtual ~IEditMode() { m_pEditor = nullptr; }

	virtual void Update(const GameContext & context) = 0;
	virtual void Draw(const GameContext & context) = 0;
	virtual void DrawMenu(const GameContext & context) = 0;

protected:
	explicit IEditMode (EditorBuilder * pEditor) 
		: m_pEditor(pEditor) { /* do nothing */ }

	EditorBuilder * m_pEditor;

private:
	// Disabling default copy constructor and default assignment operator.
	IEditMode(const IEditMode& yRef);									
	IEditMode& operator=(const IEditMode& yRef);
};