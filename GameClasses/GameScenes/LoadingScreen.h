//====================== #INCLUDES ===================================
#include "BaseScreen.h"
#include <memory>
#include "Helpers/SpriteFont.h"
//====================================================================

class UIDockInterface;

//====================== LoadingScreen Class ============================
// Description:
//		Screen Class for a loading screen
// Last Modification: August 2013
// Glen De Cauwsemaecker
// www.glendc.com
//====================================================================

class LoadingScreen: public BaseScreen
{
public:
	LoadingScreen(const tstring & previousScreen);
	virtual ~LoadingScreen(void);

	virtual void Initialize();
	virtual void Update(const GameContext& context);
	virtual void Draw(const GameContext& context);

	virtual void BeginControl();
	virtual void EndControl();

	virtual void Activated();
	virtual void Deactivated();

	void SetLoadingDescription(const tstring & description);

private:
	static const unsigned int MAX_DOTS = 3;
	shared_ptr<SpriteFont> m_pSpriteFont;
	float m_LoadTime;
	bool m_RemovedPrevious;

protected:
	tstring m_PreviousScreenName;
	tstring m_LoadingDescription;
	tstring m_TipID;
	UIDockInterface * m_pUIDock;

private:
	// Disabling default copy constructor and default assignment operator.
	LoadingScreen(const LoadingScreen& yRef);									
	LoadingScreen& operator=(const LoadingScreen& yRef);
};