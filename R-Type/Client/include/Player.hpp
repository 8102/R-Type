#ifndef               ___PLAYER_HPP___
# define              ___PLAYER_HPP___

# include             "ACharacter.hh"

class                 Player : public ACharacter
{

public:

	Player(std::string const& filename, Animation const& animation, Ammunition const& ammo, sf::Color const& colorMask);
	Player(sf::Texture const& texture, Animation const& animation, Ammunition const& ammo, sf::Color const& colorMask);
	Player(AnimatedSprite const& baseModel, Ammunition const& ammo);
	Player(ACharacter const& baseModel);
	~Player();

public:

	void						update();
	void						getDrawn(sf::RenderWindow& win);

	void						move(int xAxis = 0, int yAxis = 0);
	void						shoot(unsigned int shotOriginVertex = 0);
	void						switchWeapon();
	void						activateShield(bool const& shieldState);
	void						receiveDamage(Ammunition const& it);
	bool						collide(AGameElement const& collider, bool const& shieldCollision = true) const;
	bool						isAlive() const;

	bool						isPlayed() const;
	void						isPlayed(bool const& played);

public:

	bool						canShot() const;
	void						indicateCurrentPlayer(sf::RenderWindow & win);
	void						isReloading();

public:

	Ammunition		getWeapon() const;

	AnimatedSprite	getShield() const;
	bool						isShielded() const;
	sf::Vector2i			getEnergy() const;

	void						setEnergy(sf::Vector2i const& v);

private:

	int						_reload;
	int						_reloadingTime;
	bool						_canShot;

private:

	unsigned int        _weaponIndex;

private:

	AnimatedSprite	_shield;
	bool						_isShielded;
	sf::Vector2i			_energy;

private:

	bool					_played;

private:

	static AnimatedSprite&	initPlayerShield();
};

template < class T, class ... Args >
std::unique_ptr< T > make_unique(Args&& ... args) {
	return std::unique_ptr< T >(new T(std::forward< Args >(args)...));
}

#endif                /* !___PLAYER_HPP___ */
