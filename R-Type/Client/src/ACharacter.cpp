#include                "ACharacter.hh"
#include                "GameEngine.hh"
//#include                "UnitTest.hh"

ACharacter::ACharacter(std::string const& filename, Animation const& animation, Ammunition const& weapon, sf::Color const& colorMask)
	: AnimatedSprite(filename, animation, colorMask), _speed(1), _health(sf::Vector2i(100, 100)), _name(""), _weapon(weapon), _index(0), _gName("", *requestAssetManager.getFont("nullShock.ttf"), 7), _deathFX("", "") {

//	_shotVertexes.push_back(sf::Vector2f(getGlobalBounds().width, getGlobalBounds().height / 2));
	_weapons.push_back(Ammunition(_weapon));
	_gName.setColor(sf::Color(255, 200, 0));
}

ACharacter::ACharacter(sf::Texture const& texture, Animation const& animation, Ammunition const& weapon, sf::Color const& colorMask)
	: AnimatedSprite(texture, animation, colorMask), _speed(1), _health(sf::Vector2i(100, 100)), _name(""), _weapon(weapon), _index(0), _gName("", *requestAssetManager.getFont("nullShock.ttf"), 7), _deathFX("", "") {

//	_shotVertexes.push_back(sf::Vector2f(getGlobalBounds().width, getGlobalBounds().height / 2));
	_weapons.push_back(Ammunition(_weapon));
	_gName.setColor(sf::Color(255, 200, 0));
}

ACharacter::ACharacter(AnimatedSprite const& baseModel, Ammunition const& weapon)
	: AnimatedSprite(baseModel), _speed(1), _health(sf::Vector2i(100, 100)), _name(""), _weapon(weapon), _index(0), _gName("", *requestAssetManager.getFont("nullShock.ttf"), 7), _deathFX("", "") {

//	_shotVertexes.push_back(sf::Vector2f(getGlobalBounds().width, getGlobalBounds().height / 2));
	_weapons.push_back(Ammunition(_weapon));
	_gName.setColor(sf::Color(255, 200, 0));
}

ACharacter::ACharacter(ACharacter const& model)
	: AnimatedSprite(model), _speed(model.getSpeed()), _health(model.getLife()), _name(model.getName()), _weapon(model.getWeapon()), _index(0), _gName(model.getGraphicName()), _deathFX(model.getDeathFX()) {

	std::vector<sf::Vector2f> v = model.getShotVertices();
	for (auto it = v.begin(); it != v.end(); it++)
		_shotVertexes.push_back(*it);
	_weapons = model.getAllWeapons();
}

ACharacter::~ACharacter() {
}

void                      ACharacter::move(int xAxis, int yAxis) {

	setPosition(getPosition().x + (xAxis * _speed), getPosition().y + (yAxis * _speed));
}

void                      ACharacter::shoot(unsigned int shotOriginVertexIndex) {

	GameEngine&             engine = GameEngine::instanciate();
	Ammunition*             shot = new Ammunition(_weapon);

	shot->setPosition(getPosition() + _shotVertexes[shotOriginVertexIndex % _shotVertexes.size()]);
	shot->setTargetPosition(Vf(WIN_W * 2, getPosition().y + getGlobalBounds().height / 2));
	engine.addAmmo(shot);
	SoundSystem::instanciate().pushEffect("speedBonus.wav");
//	SoundSystem::instanciate().pushEffect("pulseShot.wav");
}


void                      ACharacter::shoot(ACharacter& target, /*_unused*/ unsigned int shotOriginVertexIndex) {

	GameEngine&             engine = GameEngine::instanciate();
	Ammunition*             shot = new Ammunition(_weapon);

	shot->setPosition(getPosition() + _shotVertexes[shotOriginVertexIndex % _shotVertexes.size()]);
	shot->setTarget(target);
	engine.addAmmo(shot);
//	SoundSystem::instanciate().pushEffect("pulseShot.wav");
}

void                      ACharacter::shoot(sf::Vector2f const& targetPosition, unsigned int shotOriginVertexIndex) {

	GameEngine&             engine = GameEngine::instanciate();
	Ammunition*             shot = new Ammunition(_weapon);

	shot->setPosition(getPosition() + _shotVertexes[shotOriginVertexIndex % _shotVertexes.size()]);
	shot->setTargetPosition(targetPosition);
	engine.addAmmo(shot);
//	SoundSystem::instanciate().pushEffect("pulseShot.wav");
}

void                      ACharacter::shoot(sf::Vector2f const& targetPosition, bool allWeapons)
{
	GameEngine&             engine = GameEngine::instanciate();

	SoundSystem::instanciate().pushEffect("pulseShot.wav");
	if (allWeapons == true) {
		for (auto it = _shotVertexes.begin(); it != _shotVertexes.end(); it++) {
			Ammunition*             shot = new Ammunition(_weapon);
			shot->setPosition(getPosition() + *it);
			shot->setTargetPosition(targetPosition);
			engine.addAmmo(shot);
		}
	}
	else {
		shoot(targetPosition, _index);
		_index = (_index + 1) % _shotVertexes.size();
	}
}

void ACharacter::die()
{
	if (_deathFX.getAnimationName().size() > 0)
	{
		sf::FloatRect		r = getGlobalBounds();
		sf::Vector2i	d = requestGameEngine.getAnimation(_deathFX.getAnimationName()).getFrameDimensions();
		sf::Vector2f	p(r.left + r.width / 2 - d.x / 2, r.top + r.height / 2 - d.y / 2);
		_deathFX.trigger(p);
	}

}

unsigned int              ACharacter::getSpeed() const {

	return _speed;
}

sf::Vector2i ACharacter::getLife() const
{
	return _health;
}

std::string ACharacter::getName() const
{
	return _name;
}

Ammunition               ACharacter::getWeapon() const {

	return _weapon;
}

sf::Text ACharacter::getGraphicName() const
{
	return _gName;
}

FX ACharacter::getDeathFX() const
{
	return _deathFX;
}

void                     ACharacter::setSpeed(unsigned int const& speed) {

	_speed = speed;
}

void ACharacter::setLife(sf::Vector2i const & life)
{
	_health = life;
}

void ACharacter::setName(std::string const & name)
{
	_name = name;
	_gName.setString(name);
}

void ACharacter::setDeathFX(std::string const & aName, std::string const & rName, std::string const & eName, sf::Color const & colorMask)
{
	_deathFX.setAnimationName(aName);
	_deathFX.setRessourceName(rName);
	_deathFX.setEffectName(eName);
	_deathFX.setColorMask(colorMask);
}

void                     ACharacter::addShotVertex(sf::Vector2f const& shotOriginVertex) {

	_shotVertexes.push_back(shotOriginVertex);
}

template< class T >
void                    ACharacter::shoot(T& target, bool useAllWeapon, unsigned int const& shotOriginVertex) {

	GameEngine&           e = requestGameEngine;

	if (useAllWeapon == true)
		for (auto it = _shotVertexes.begin(); it != _shotVertexes.end(); it++)
			shoot(target, false, std::distance(_shotVertexes.begin(), it));
	else {
		Ammunition  *amo = new Ammunition(_weapon);

		amo->setPosition(target);
		amo->setTargetPosition(target);
		e.addAmmo(amo);
//		SoundSystem::instanciate().pushEffect("speedBonus.wav");
		//		SoundSystem::instanciate().pushEffect("pulseShot.wav");
	}
}

void                       ACharacter::addWeapon(Ammunition* ammo) {

	_weapons.push_back(Ammunition(*ammo));
}

std::vector<Ammunition> ACharacter::getAllWeapons() const
{
	return _weapons;
}

std::vector<sf::Vector2f>            ACharacter::getShotVertices() const {

	return _shotVertexes;
}

void ACharacter::drawName(sf::RenderWindow& win)
{
	_gName.setPosition(sf::Vector2f(getGlobalBounds().left + getGlobalBounds().width / 2 - _gName.getGlobalBounds().width / 2,
													  getGlobalBounds().top + getGlobalBounds().height));
	win.draw(_gName);
}


void ACharacter::drawLife(sf::RenderWindow& win, bool const& up) {

	sf::Sprite					s;
	sf::RectangleShape	r;
	float							lifeRatio;

	s.setTexture(*requestAssetManager.getTexture("lifebar.png"));
	s.setScale(sf::Vector2f(0.5f, 0.5f));
	s.setPosition(sf::Vector2f(getGlobalBounds().left + getGlobalBounds().width / 2 - s.getGlobalBounds().width / 2,
		getGlobalBounds().top + (up == true ? -s.getGlobalBounds().height : getGlobalBounds().height)));
	lifeRatio = static_cast<float>(_health.x) / static_cast<float>(_health.y);
	r.setSize(sf::Vector2f((s.getGlobalBounds().width / 20 * 19) * lifeRatio, s.getGlobalBounds().height / 10 * 9));
	r.setFillColor(lifeRatio < 0.3 ? sf::Color(160, 0, 0) : (lifeRatio < 0.6 ? sf::Color(200, 150, 0) : sf::Color(0, 255, 0)));
	r.setPosition(s.getPosition());
	win.draw(r);
	win.draw(s);
}

void ACharacter::drawInformation(sf::RenderWindow& win)
{
	drawName(win);
	drawLife(win);
}

// template<>
// void                    ACharacter::shoot<ACharacter&>(T& target, bool useAllWeapon, unsigned int const& shotOriginVertex) {
//
//   GameEngine&           e = requestGameEngine;
//
//   if (useAllWeapon == true)
//     for (auto it = _shotVertexes.begin(); it != _shotVertexes.end(); it++)
//         shoot<Vf>(target.getPosition(), false, std::distance(_shotVertexes.begin(), it));
//   else {
//     Ammunition  *amo = new Ammunition(_weapon);
//
//     amo->setPosition(target);
//     amo->setTargetPosition(target.getPosition());
//     e.addAmmo(amo);
//     SoundSystem::instanciate().playEffect("pulseShot.wav");
//   }
// }
