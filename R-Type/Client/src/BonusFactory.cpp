#include "BonusFactory.hh"
#include "GameEngine.hh"

BonusFactory::BonusFactory()
{
}


BonusFactory::~BonusFactory()
{
}

void BonusFactory::loadConfig()
{
	_BonusFunctions["speed"] = &Bonus::giveSpeed;
	_config["speedBonus"] = {
		"atom.png",
		"atom",
		"speed",
		sf::Color::White
	};

	_BonusFunctions["energy"] = &Bonus::giveEnergy;
	_config["energy"] = {
		"shieldBonus.png",
		"shieldBonus",
		"energy",
		sf::Color::Black
	};

	_BonusFunctions["minigun"] = &Bonus::giveSpeed;
	_config["minigunBonus"] = {
		"bonusMinigun.png",
		"icon",
		"speed",
		sf::Color::White
	};



}

Bonus* BonusFactory::createBonus(std::string const & name, sf::Vector2f const & position, int const& value)
{
	bonusParams		p;

	p = _config[name];
	if (_models.find(name) == _models.end() || (_models[name] == false)) {
		_models[name] = make_unique< Bonus >(
			*requestAssetManager.getTexture(p.texture),
			requestGameEngine.getAnimation(p.anim),
			_BonusFunctions[p.fonction],
			value,
			p.colorMask);
		_models[name]->setPosition(position);
		return _models[name].get();
	}
	return nullptr;
}
