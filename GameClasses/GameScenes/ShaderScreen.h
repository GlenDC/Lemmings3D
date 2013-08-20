//====================== #INCLUDES ===================================
#include "BaseScreen.h"
#include <memory>
#include <thread>
#include "Helpers/SpriteFont.h"
//====================================================================

class UIDockInterface;
class StateManager;

//====================== ShaderScreen Class =========================
// Description:
//		Screen class for the demo screen
// Last Modification: August 2013
// Glen De Cauwsemaecker
// www.glendc.com
//====================================================================

class ColissionEntity;
class GameObject;

class ShaderScreen: public BaseScreen
{
public:
	ShaderScreen(void);
	virtual ~ShaderScreen(void);

	virtual void Initialize();
	virtual void Update(const GameContext& context);
	virtual void Draw(const GameContext& context);

	virtual void BeginControl();
	virtual void EndControl();

	virtual void Activated();
	virtual void Deactivated();

private:
	shared_ptr<SpriteFont> m_pSpriteFont;
	UIDockInterface *m_pDemoDock, *m_pMenuDock;
	StateManager *m_pStates;

	std::thread m_Thread;

	// Disabling default copy constructor and default assignment operator.
	ShaderScreen(const ShaderScreen& yRef);									
	ShaderScreen& operator=(const ShaderScreen& yRef);
};