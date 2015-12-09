#ifndef             ___ENNEMY_HH___
# define            ___ENNEMY_HH___

# include           "ACharacter.hh"

class               Ennemy : public ACharacter
{
public:

	Ennemy(std::string const& filename, Animation const& animation, Ammunition const& ammo, sf::Color const& colorMask = sf::Color::Black);
	Ennemy(sf::Texture const& texture, Animation const& animation, Ammunition const& ammo, sf::Color const& colorMask = sf::Color::Black);
	Ennemy(AnimatedSprite const& baseModel, Ammunition const& ammo);
	Ennemy(ACharacter const& baseModel);
	Ennemy(Ennemy const& baseModel);
	~Ennemy();

public:

	void              update();
	void              move(float x = 0.0f, float y = 0.0f);

	int               _reloading;
};


#endif              /* !___ENNEMY_HH___ */
