#pragma once

//====================== #INCLUDES ===================================
#include "BaseModeScreen.h"
//====================================================================

//====================== EditModeScreen Class =========================
// Description:
//		Screen State for the editor logic
// Last Modification: July 2013
// Glen De Cauwsemaecker
// www.glendc.com
//====================================================================

class GameEntity;
class EditorCamera;
class ColissionEntity;
class EditorBuilder;
class PhysicsCube;

class EditModeScreen : public BaseModeScreen
{
public:
	EditModeScreen(GameScreen * parent, InputManager * inputManager);
	virtual ~EditModeScreen(void);

	virtual void Initialize();
	virtual void Update(const GameContext& context);
	virtual void Draw(const GameContext& context);
	virtual void Draw2D(const GameContext& context);

	virtual void Activate();
	virtual void Deactivate();
	
private:
	void AddEnvironmentCube(const D3DXVECTOR3 & pos, const int id);
	bool RemoveEnvironmentCube(const D3DXVECTOR3 & pos);
	bool PaintEnvironmentCube(const D3DXVECTOR3 & pos, const int id);
	void RecheckEnvironment();
	void CalculateEditorCollision();

	std::vector<PhysicsCube*> m_EditorCubeVec;
	EditorBuilder *m_pBuilder;
	EditorCamera *m_pCamera;

	// Disabling default copy constructor and default assignment operator.
	EditModeScreen(const EditModeScreen& yRef);									
	EditModeScreen& operator=(const EditModeScreen& yRef);
};