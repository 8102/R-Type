#include              "Ennemy.hh"
#include              "GameEngine.hh"

Ennemy::Ennemy(std::string const& filename, Animation const& animation, Ammunition const& ammo, sf::Color const& colorMask)
	: ACharacter(filename, animation, ammo, colorMask), _reloading(0) {

}

Ennemy::Ennemy(sf::Texture const& texture, Animation const& animation, Ammunition const& ammo, sf::Color const& colorMask)
	: ACharacter(texture, animation, ammo, colorMask), _reloading(0) {

}

Ennemy::Ennemy(AnimatedSprite const& baseModel, Ammunition const& ammo)
	: ACharacter(baseModel, ammo), _reloading(0) {

	_weapon.setType(Ammunition::EnnemyShot);
	//    _type = AGameElement::Ennemy;
	setType(AGameElement::Ennemy);
}

Ennemy::Ennemy(ACharacter const& baseModel)
	: ACharacter(baseModel), _reloading(0) {

}

Ennemy::Ennemy(Ennemy const& baseModel)
	: ACharacter(baseModel), _reloading(0) {

}


Ennemy::~Ennemy() {}


void              Ennemy::update() {


	ACharacter::update();
	if (_reloading <= 0) {
		shoot(requestGameEngine.getPlayer().getPosition(), false);
		_reloading = 350;
	}
	else _reloading--;
}

void              Ennemy::move(float x, float y) {

	sf::Sprite::setPosition(getPosition().x + (x * _speed), getPosition().y + (y * _speed));
}
