#pragma once
//====================== #INCLUDES ===================================
#include <memory>
#include "Helpers/SpriteFont.h"
#include "LoadingScreen.h"
//----------------------------------------------------------------------------
#include <thread>
//====================================================================

//====================== ShaderLoadingScreen Class ============================
// Description:
//		Loading screen for the shader demos
// Last Modification: August 2013
// Glen De Cauwsemaecker
// www.glendc.com
//====================================================================

class ShaderLoadingScreen: public LoadingScreen
{
public:
	ShaderLoadingScreen(const tstring & previousScreen);
	virtual ~ShaderLoadingScreen(void);

	virtual void Initialize();
	virtual void Update(const GameContext& context);
	virtual void Draw(const GameContext& context);

	virtual void BeginControl();
	virtual void EndControl();

	virtual void Activated();
	virtual void Deactivated();

private:
	std::thread m_Thread;

	// Disabling default copy constructor and default assignment operator.
	ShaderLoadingScreen(const ShaderLoadingScreen& yRef);									
	ShaderLoadingScreen& operator=(const ShaderLoadingScreen& yRef);
};
