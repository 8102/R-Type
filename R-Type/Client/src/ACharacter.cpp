#include                "ACharacter.hh"
#include                "GameEngine.hh"
//#include                "UnitTest.hh"

ACharacter::ACharacter(std::string const& filename, Animation const& animation, Ammunition const& weapon, sf::Color const& colorMask)
	: AnimatedSprite(filename, animation, colorMask), _speed(1), _weapon(weapon) {

	_shotVertexes.push_back(sf::Vector2f(getGlobalBounds().width, getGlobalBounds().height / 2));
	_weapons.push_back(Ammunition(_weapon));
}

ACharacter::ACharacter(sf::Texture const& texture, Animation const& animation, Ammunition const& weapon, sf::Color const& colorMask)
	: AnimatedSprite(texture, animation, colorMask), _speed(1), _weapon(weapon) {

	_shotVertexes.push_back(sf::Vector2f(getGlobalBounds().width, getGlobalBounds().height / 2));
	_weapons.push_back(Ammunition(_weapon));
}

ACharacter::ACharacter(AnimatedSprite const& baseModel, Ammunition const& weapon)
	: AnimatedSprite(baseModel), _speed(1), _weapon(weapon) {

	_shotVertexes.push_back(sf::Vector2f(getGlobalBounds().width, getGlobalBounds().height / 2));
	_weapons.push_back(Ammunition(_weapon));
}

ACharacter::ACharacter(ACharacter const& model)
	: AnimatedSprite(model), _speed(model.getSpeed()), _weapon(model.getWeapon()) {

	std::vector<sf::Vector2f> v = model.getShotVertices();
	for (auto it = v.begin(); it != v.end(); it++)
		_shotVertexes.push_back(*it);
	_weapons.push_back(Ammunition(_weapon));
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
	SoundSystem::instanciate().pushEffect("pulseShot.wav");
}


void                      ACharacter::shoot(ACharacter& target, /*_unused*/ unsigned int shotOriginVertexIndex) {

	GameEngine&             engine = GameEngine::instanciate();
	Ammunition*             shot = new Ammunition(_weapon);

	shot->setPosition(getPosition() + _shotVertexes[shotOriginVertexIndex % _shotVertexes.size()]);
	shot->setTarget(target);
	engine.addAmmo(shot);
	SoundSystem::instanciate().pushEffect("pulseShot.wav");
}

void                      ACharacter::shoot(sf::Vector2f const& targetPosition, unsigned int shotOriginVertexIndex) {

	GameEngine&             engine = GameEngine::instanciate();
	Ammunition*             shot = new Ammunition(_weapon);

	shot->setPosition(getPosition() + _shotVertexes[shotOriginVertexIndex % _shotVertexes.size()]);
	shot->setTargetPosition(targetPosition);
	engine.addAmmo(shot);
	SoundSystem::instanciate().pushEffect("pulseShot.wav");
}

void                      ACharacter::shoot(sf::Vector2f const& targetPosition, bool allWeapons)
{
	GameEngine&             engine = GameEngine::instanciate();

	if (allWeapons == true) {
		for (auto it = _shotVertexes.begin(); it != _shotVertexes.end(); it++) {
			Ammunition*             shot = new Ammunition(_weapon);
			shot->setPosition(getPosition() + *it);
			shot->setTargetPosition(targetPosition);
			engine.addAmmo(shot);
			SoundSystem::instanciate().pushEffect("pulseShot.wav");
		}
	}
}

unsigned int              ACharacter::getSpeed() const {

	return _speed;
}

Ammunition               ACharacter::getWeapon() const {

	return _weapon;
}

void                     ACharacter::setSpeed(unsigned int const& speed) {

	_speed = speed;
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
		SoundSystem::instanciate().pushEffect("pulseShot.wav");
	}
}

void                       ACharacter::addWeapon(Ammunition* ammo) {

	_weapons.push_back(Ammunition(*ammo));
}

std::vector<sf::Vector2f>            ACharacter::getShotVertices() const {

	return _shotVertexes;
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
