#ifndef								___BONUS_HH___
# define							___BONUS_HH___

#include							"Client_graphicUtils.hh"
#include							"Player.hpp"
#include							"FX.hh"

class Bonus : public AnimatedSprite
{
public:
	typedef		void		(Bonus::*bonusFct)(Player&, int const& value) const;

public:

	Bonus(sf::Texture const& texture, Animation const& anim, bonusFct onTriggering, int const& value = 1, sf::Color const& colorMask = sf::Color::White);
	Bonus(Bonus const& model);
	~Bonus();

public:

	void								trigger(Player& p, int const& value = 0, bool const& useDefault = true);
	bonusFct						getFonction() const;
	int								getValue() const;

public:

	void								giveSpeed(Player& p, int const& speed) const;
	void								giveEnergy(Player&p, int const& amount) const;

private:

	bonusFct						_fct;
	int								_value;
};

#endif								/* !___BONUS_HH___ */