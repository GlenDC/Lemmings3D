//====================== #INCLUDES ===================================
#include "BaseScreen.h"
#include <memory>
#include "Helpers/SpriteFont.h"
//====================================================================

class UIDockInterface;

//====================== MainMenuScreen Class =========================
// Description:
//		Screen Class for the main menu
// Last Modification: August 2013
// Glen De Cauwsemaecker
// www.glendc.com
//====================================================================

class ColissionEntity;

class MainMenuScreen: public BaseScreen
{
public:
	MainMenuScreen(void);
	virtual ~MainMenuScreen(void);

	virtual void Initialize();
	virtual void Update(const GameContext& context);
	virtual void Draw(const GameContext& context);

	virtual void BeginControl();
	virtual void EndControl();

	virtual void Activated();
	virtual void Deactivated();

private:
	shared_ptr<SpriteFont> m_pSpriteFont;
	UIDockInterface * m_pMainMenuDock,
					* m_pLevelMenuDock,
					* m_pStatisticsDock;

	// Disabling default copy constructor and default assignment operator.
	MainMenuScreen(const MainMenuScreen& yRef);									
	MainMenuScreen& operator=(const MainMenuScreen& yRef);
};