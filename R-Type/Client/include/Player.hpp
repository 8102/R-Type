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

	void                update();
	void                move(int xAxis = 0, int yAxis = 0);
	void                shoot(unsigned int shotOriginVertex = 0);
	void                switchWeapon();

public:

	bool                canShot() const;
	void                isReloading();

private:

	int                 _reload;
	int                 _reloadingTime;
	bool                _canShot;

private:

	unsigned int        _weaponIndex;

};

template < class T, class ... Args >
std::unique_ptr< T > make_unique(Args&& ... args) {
	return std::unique_ptr< T >(new T(std::forward< Args >(args)...));
}

#endif                /* !___PLAYER_HPP___ */
