//====================== #INCLUDES ===================================
#include "BaseModeScreen.h"
//--------------------------------------------------------------------
#include "OverlordComponents.h"
#include "Game.h"
#include "Graphics/GraphicsDevice.h"
#include "Helpers/D3DUtil.h"
#include "Helpers/SpriteFont.h"
#include "Helpers/GeneralStructs.h"
#include "Managers/ContentManager.h"
#include "Scenegraph/GameObject.h"
//--------------------------------------------------------------------
#include "../Entities/ParameterClass.h"
#include "../GameObjects/GameEntity.h"
#include "../GameObjects/ColissionEntity.h"
#include "../Managers/ScreenManager.h"
#include "../Managers/Stopwatch.h"
#include "../Managers/SpritefontManager.h"
#include "../UserInterface/BaseCursor.h"
#include "../XML/XMLConverter.h"
//====================================================================

// Protected constructor
BaseModeScreen::BaseModeScreen(GameScreen * parent, const InputManager *inputManager)
	: State()
	, m_pParentScreen(parent)
	, m_pInputManager(inputManager)
{
	m_pDefaultFont = SpritefontManager::GetInstance()->CreateOrGet(_T("ComicSansMs"), 25);
}