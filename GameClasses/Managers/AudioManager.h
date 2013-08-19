#pragma once

//====================== #INCLUDES ===================================
#include "IManager.h"
#include <vector>
#include "../../FMOD/FModSound.h"
#include "../../FMOD/FModSystem.h"
//====================================================================

//====================== AudioManager Class =========================
// Description:
//		management for songs and sound effects (both 2D)
// Last Modification: August 2013
// Glen De Cauwsemaecker
// www.glendc.com
//====================================================================

class Game;

// Ancillary class, implementing the Singleton Design pattern
class AudioManager : public IManager
{
public:
	~AudioManager(void);

	static AudioManager* GetInstance();

	void Initialize();
	void Update(GameContext& context);
	void Draw(GameContext& context);

	void PlaySoundEffect(const tstring & name);
	void PlaySong(const tstring & name);

	void SetIsMuted(bool is_muted);
	bool IsMuted() const;

private:
	AudioManager(void);
	static AudioManager* m_pInstance;
	tstring GetFile(const tstring & name);
	
	bool m_IsInitialized, m_IsMuted;

	FModSound *m_pCurrentSong;
	std::vector<FModSound*> m_Sounds;
	std::vector<FModSound*> m_GarbageSounds;

	// Disabling default copy constructor and default assignment operator.
	AudioManager(const AudioManager& t);
	AudioManager& operator=(const AudioManager& t);
};

