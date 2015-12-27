#include "PlayerFactory.hh"
#include "AssetManager.hh"
#include "GameEngine.hh"

PlayerFactory::PlayerFactory()
{
}


PlayerFactory::~PlayerFactory()
{
}

Player&		PlayerFactory::getPlayer(int const & playerID)
{
	std::cout << "FACTORY" << std::endl;

	if (_bluePrint[playerID].second == false)
		loadPlayer(playerID);

	return *_bluePrint[playerID].second.get();
}

void PlayerFactory::loadConfigs()
{
	_bluePrint[1].first = { "flyingSaucer.png", "flyingSaucer", "simpleBullet", { "rocket" }, sf::Color::White, 4, sf::Vector2i(200, 200), "player1", { sf::Vector2f(37.0f, 16.0f) } };
	_bluePrint[2].first = { "UFO.png", "ufo", "plasmaBullet", { "rocket" }, sf::Color(255, 0, 255), 1, sf::Vector2i(300, 300), "player2", { sf::Vector2f(30.0f, 12.0f) } };
	_bluePrint[3].first = { "player3.png", "attackShip", "simpleBullet",{ "rocket" }, sf::Color::White, 2, sf::Vector2i(200, 200), "player3", { sf::Vector2f(35.0f, 25.0f) } };
	_bluePrint[4].first = { "player4.png", "spacePig", "plasmaBullet",{ "rocket" }, sf::Color::White, 3, sf::Vector2i(150, 150), "player4", { sf::Vector2f(25.0f, 8.0f) } };
}

void PlayerFactory::loadPlayer(int const & playerID)
{
	struct playerParams	p;
	AmmoFactory			af;
	af.loadAmmoConfigFromFile();

	if (_bluePrint.find(playerID) == _bluePrint.end()) {}
		/* throw exception */
	p = _bluePrint[playerID].first;
	_bluePrint[playerID].second = make_unique<Player>(
		*requestAssetManager.getTexture(p.textureName),
		requestGameEngine.getAnimation(p.animationName),
		*af.createAmmo(p.weaponName),
		p._colorMask);
	_bluePrint[playerID].second->setSpeed(p._speed);
	_bluePrint[playerID].second->setLife(p.health);
	_bluePrint[playerID].second->setName(p.name);

	for (auto it = p._additionalWeapons.begin(); it != p._additionalWeapons.end(); it++)
		_bluePrint[playerID].second->addWeapon(af.createAmmo(*it));
	for (auto it = p.shotVertices.begin(); it != p.shotVertices.end(); it++) {
		_bluePrint[playerID].second->addShotVertex(*it);
	}
}
