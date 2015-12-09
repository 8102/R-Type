#ifndef                     ___SOUND_SYSTEM_HH___
# define                    ___SOUND_SYSTEM_HH___

#include                    <string>
#include                    <map>
#include                    <iostream>
#include                    <deque>

#include                    <SFML/Audio/Music.hpp>
#include                    <SFML/Audio/Sound.hpp>
#include                    <SFML/Audio/SoundBuffer.hpp>

#include                    "AssetManager.hh"
#include                    "Client_graphicUtils.hh"

// Singleton SoundSystem :
//   Handle a vector of souneffects ordred by name (std::string)
//   Manage all audio outputs from the program
//   as well as a vector of musics equally oredred by name

class                       SoundSystem
{
public:

	static SoundSystem&              instanciate();

private:

	SoundSystem();

public:

	~SoundSystem();

public:

	void                     update();

	bool                     addEffect(std::string const& filename);
	bool                     addMusic(std::string const& filename);

	void                     playMusic();
	void                     playEffect(std::string const& effect);
	void                     pushEffect(std::string const& effect);


	sf::Music&               getCurrentMusic();

	void                     setCurrentMusic(std::string const& musicName);

public:

	float                    getEffectVolume() const;
	float                    getMusicVolume() const;
	float                    getMasterVolume() const;

public:

	void                     setEffectVolume(float const& volume);
	void                     setMusicVolume(float const& volume);
	void                     setMasterVolume(float const& volume);

	// public:
	//
	//   unsigned int             getEffectIndex() const;
	//   unsigned int             getMusicIndex() const;

private:

	float                    _effectVolume;
	float                    _musicVolume;
	float                    _masterVolume;

private:

	unsigned int             _effectsIndex;
	unsigned int             _musicIndex;

private:

	std::vector < std::pair < std::string, sf::Sound* > >         _effects;
	std::vector < std::pair < std::string, sf::Music* > >         _musics;

	std::deque  < sf::Sound* >      _playedEffects;

};


#endif                      /* !___SOUND_SYSTEM_HH___ */
