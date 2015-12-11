#include                "AssetManager.hh"

AssetManager&           AssetManager::instanciate() {

	static  AssetManager  instance;

	return instance;
}

AssetManager::AssetManager() : _audioEffects(EFFECT_FOLDER), _textures(TEXTURE_FOLDER), _musics(MUSIC_FOLDER), _fonts(FONT_FOLDER) {

}

AssetManager::~AssetManager() {
}

sf::SoundBuffer*          AssetManager::getSoundBuffer(std::string const& filename) {

	return  _audioEffects.getRessource(filename);
}

sf::Music*                AssetManager::getMusic(std::string const& filename) {

	return _musics.getRessource(filename);
}

sf::Texture*             AssetManager::getTexture(std::string const& filename) {

	return _textures.getRessource(filename);
}

sf::Font*                AssetManager::getFont(std::string const& filename) {

	return _fonts.getRessource(filename);
}
