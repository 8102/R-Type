#include      "SoundSystem.hh"

SoundSystem::SoundSystem()
	: _effectVolume(50.0f), _musicVolume(50.0f), _masterVolume(0.3f),
	_effectsIndex(0), _musicIndex(0) {

}

/*
** Only cleaning Sound <map> :
** RessourceManager< SoundTrack > is in charge for musics
*/
SoundSystem::~SoundSystem() {

	for (auto it = _playedEffects.begin(); it != _playedEffects.end(); it++) {
		(*it)->stop();
		delete *it;
	}
	for (auto it = _effects.begin(); it != _effects.end(); it++)
	{
		delete it->second;
		it->second = nullptr;
	}
}

void                      SoundSystem::update() {

	for (auto it = _playedEffects.begin(); it != _playedEffects.end();)
	{
		if ((*it)->getStatus() == sf::Sound::Stopped) {
			delete *it;
			it = _playedEffects.erase(it);
		}
		else it++;
	}
}

bool                      SoundSystem::addEffect(std::string const& filename) {

	sf::Sound*              sound = new sf::Sound();
	sf::SoundBuffer*        buffer;

	if ((buffer = AssetManager::instanciate().getSoundBuffer(filename)) == nullptr) {
		return false;
	}
	sound->setBuffer(*buffer);
	sound->setVolume(_effectVolume * _masterVolume);
	_effects.push_back(std::pair<std::string, sf::Sound*>(filename, sound));
	return true;
}

void                      SoundSystem::pushEffect(std::string const& filename) {

	sf::Sound*              sound = nullptr;

	for (auto it = _effects.begin(); it != _effects.end(); it++)
		if (it->first == filename) sound = new sf::Sound(*it->second);
	if (sound != nullptr) {
		sound->setVolume(_effectVolume * _masterVolume);
		_playedEffects.push_back(sound);
		sound->play();
	}
}


bool                      SoundSystem::addMusic(std::string const& filename) {

	sf::Music*              music;

	if ((music = AssetManager::instanciate().getMusic(filename)) == nullptr) {
		return false;
	}
	_musics.push_back(std::pair<std::string, sf::Music*>(filename, music));
	return true;
}

void                      SoundSystem::playMusic() {

	sf::Music*              music = _musics[_musicIndex].second;

	if (music != nullptr) {
		music->setVolume(_musicVolume * _masterVolume);
		music->play();
	}
}

void                      SoundSystem::playEffect(std::string const& effectName)
{
	for (auto it = _effects.begin(); it != _effects.end(); it++) {
		if (it->first == effectName) { it->second->play(); break; }
	}
}

void                      SoundSystem::setCurrentMusic(std::string const& musicName) {

	for (auto it = _musics.begin(); it != _musics.end(); it++)
	{
		if (it->first == musicName)
			_musicIndex = static_cast< unsigned int >(it - _musics.begin());
	}
}

float                      SoundSystem::getEffectVolume() const {

	return _effectVolume;
}

float                     SoundSystem::getMusicVolume() const {

	return _musicVolume;
}

float                     SoundSystem::getMasterVolume() const {

	return _masterVolume;
}

void                      SoundSystem::setEffectVolume(float const& volume) {

	_effectVolume = volume;
	// for (auto it  = _playedEffects.begin(); it != _playedEffects.end(); it++)
	//   (*it)->setVolume(_effectVolume * _masterVolume);
}

void                      SoundSystem::setMusicVolume(float const& volume) {

	_musicVolume = volume;
	getCurrentMusic().setVolume(_musicVolume * _masterVolume);
}

void                      SoundSystem::setMasterVolume(float const& volume) {

	_masterVolume = volume / 100;
	//  if (_musics[_musicIndex] != nullptr) {
	_musics[_musicIndex].second->setVolume(_musicVolume * _masterVolume);
	// }
	for (auto it = _playedEffects.begin(); it != _playedEffects.end(); it++)
		(*it)->setVolume(_effectVolume * _masterVolume);
}

sf::Music&                SoundSystem::getCurrentMusic() {

	return *_musics[_musicIndex].second;
}

SoundSystem&              SoundSystem::instanciate() {

	static SoundSystem      instance;

	return instance;
}
