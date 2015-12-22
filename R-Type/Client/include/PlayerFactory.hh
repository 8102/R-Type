#ifndef							___PLAYER_FACTORY_HH___
# define						___PLAYER_FACTORY_HH___

# include						"Player.hpp"

class PlayerFactory
{

	struct	playerParams {

		std::string							textureName;
		std::string							animationName;
		std::string							weaponName;
		std::vector<std::string>		_additionalWeapons;
		sf::Color								_colorMask;
		unsigned int						_speed;
		sf::Vector2i							health;
		std::string							name;
		std::vector<sf::Vector2f>	shotVertices;
	};

public:
	PlayerFactory();
	~PlayerFactory();

public:
	
	Player&					getPlayer(int const& playerID);
	void							loadConfigs();
	void							loadPlayer(int const& playerID);
private:

	std::map < int, std::pair<struct playerParams , std::unique_ptr<Player >> >		_bluePrint;
};

#endif							/* !___PLAYER_FACTORY_HH___ */