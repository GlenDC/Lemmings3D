//====================== #INCLUDES ===================================
#include "AudioManager.h"
#include "Game.h"
//--------------------------------------------------------------------
#include <algorithm>
#include "ParameterManager.h"
#include "../Entities/ParameterClass.h"
//====================================================================

AudioManager* AudioManager::m_pInstance = nullptr;

// private constructor
AudioManager::AudioManager(void)
	: m_IsInitialized(false)
	, m_pCurrentSong(nullptr)
	, m_Sounds(0)
	, m_GarbageSounds(0)
	, m_IsMuted(false)
{
}

// public destructor
AudioManager::~AudioManager(void)
{
	for ( auto effect : m_Sounds)
	{
		SafeDelete(effect);
	}
	m_Sounds.clear();
	m_pCurrentSong = nullptr;
}

// receive a poiner to the object, 
// and create it first if the object isn't created yet.
AudioManager* AudioManager::GetInstance()
{
	if (m_pInstance == nullptr)
	{
		m_pInstance = new AudioManager();
	}
	return m_pInstance;
}

// initialize the console manager only once per session.
void AudioManager::Initialize()
{
	if(!m_IsInitialized) 
	{
		// initialize nothing
		m_IsInitialized = true;
	}
}

// update nothing
void AudioManager::Update(GameContext& context)
{
	for ( auto effect : m_Sounds )
	{
		effect->SetMuted(m_IsMuted);
		if(!effect->IsPlaying())
		{
			m_GarbageSounds.push_back(effect);
		}
	}
	for ( auto dirt : m_GarbageSounds )
	{
		auto it = std::find(m_Sounds.begin(), m_Sounds.end(), dirt);
		m_Sounds.erase(it);
		if(dirt == m_pCurrentSong)
		{
			m_pCurrentSong = nullptr;
		}
		SafeDelete(dirt);
	}
	m_GarbageSounds.clear();
}

// draw nothing
void AudioManager::Draw(GameContext& context)
{
	// draw sound ? ah , funny, but cool... 
}

void AudioManager::PlaySoundEffect(const tstring & name)
{
	FModSound * sound = new FModSound();
	sound->CreateSound(GetFile(name));
	sound->Play();
	sound->SetMuted(m_IsMuted);
	m_Sounds.push_back(sound);
}

void AudioManager::PlaySong(const tstring & name)
{
	if(m_pCurrentSong != nullptr)
	{
		m_pCurrentSong->Stop();
		auto it = std::find(m_Sounds.begin(), m_Sounds.end(), m_pCurrentSong);
		m_Sounds.erase(it);
		SafeDelete(m_pCurrentSong);
	}
	FModSound * sound = new FModSound();
	sound->CreateStream(GetFile(name));
	sound->Play();
	sound->SetMuted(m_IsMuted);
	m_pCurrentSong = sound;
	m_Sounds.push_back(sound);
}

void AudioManager::SetIsMuted(bool is_muted)
{
	m_IsMuted = is_muted;
	for ( auto effect : m_Sounds )
	{
		effect->SetMuted(is_muted);
	}
}

bool AudioManager::IsMuted() const
{
	return m_IsMuted;
}

tstring AudioManager::GetFile(const tstring & name)
{
	auto & parameters = ParameterManager::GetInstance()->CreateOrGet(_T("Audio"));
	tstringstream strstr;
	strstr << _T("./Resources/Lemmings3D/audio/") << parameters.GetParameter<tstring>(name);

	return strstr.str();
}