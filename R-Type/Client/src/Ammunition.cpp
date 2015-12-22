#include           "Ammunition.hh"
#include           "ACharacter.hh"
#include			"GameEngine.hh"
#include			"FX.hh"

//#include           "UnitTest.hh"
Ammunition::Ammunition(std::string const& filename, Animation const& pattern, unsigned int speed, sf::Color const& colorMask)
	: AnimatedSprite(filename, pattern, colorMask), _targetPosition(0.0f, 0.0f), _speed(speed), _damage(10), _target(nullptr), _type(NeutralShot), _deathFX("", "") {

}

Ammunition::Ammunition(sf::Texture const& texture, Animation const& pattern, unsigned int speed, sf::Color const& colorMask)
	: AnimatedSprite(texture, pattern, colorMask), _targetPosition(0.0f, 0.0f), _speed(speed), _damage(10), _target(nullptr), _type(NeutralShot), _deathFX("", "") {

}

Ammunition::Ammunition(Ammunition const& model)
	: AnimatedSprite(model), _targetPosition(model.getTargetPosition()), _speed(model.getSpeed()), _damage(model.getDamage()), _movement(model.getMovement()), _target(model.getTarget()), _type(model.getType()), _deathFX(model.getDeathFX()) {

}

Ammunition::~Ammunition() {
}

void                      Ammunition::update() {

	AnimatedSprite::update();
	if (_target != nullptr)
		setTargetPosition(_target->getPosition());
	setPosition(getPosition().x + _movement.x, getPosition().y + _movement.y);
	if (_animationState != Animation::current)
		changeFrame();
}
bool Ammunition::dealDamage(ACharacter& target) const
{
	target.setLife(sf::Vector2i(target.getLife().x - _damage, target.getLife().y));
	if (target.getLife().x < 0)
		target.setLife(sf::Vector2i(0, target.getLife().y));
	return target.getLife().x <= 0 ? true : false;
}

void Ammunition::trigger()
{
	if (_deathFX.getAnimationName().size() > 0)
	{
		sf::FloatRect		r = getGlobalBounds();
		sf::Vector2i	d = requestGameEngine.getAnimation(_deathFX.getAnimationName()).getFrameDimensions();
		sf::Vector2f	p(r.left + r.width / 2 - d.x / 2, r.top + r.height / 2 - d.y / 2);
		_deathFX.trigger(p);
	}
}
void                      Ammunition::setTargetPosition(sf::Vector2f const& targetPosition) {
	
	float					vx, vy, deltax, deltay, angle;
	
	_targetPosition = targetPosition;
	deltax = targetPosition.x - getPosition().x;
	deltay = targetPosition.y - getPosition().y;
	angle = std::atan2f(deltay, deltax);
	vx = std::cos(angle) * _speed;
	vy = std::sin(angle) * _speed;
	_movement = sf::Vector2f(vx, vy);
}

void                      Ammunition::setSpeed(unsigned int const&  speed) {

	_speed = speed;
}

void Ammunition::setDamage(int const & damage)
{
	_damage = damage;
}

void                      Ammunition::setMovement(sf::Vector2f const& movement) {

	_movement = movement;
}

void                      Ammunition::setTarget(ACharacter& target) {

	_target = &target;
}

void Ammunition::setDeathFX(std::string const & aName, std::string const & rName, std::string const & eName, sf::Color const & colorMask)
{
	_deathFX.setAnimationName(aName);
	_deathFX.setRessourceName(rName);
	_deathFX.setEffectName(eName);
	_deathFX.setColorMask(colorMask);
}

void                      Ammunition::setType(eTargets const& type) {

	_type = type;
}


sf::Vector2f              Ammunition::getTargetPosition() const {

	return _targetPosition;
}

unsigned int              Ammunition::getSpeed() const {


	return _speed;
}

int Ammunition::getDamage() const
{
	return _damage;
}

sf::Vector2f              Ammunition::getMovement() const {

	return _movement;
}

AGameElement*             Ammunition::getTarget() const {

	return _target;
}

Ammunition::eTargets      Ammunition::getType() const {

	return _type;
}

FX Ammunition::getDeathFX() const
{
	return _deathFX;
}

Ammunition&               Ammunition::operator=(Ammunition const& model) {

	if (this == &model)
		return *this;
	AnimatedSprite::operator=(model);
	setType(model.getType());
	setTargetPosition(model.getTargetPosition());
	setSpeed(model.getSpeed());
	setMovement(model.getMovement());
	return *this;
}
