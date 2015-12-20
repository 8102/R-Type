#include                     "Player.hpp"
#include                     "GameEngine.hh"
//#include                     "UnitTest.hh"
Player::Player(std::string const& filename, Animation const& animation, Ammunition const& ammo, sf::Color const& colorMask)
	: ACharacter(filename, animation, ammo, colorMask), _reload(50), _reloadingTime(_reload), _canShot(true), _weaponIndex(0) {

	setType(AGameElement::Friendly);
}

Player::Player(sf::Texture const& texture, Animation const& animation, Ammunition const& ammo, sf::Color const& colorMask)
	: ACharacter(texture, animation, ammo, colorMask), _reload(50), _reloadingTime(_reload), _canShot(true), _weaponIndex(0) {

	setType(AGameElement::Friendly);
}

Player::Player(AnimatedSprite const& baseModel, Ammunition const& ammo)
	: ACharacter(baseModel, ammo), _reload(50), _reloadingTime(_reload), _canShot(true), _weaponIndex(0) {

	setType(AGameElement::Friendly);
}


Player::Player(ACharacter const& baseModel)
	: ACharacter(baseModel), _reload(50), _reloadingTime(_reload), _canShot(true), _weaponIndex(0) {

	setType(AGameElement::Friendly);
}

void                         Player::update() {

	ACharacter::update();
	if (_reloadingTime <= 0)
	{
		std::string s = _weapons[_weaponIndex].getCurrentAnimation().getAnimationName();
		_reloadingTime = (s == "rocket" ? 120 : (s == "simpleBullet" ? 20 : 40));
		_canShot = true;
	}
	else _reloadingTime -= 1;
}

void                         Player::isReloading() {

	_canShot = false;
}

Ammunition Player::getWeapon() const
{
	return _weapons[_weaponIndex];
}

bool                         Player::canShot() const {

	return _canShot;
}

void							Player::indicateCurrentPlayer(sf::RenderWindow& win)
{
	sf::VertexArray		a(sf::Triangles, 4);
	sf::FloatRect			r = getGlobalBounds();
	a[0] = sf::Vector2f(r.left + r.width / 2 - 5, r.top - 5);
	a[1] = sf::Vector2f(r.left + r.width / 2 + 5, r.top - 5);
	a[2] = sf::Vector2f(r.left + r.width / 2, r.top);
	a[3] = sf::Vector2f(r.left + r.width / 2 - 5, r.top - 5);
	a[0].color = sf::Color(255, 170, 0);
	a[1].color = sf::Color(255, 170, 0);
	a[2].color = sf::Color(255, 170, 0);
	win.draw(a);
}

void                         Player::shoot(unsigned int shotOriginVertexIndex) {

	if (canShot() == true)
	{
		_weapons[_weaponIndex].setType(Ammunition::friendlyShot);
		GameEngine&             engine = GameEngine::instanciate();
		Ammunition*             shot = new Ammunition(_weapons[_weaponIndex]);
		shot->setPosition(getPosition() + _shotVertexes[shotOriginVertexIndex % _shotVertexes.size()]);
		shot->setTargetPosition(Vf(WIN_W * 2, getPosition().y + getGlobalBounds().height / 2));
		engine.addAmmo(shot);
		SoundSystem::instanciate().pushEffect("speedBonus.wav");
		//		SoundSystem::instanciate().playEffect("speedBonus.wav");
		isReloading();
		if (_weapons[_weaponIndex].getCurrentAnimation().getAnimationName() == "plasmaBullet")
			engine.addFX("loadingShot", "r-typesheet1.gif", sf::Vector2f(getPosition().x + _shotVertexes[shotOriginVertexIndex].x, getPosition().y + _shotVertexes[shotOriginVertexIndex].y - engine.getAnimation("loadingShot").getFrameDimensions().y / 2), sf::Color::Black);
		else 
		engine.addFX("fireshot", "fire.png", sf::Vector2f(getPosition().x + _shotVertexes[shotOriginVertexIndex].x, getPosition().y + _shotVertexes[shotOriginVertexIndex].y - engine.getAnimation("fireshot").getFrameDimensions().y / 2), sf::Color::White);
	}
}

// void                         Player::shoot(unsigned int shotOriginVertex, sf::Vector2f const& targetPosition) {
//
//   if (canShot() == true)
//     {
//       ACharacter::shoot(shotOriginVertex, targetPosition)
//       isReloading();
//     }
// }

//void						    Player::ActivateShield()
//{
//	_shield = 
//}

void                         Player::move(int xAxis, int yAxis) {

	sf::Vector2f               movement(static_cast<float>(static_cast<int>(_speed * xAxis)), static_cast<float>(static_cast<int>(_speed * yAxis)));
	sf::Vector2f               nextPosition = getPosition() + movement;

	if (nextPosition.x < (WIN_W - getGlobalBounds().width - 50) &&
		nextPosition.x > 50 &&
		nextPosition.y > 10 &&
		nextPosition.y < (WIN_H - getGlobalBounds().height - 10))
		setPosition(nextPosition);
}

void                         Player::switchWeapon() {

	std::cout << "[Player::switchWeapon] : ";
	_weaponIndex = (_weaponIndex + 1) % _weapons.size();
	_weapon = _weapons[_weaponIndex];
	std::cout << " Extern switch : " << getWeapon().getCurrentAnimation().getAnimationName() << std::endl;
	std::cout << "{ " << _weapon.getCurrentAnimation().getAnimationName() << " } :  [" << _weapon.getDamage() << "]" << std::endl;
	std::cout << "{ " << _weapons[_weaponIndex].getCurrentAnimation().getAnimationName() << " } :  [" << _weapons[_weaponIndex].getDamage() << "]" << std::endl;
}

Player::~Player() {}
