#ifndef										___BONUS_FACTORY_HH___
# define									___BONUS_FACTORY_HH___

#include									"Bonus.hh"

class BonusFactory
{
public:

	struct				bonusParams {

		std::string		texture;
		std::string		anim;
		std::string		fonction;
		sf::Color			colorMask;
	};

public:

	BonusFactory();
	~BonusFactory();

	void					clear();

public:

	void					loadConfig();
	Bonus*				createBonus(std::string const& name, sf::Vector2f const& position, int const& value = 1);

private:

	std::map<std::string, Bonus::bonusFct>					_BonusFunctions;
	std::map<std::string, bonusParams>						_config;
	std::map<std::string, std::unique_ptr<Bonus>>	_models;
};

#endif										/* ___BONUS_FACTORY_HH___  */