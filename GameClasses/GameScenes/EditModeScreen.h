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
class Level;

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

	virtual void Save();

	void AddEnvironmentCube(const D3DXVECTOR3 & pos, const int id);
	bool RemoveEnvironmentCube(const D3DXVECTOR3 & pos);
	bool PaintEnvironmentCube(const D3DXVECTOR3 & pos, const int id);
	void RecheckEnvironment();

	std::shared_ptr<Level> GetCurrentLevel() const;
	
private:
	enum EntityMode : byte
	{
		mode_object = 0,
		mode_environment = 1
	};

	void CalculateEditorCollision();
	void ClearCollectionList();
	void CreateAndAddPhysicsCube(const D3DXVECTOR3 & pos, float size);
	void RemovePhysicsCube(const D3DXVECTOR3 & pos);

	std::vector<PhysicsCube*> m_EditorCubeVec;
	EditorBuilder *m_pBuilder;
	EditorCamera *m_pCamera;

	EntityMode m_EditorMode;

	// Disabling default copy constructor and default assignment operator.
	EditModeScreen(const EditModeScreen& yRef);									
	EditModeScreen& operator=(const EditModeScreen& yRef);
};