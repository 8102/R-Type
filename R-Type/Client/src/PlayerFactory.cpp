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
	if (_bluePrint[playerID].second == false)
		loadPlayer(playerID);
	return *_bluePrint[playerID].second.get();
}

void PlayerFactory::loadConfigs()
{
	_bluePrint[1].first = { "flyingSaucer.png", "flyingSaucer", "simpleBullet", { "rocket" }, sf::Color::White, 2, sf::Vector2i(100, 100), "player1" };
	_bluePrint[2].first = { "UFO.png", "ufo", "plasmaBullet", { "rocket" }, sf::Color(255, 0, 255), 2, sf::Vector2i(250, 250), "player2" };
	_bluePrint[3].first = { "hunter.png", "spaceFighter", "simpleBullet", { "rocket" }, sf::Color::White, 2, sf::Vector2i(150, 150), "player3" };
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
}
