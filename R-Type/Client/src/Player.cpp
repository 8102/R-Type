#include                     "Player.hpp"
#include                     "GameEngine.hh"
//#include                     "UnitTest.hh"
Player::Player(std::string const& filename, Animation const& animation, Ammunition const& ammo, sf::Color const& colorMask)
	: ACharacter(filename, animation, ammo, colorMask), _reload(50), _reloadingTime(_reload), _canShot(true), _weaponIndex(0), _shield(Player::initPlayerShield()), _isShielded(false), _energy(200, 200), _played(false) {

	setType(AGameElement::Friendly);
}

Player::Player(sf::Texture const& texture, Animation const& animation, Ammunition const& ammo, sf::Color const& colorMask)
	: ACharacter(texture, animation, ammo, colorMask), _reload(50), _reloadingTime(_reload), _canShot(true), _weaponIndex(0), _shield(Player::initPlayerShield()), _isShielded(false), _energy(200, 200), _played(false) {

	setType(AGameElement::Friendly);
}

Player::Player(AnimatedSprite const& baseModel, Ammunition const& ammo)
	: ACharacter(baseModel, ammo), _reload(50), _reloadingTime(_reload), _canShot(true), _weaponIndex(0), _shield(Player::initPlayerShield()), _isShielded(false), _energy(200, 200), _played(false) {

	setType(AGameElement::Friendly);
}


Player::Player(ACharacter const& baseModel)
	: ACharacter(baseModel), _reload(50), _reloadingTime(_reload), _canShot(true), _weaponIndex(0), _shield(Player::initPlayerShield()), _isShielded(false), _energy(200, 200), _played(false) {

	setType(AGameElement::Friendly);
}

void                         Player::update() {

	ACharacter::update();
	if (_isShielded == true)
		_shield.update();
	if (_reloadingTime <= 0)
	{
		std::string s = _weapons[_weaponIndex].getCurrentAnimation().getAnimationName();
		_reloadingTime = (s == "rocket" ? 80 : (s == "simpleBullet" ? 1 : 10));
		_canShot = true;
	}
	else _reloadingTime -= 1;
}

void Player::getDrawn(sf::RenderWindow & win)
{
	win.draw(*this);
	if (isShielded() == true)
		win.draw(_shield);
}

void                         Player::isReloading() {

	_canShot = false;
}

Ammunition			Player::getWeapon() const
{
	return _weapons[_weaponIndex];
}

AnimatedSprite Player::getShield() const
{
	return _shield;
}

bool						Player::isShielded() const
{

	return _isShielded;
}

sf::Vector2i Player::getEnergy() const
{

	return	_energy;
}

void Player::setEnergy(sf::Vector2i const & v)
{
	_energy = v;
}

AnimatedSprite & Player::initPlayerShield()
{
	static AnimatedSprite	shield(*requestAssetManager.getTexture("bubbleShield.png"), requestGameEngine.getAnimation("bubbleShield"), sf::Color::Black);

	return shield;
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

void                         Player::move(int xAxis, int yAxis) {

	sf::Vector2f               movement(static_cast<float>(static_cast<int>(_speed * xAxis)), static_cast<float>(static_cast<int>(_speed * yAxis)));
	sf::Vector2f               nextPosition = getPosition() + movement;

	if (nextPosition.x < (WIN_W - getGlobalBounds().width - 50) &&
		nextPosition.x > 50 &&
		nextPosition.y > 10 &&
		nextPosition.y < (WIN_H - getGlobalBounds().height - 10))
		setPosition(nextPosition);
		_shield.setPosition(sf::Vector2f(getGlobalBounds().left + getGlobalBounds().width / 2.0f - _shield.getGlobalBounds().width / 2.0f,
			getGlobalBounds().top + getGlobalBounds().height / 2.0f - _shield.getGlobalBounds().height / 2.0f));
}

void                         Player::switchWeapon() {

	_weaponIndex = (_weaponIndex + 1) % _weapons.size();
	_weapon = _weapons[_weaponIndex];
	//std::cout << " Extern switch : " << getWeapon().getCurrentAnimation().getAnimationName() << std::endl;
	//std::cout << "{ " << _weapon.getCurrentAnimation().getAnimationName() << " } :  [" << _weapon.getDamage() << "]" << std::endl;
	//std::cout << "{ " << _weapons[_weaponIndex].getCurrentAnimation().getAnimationName() << " } :  [" << _weapons[_weaponIndex].getDamage() << "]" << std::endl;
}

void Player::activateShield(bool const & shieldState)
{
	if (shieldState == true && _energy.x <= 0) _isShielded = false;
	else	_isShielded = shieldState;
}

void Player::receiveDamage(Ammunition const & shot)
{
	if (_isShielded == true) {
		_energy.x -= shot.getDamage();
		if (_energy.x <= 0) {
			_health.x -= _energy.x;
			_energy.x = 0;
			_isShielded = false;
		}
	} else {
		shot.dealDamage(*this);
	}
}

bool Player::collide(AGameElement const & collider, bool const &shieldCollision) const
{
	if (isShielded() == true && shieldCollision == true)
		return collider.collide(_shield);
	return collider.collide(*this);
}

bool Player::isAlive() const
{
	return _health.x <= 0.0f;
}

bool Player::isPlayed() const
{
	return _played;
}

void Player::isPlayed(bool const & played)
{
	_played = played;
}


Player::~Player() {}

