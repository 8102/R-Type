#include           "Ammunition.hh"
#include           "ACharacter.hh"
#include			"GameEngine.hh"
//#include           "UnitTest.hh"
Ammunition::Ammunition(std::string const& filename, Animation const& pattern, unsigned int speed, sf::Color const& colorMask)
	: AnimatedSprite(filename, pattern, colorMask), _targetPosition(0.0f, 0.0f), _speed(speed), _target(nullptr), _type(NeutralShot) {

}

Ammunition::Ammunition(sf::Texture const& texture, Animation const& pattern, unsigned int speed, sf::Color const& colorMask)
	: AnimatedSprite(texture, pattern, colorMask), _targetPosition(0.0f, 0.0f), _speed(speed), _target(nullptr), _type(NeutralShot) {

}

Ammunition::Ammunition(Ammunition const& model)
	: AnimatedSprite(model), _targetPosition(model.getTargetPosition()), _speed(model.getSpeed()), _movement(model.getMovement()), _target(model.getTarget()), _type(model.getType()) {

}

Ammunition::~Ammunition() {

	if (requestGameEngine.isPaused() == false && requestGameEngine.isRunning() == true) {
		AnimatedSprite*  fx = new AnimatedSprite(*requestAssetManager.getTexture("r-typesheet44.gif"),
			requestGameEngine.getAnimation("explosion"),
			sf::Color::Black);
		requestGameEngine.addFX(fx, *this);
	}
}

void                      Ammunition::update() {

	AnimatedSprite::update();
	if (_target != nullptr)
		setTargetPosition(_target->getPosition());
	setPosition(getPosition().x + _movement.x, getPosition().y + _movement.y);
	if (_animationState != Animation::current)
		changeFrame();
}
void                      Ammunition::setTargetPosition(sf::Vector2f const& targetPosition) {

	_targetPosition = targetPosition;
	_movement = sf::Vector2f((_targetPosition.x - getPosition().x) / _speed, (_targetPosition.y - getPosition().y) / _speed);
}

void                      Ammunition::setSpeed(unsigned int const&  speed) {

	_speed = speed;
}

void                      Ammunition::setMovement(sf::Vector2f const& movement) {

	_movement = movement;
}

void                      Ammunition::setTarget(ACharacter& target) {

	_target = &target;
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

sf::Vector2f              Ammunition::getMovement() const {

	return _movement;
}

AGameElement*             Ammunition::getTarget() const {

	return _target;
}

Ammunition::eTargets      Ammunition::getType() const {

	return _type;
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
