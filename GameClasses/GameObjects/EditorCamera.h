#pragma once

//====================== #INCLUDES ===================================
#include "BaseCamera.h"
//====================================================================

//====================== EditorCamera Class =========================
// Description:
//		Camera for the LevelEditor 
// Last Modification: July 2013
// Glen De Cauwsemaecker
// www.glendc.com
//====================================================================

struct GameContext;
class CameraComponent;

class EditorCamera : public BaseCamera
{
public:
	EditorCamera(void);
	~EditorCamera(void);

	void SetCanControl(bool can_control) { m_CanControl = can_control; }

protected:
	bool m_CanControl;

	virtual void Initialize();
	virtual void Update(const GameContext& context);

private:
	// Disabling default copy constructor and default assignment operator.
	EditorCamera(const EditorCamera& yRef);									
	EditorCamera& operator=(const EditorCamera& yRef);
};

