#ifndef             ___AMMUNITION_HH___
# define            ___AMMUNITION_HH___

# include           "AnimatedSprite.hh"
# include           "AGameElement.hh"
# include			 "FX.hh"

class               ACharacter;

class               Ammunition : public AnimatedSprite
{
public:

	enum eTargets
	{
		friendlyShot = 0,
		EnnemyShot,
		NeutralShot
	};

public:

	Ammunition(std::string const& filename, Animation const& pattern, unsigned int speed = 100, sf::Color const& colorMask = sf::Color::Black);
	Ammunition(sf::Texture const& texture, Animation const& pattern, unsigned int speed = 100, sf::Color const& colorMask = sf::Color::Black);
	Ammunition(Ammunition const& model);
	~Ammunition();

public:

	void              update();

	bool				 dealDamage(ACharacter& target);
	void				 trigger();

public:

	void              setTargetPosition(sf::Vector2f const& targetPosition);
	void              setSpeed(unsigned int const& speed);
	void				 setDamage(int const& damage);
	void              setMovement(sf::Vector2f const& movement);
	void              setType(eTargets const& type);
	void              setTarget(ACharacter& target);
	void				setDeathFX(std::string const& aName, std::string const& rName, std::string const& eName, sf::Color const& colorMask);

public:

	sf::Vector2f			getTargetPosition() const;
	unsigned int			getSpeed() const;
	int						getDamage() const;
	sf::Vector2f			getMovement() const;
	AGameElement*   getTarget() const;
	eTargets				getType() const;
	FX							getDeathFX() const;

	Ammunition&       operator=(Ammunition const& model);

private:

	sf::Vector2f			_targetPosition;
	unsigned int			_speed;
	int						_damage;
	sf::Vector2f			_movement;
	AGameElement*   _target;

	eTargets				_type;

private:

	FX						  _deathFX;

};

#endif              /* !___AMMUNITION_HH___ */
