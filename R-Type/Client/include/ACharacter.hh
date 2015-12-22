#ifndef               ___ABSTRACT_CHARACTER_HH___
# define              ___ABSTRACT_CHARACTER_HH___

# include             "AnimatedSprite.hh"
# include             "Ammunition.hh"

/*
**  Class   Abstract Character :
**
**  Represents the Abstract model of any game-interactive entity,
**  such as Player or ennemies.
**  They are pre-typed Abstract GameElements.
*/
class                 ACharacter : public AnimatedSprite
{
public:

	/* The ammunition field must be included, as it will be inherant of a Character to be able to shoot */
	ACharacter(std::string const& filename, Animation const& animation, Ammunition const& weapon, sf::Color const& colorMask = sf::Color::Black);
	ACharacter(sf::Texture const& texture, Animation const& animation, Ammunition const& weapon, sf::Color const& colorMask = sf::Color::Black);
	ACharacter(AnimatedSprite const& baseModel, Ammunition const& weapon);
	ACharacter(ACharacter const& model);

	~ACharacter();

public:

	void               move(int xAxis, int yAxis);

	/*
	**  shoot functions() :
	**  shotOriginVertex represent the points of the sprite used to represent the character,
	**  from which the ammo must be shot. */
	void               shoot(unsigned int shotOriginVertexIndex = 0);
	void               shoot(ACharacter& target, unsigned int shotOriginVertexIndex = 0);
	void               shoot(sf::Vector2f const& targetPosition, unsigned int shotOriginVertexIndex = 0);
	void               shoot(sf::Vector2f const& targetPosition, bool allWeapons = false);

	template< class T >
	void               shoot(T&, bool useAllWeapon = false, unsigned int const& shotOriginVertexIndex = 0);

	void				die();

public:

	unsigned int       getSpeed() const;
	sf::Vector2i		  getLife() const;
	std::string			  getName() const;
	Ammunition       getWeapon() const;
	sf::Text				  getGraphicName() const;
	FX						  getDeathFX() const;
	void               addWeapon(Ammunition* ammo);

	std::vector<Ammunition>     getAllWeapons() const;

public:

	void               setSpeed(unsigned int const& speed);
	void				  setLife(sf::Vector2i const& life);
	void				  setName(std::string const& name);
	void					setDeathFX(std::string const& aName, std::string const& rName, std::string const& eName, sf::Color const& colorMask);

public:

	void              addShotVertex(sf::Vector2f const& shotOriginVertex);
	std::vector<sf::Vector2f>  getShotVertices() const;

public:

	void						drawName(sf::RenderWindow& win);
	void						drawLife(sf::RenderWindow& win, bool const& up = true);
	void						drawInformation(sf::RenderWindow& win);

protected:

	unsigned int       _speed;
	sf::Vector2i		  _health;
	std::string			  _name;

protected:

	Ammunition        _weapon;

protected:

	std::vector<Ammunition> _weapons;

protected:

	/* Represents all the possible origin points from which the Character can shot */
	std::vector< sf::Vector2f > _shotVertexes;
	unsigned int						 _index;

protected:

	sf::Text				_gName;
	FX							_deathFX;
};

#endif                /* !___ABSTRACT_CHARACTER_HH___ */
