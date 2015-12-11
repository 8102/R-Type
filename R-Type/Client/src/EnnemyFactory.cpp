#include       "EnnemyFactory.hh"
#include       "AmmoFactory.hh"
#include       "GameEngine.hh"

EnnemyFactory::EnnemyFactory(std::string const& configurationFileName)
	: _configurationFile(configurationFileName) {

}

EnnemyFactory::~EnnemyFactory() {}

bool                          EnnemyFactory::loadEnnemyConfigFromFile() {

	GameEngine&                 e = requestGameEngine;

	_ennemyConfigs["boss1"] = {
		std::string("r-typesheet34.gif"),
		std::string("boss1"),
		std::string("spaceBomb"),
		sf::Color::Blue,
		std::vector<sf::Vector2f> {
			Vf(0.0f, static_cast<float>(e.getAnimation("boss1").getFrameDimensions().y / 2 + 10.0f)),
			Vf(static_cast< float >(e.getAnimation("boss1").getFrameDimensions().x / 4), 5.0f),
			Vf(static_cast< float >(e.getAnimation("boss1").getFrameDimensions().x / 4 * 3), 15.0f)
	}
	};

	_ennemyConfigs["alienShipBoss"] = {
		std::string("AlienShip.png"),
		std::string("void"),
		std::string("simpleBullet"),
		sf::Color::Black,
		std::vector<sf::Vector2f> {
		Vf(e.getAnimation("void").getFrameDimensions().x / 7 + 5.0f, e.getAnimation("void").getFrameDimensions().y / 4 - 20.0f),
			Vf(e.getAnimation("void").getFrameDimensions().x / 4 + 90.0f, e.getAnimation("void").getFrameDimensions().y / 4 - 30.0f),
			Vf(e.getAnimation("void").getFrameDimensions().x / 4 + 90.0f, e.getAnimation("void").getFrameDimensions().y / 4 - 30.0f),
			Vf(e.getAnimation("void").getFrameDimensions().x / 4 + 150.0f, e.getAnimation("void").getFrameDimensions().y / 4 - 30.0f),
			Vf(e.getAnimation("void").getFrameDimensions().x / 4 + 220.0f, e.getAnimation("void").getFrameDimensions().y / 4 - 30.0f)
	}
	};

	_ennemyConfigs["bountyHunter"] = {
		std::string("r-typesheet7.gif"),
		std::string("bountyHunter"),
		std::string("simpleBullet"),
		sf::Color(0, 0, 173, 255),
		std::vector<sf::Vector2f> {
	}
	};

	_ennemyConfigs["alienJet"] = {
		std::string("r-typesheet24.gif"),
		std::string("alienJet"),
		std::string("simpleBullet"),
		sf::Color::Black,
		std::vector<sf::Vector2f> {
	}
	};

	_ennemyConfigs["ufo"] = {
		std::string("UFO.png"),
		std::string("ufo"),
		std::string("simpleBullet"),
		sf::Color(255, 0, 255),
		std::vector<sf::Vector2f> {
	}
	};

	_ennemyConfigs["spaceFighter"] = {
		std::string("hunter.png"),
		std::string("spaceFighter"),
		std::string("simpleBullet"),
		sf::Color(255, 0, 255),
		std::vector<sf::Vector2f> {
	}
	};

	return true;
}

void                          EnnemyFactory::setConfigurationFile(std::string const& filename) {

	_configurationFile = filename;
}

std::string                   EnnemyFactory::getConfigurationFile() const {

	return _configurationFile;
}

Ennemy*                       EnnemyFactory::createEnnemy(std::string const& ennemyName, /* _unused */ sf::Vector2f const& ennemyPosition, bool const& relativePos)
{
	Ennemy*                     clone = nullptr;
	struct s_ennemyParams       config;
	AmmoFactory                 af;

	af.loadAmmoConfigFromFile();
	if (_ennemyConfigs.find(ennemyName) == _ennemyConfigs.end())
		return nullptr;
	config = _ennemyConfigs[ennemyName];
	if ((clone = new Ennemy(*requestAssetManager.getTexture(config.textureFilename),
		requestGameEngine.getAnimation(config.animationName),
		*af.createAmmo(config.ammunitionName, Ammunition::EnnemyShot), /*to be changed with factorymanager */
		config.colorMask)) == nullptr)
		return nullptr;
	for (auto it = config.shotOriginVertices.begin(); it != config.shotOriginVertices.end(); it++)
		clone->addShotVertex(*it);
	if (relativePos == false)
		clone->setPosition(ennemyPosition);
	else
		clone->setPosition(Vf(ennemyPosition.x - requestGameEngine.getAnimation(config.animationName).getFrameDimensions().x,
			ennemyPosition.y - requestGameEngine.getAnimation(config.animationName).getFrameDimensions().y));
	return clone;
}
