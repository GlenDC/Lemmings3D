#pragma once

//====================== #INCLUDES ===================================
#include "../../Interfaces/IEditMode.h"
//====================================================================

class UIDockInterface;
class GameEntity;

//====================== EditorModePlacer Class =======================
// Description:
//		Class to build premade 3D models + their physics colission body
// Last Modification: August 2013
// Glen De Cauwsemaecker
// www.glendc.com
//====================================================================

class EditorModePlacer : public IEditMode
{
public:
	explicit EditorModePlacer (EditorBuilder * pEditor);
	virtual ~EditorModePlacer();

	virtual void Update(const GameContext & context);
	virtual void Draw(const GameContext & context);
	virtual void DrawMenu(const GameContext & context);

private:
	UINT m_ModelsCount, m_CurrentModelID;
	UIDockInterface *m_pModelMenu;
	std::vector<GameEntity*> m_PreviewObjects;

	// Disabling default copy constructor and default assignment operator.
	EditorModePlacer(const EditorModePlacer& yRef);									
	EditorModePlacer& operator=(const EditorModePlacer& yRef);
};