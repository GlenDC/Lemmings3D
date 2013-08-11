//====================== #INCLUDES ===================================
#include <memory>
#include "Helpers/SpriteFont.h"
#include "LoadingScreen.h"
//----------------------------------------------------------------------------
#include <thread>
//====================================================================

//====================== GameLoadingScreen Class ============================
// Description:
//		Screen Class for the main menu
// Last Modification: August 2013
// Glen De Cauwsemaecker
// www.glendc.com
//====================================================================

class GameLoadingScreen: public LoadingScreen
{
public:
	GameLoadingScreen(const tstring & previousScreen, UINT leveL_id);
	virtual ~GameLoadingScreen(void);

	virtual void Initialize();
	virtual void Update(const GameContext& context);
	virtual void Draw(const GameContext& context);

	virtual void BeginControl();
	virtual void EndControl();

	virtual void Activated();
	virtual void Deactivated();

private:

	UINT m_LevelID;
	std::thread m_Thread;

	// Disabling default copy constructor and default assignment operator.
	GameLoadingScreen(const GameLoadingScreen& yRef);									
	GameLoadingScreen& operator=(const GameLoadingScreen& yRef);
};
