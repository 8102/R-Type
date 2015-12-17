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
		350,
		10,
		sf::Color::White,
		sf::Vector2f(1.0f, 1.0f),
		{ "explosion", "r-typesheet44.gif", "", sf::Color::Black }
	};

	_ammoConfigs["plasmaBullet"] = {
		std::string("r-typesheet1.gif"),
		std::string("plasmaBullet"),
		200,
		20,
		sf::Color::Black,
		sf::Vector2f(1.0f, 1.0f),
		{ "plasmaBoom", "plasmaBoom.png", "", sf::Color::White }
		//	{"plasmaExplosion", "r-typesheet1.gif", "", sf::Color::Black}
	};


	_ammoConfigs["rocket"] = {
		std::string("rocket.png"),
		std::string("rocket"),
		700,
		50,
		sf::Color::White,
		sf::Vector2f(0.25f, 0.25f),
		{"bigExplosion", "r-typesheet44.gif", "bigExplosion.wav", sf::Color::Black}
	};
	
	_ammoConfigs["spaceBomb"] = {
		std::string("r-typesheet3.gif"),
		std::string("spaceBomb"),
		500,
		75,
		sf::Color::Black,
		sf::Vector2f(2.0f, 2.0f),
		{ "bigExplosion", "r-typesheet44.gif", "bigExplosion.wav", sf::Color::Black }
	};
	
	_ammoConfigs["HBomb"] = {
		std::string("HBomb.png"),
		std::string("HBomb"),
		500,
		75,
		sf::Color::Black,
		sf::Vector2f(2.0f, 2.0f),
		{ "bigExplosion", "r-typesheet44.gif", "bigExplosion.wav", sf::Color::Black }
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
	clone->setScale(config.scale);
	clone->setDamage(config.damage);
//to be replaced by passing as struct
	clone->setDeathFX(config.fx.animationName, config.fx.ressourceName, config.fx.effectName, config.fx.colorMask);
	return clone;
}
