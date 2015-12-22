#include "Bonus.hh"

Bonus::Bonus(sf::Texture const & texture, Animation const & anim, bonusFct onTriggering, int const& value, sf::Color const & colorMask)
: AnimatedSprite(texture, anim, colorMask), _fct(onTriggering), _value(value) {
	std::cout << "on creation value = " << _value << std::endl;
}

Bonus::Bonus(Bonus const& model)
	: AnimatedSprite(model), _fct(model.getFonction()), _value(model.getValue())
{
}

Bonus::~Bonus()
{
}

void									Bonus::trigger(Player& p, int const& value, bool const& useDefault) {

	std::cout << "Values : " << _value << " : " << value << std::endl;
	(this->*_fct)(p, useDefault == true ? _value : value);
}

Bonus::bonusFct				Bonus::getFonction() const
{
	return _fct;
}

int									Bonus::getValue() const {

	return _value;
}

void Bonus::giveSpeed(Player & p, int const& speed) const
{
	p.setSpeed(p.getSpeed() + speed);
}

void Bonus::giveEnergy(Player & p, int const& amount) const
{
	int		value = amount + p.getEnergy().x;
	if (value > p.getEnergy().y)
		value = p.getEnergy().y;
	else if (value < 0)
		value = 0;
	p.setEnergy(sf::Vector2i(value, p.getEnergy().y));
}


