#include          "AmmoFactory.hh"
#include          "GameEngine.hh"

AmmoFactory::AmmoFactory(std::string const& configurationFileName)
	: _configurationFile(configurationFileName) {

}

AmmoFactory::~AmmoFactory() {}

bool                        AmmoFactory::loadAmmoConfigFromFile() {


	_ammoConfigs["simpleBullet"] = {
		std::string("r-typesheet43.gif"),
		std::string("bullet"),
		1000,
		sf::Color::White
	};

	_ammoConfigs["rocket"] = {
		std::string("rocket.png"),
		std::string("rocket"),
		1000,
		sf::Color::White
	};
	
	_ammoConfigs["spaceBomb"] = {
		std::string("r-typesheet3.gif"),
		std::string("spaceBomb"),
		1000,
		sf::Color::Black
	};
	return true;
}

void                        AmmoFactory::setConfigurationFile(std::string const& configurationFileName) {

	_configurationFile = configurationFileName;
}

std::string                 AmmoFactory::getConfigurationFile() const {

	return _configurationFile;
}

Ammunition*                 AmmoFactory::createAmmo(std::string const& ammunitionName, Ammunition::eTargets const& ammoType) {

	Ammunition*               clone = nullptr;
	struct s_ammunitionParams config;

	if (_ammoConfigs.find(ammunitionName) == _ammoConfigs.end())
		return nullptr;
	config = _ammoConfigs[ammunitionName];
	if ((clone = new Ammunition(
		*requestAssetManager.getTexture(config.textureFilename),
		requestGameEngine.getAnimation(config.animationName),
		config.ammoSpeed,
		config.colorMask
		)) == nullptr)
		return nullptr;
	clone->setType(ammoType);
	return clone;
}
