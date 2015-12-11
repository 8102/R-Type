#ifndef             ___AMMUNITION_HH___
# define            ___AMMUNITION_HH___

# include           "AnimatedSprite.hh"
# include           "AGameElement.hh"

class               ACharacter;

//?templaté selon target ?
class               Ammunition : public AnimatedSprite /*, public CallBack ? */
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
	// Ammunition(AnimatedSprite const& baseObject, sf::Vector2f const& pattern);
	// Ammunition(AnimatedSprite const& baseObject, AGameElement const& target);
	~Ammunition();

public:

	void              update();

public:

	void              setTargetPosition(sf::Vector2f const& targetPosition);
	void              setSpeed(unsigned int const& speed);
	void              setMovement(sf::Vector2f const& movement);
	void              setType(eTargets const& type);
	void              setTarget(ACharacter& target);

public:

	sf::Vector2f      getTargetPosition() const;
	unsigned int      getSpeed() const;
	sf::Vector2f      getMovement() const;
	AGameElement*     getTarget() const;
	eTargets          getType() const;

	Ammunition&       operator=(Ammunition const& model);

private:

	sf::Vector2f      _targetPosition;
	unsigned int      _speed;
	sf::Vector2f      _movement;
	AGameElement*     _target;

	eTargets          _type;

};

#endif              /* !___AMMUNITION_HH___ */
