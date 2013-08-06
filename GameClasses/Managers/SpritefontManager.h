#pragma once

//====================== #INCLUDES ===================================
#include "IManager.h"
#include <map>
#include <memory>
//====================================================================

//====================== SpritefontManager Class =====================
// Description:
//		A singleton implementation, to collect all the spritfonts used in this game.
// Last Modification: August 2013
// Glen De Cauwsemaecker
// www.glendc.com
//====================================================================

class Game;
class HashIdentifier;
class SpriteFont;

// Ancillary class, implementing the Singleton Design pattern
class SpritefontManager : public IManager
{
public:
	~SpritefontManager(void);

	static SpritefontManager* GetInstance();

	void Initialize();
	void Update(GameContext& context);
	void Draw(GameContext& context);
	
	shared_ptr<SpriteFont> CreateOrGet(const tstring & font);
	shared_ptr<SpriteFont> CreateOrGet(const tstring & font, UINT size);

private:
	SpritefontManager(void);
	static SpritefontManager* m_pInstance;

	map<HashIdentifier, shared_ptr<SpriteFont>> m_Fonts;
	
	bool m_IsInitialized;

	// Disabling default copy constructor and default assignment operator.
	SpritefontManager(const SpritefontManager& t);
	SpritefontManager& operator=(const SpritefontManager& t);
};

