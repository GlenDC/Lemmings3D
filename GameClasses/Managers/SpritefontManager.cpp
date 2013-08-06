//====================== #INCLUDES ===================================
#include "SpritefontManager.h"
#include "../Entities/HashIdentifier.h"
#include "Helpers/SpriteFont.h"
#include "Managers/ContentManager.h"
//====================================================================

SpritefontManager * SpritefontManager::m_pInstance = nullptr;

SpritefontManager::SpritefontManager(void)
{

}

SpritefontManager::~SpritefontManager(void)
{
	m_Fonts.clear();
}

SpritefontManager* SpritefontManager::GetInstance()
{
	if (m_pInstance == nullptr)
	{
		m_pInstance = new SpritefontManager();
	}

	return m_pInstance;
}

void SpritefontManager::Initialize()
{

}

void SpritefontManager::Update(GameContext& context)
{

}

void SpritefontManager::Draw(GameContext& context)
{

}

shared_ptr<SpriteFont> SpritefontManager::CreateOrGet(const tstring & font)
{
	HashIdentifier identifier(font, 0);
	auto it = m_Fonts.find(identifier);
	if(it == m_Fonts.end())
	{
		tstringstream strstr;
		strstr << _T("./Resources/Lemmings3D/fonts/") << font << _T(".fnt");
		shared_ptr<SpriteFont> font(ContentManager::Load<SpriteFont>(strstr.str()));
		m_Fonts[identifier] = font;
	}
	return m_Fonts[identifier];
}

shared_ptr<SpriteFont> SpritefontManager::CreateOrGet(const tstring & font, UINT size)
{
	HashIdentifier identifier(font, size);
	auto it = m_Fonts.find(identifier);
	if(it == m_Fonts.end())
	{
		tstringstream strstr;
		strstr << _T("./Resources/Lemmings3D/fonts/") << font << _T("_") << size << _T(".fnt");
		shared_ptr<SpriteFont> font(ContentManager::Load<SpriteFont>(strstr.str()));
		m_Fonts[identifier] = font;
	}
	return m_Fonts[identifier];
}