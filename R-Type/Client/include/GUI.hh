#ifndef									___GUI_HH___
# define								___GUI_HH___

# include								"Client_graphicUtils.hh"
# include								"Player.hpp"

class GUI
{
public:

	GUI(Player const& player, sf::RenderWindow& window);
	~GUI();

public:

	void									drawUserInfo();
	void									drawEnnemyInfo(ACharacter const& character);
	void									drawPlayerInfo(ACharacter const& character);
	void									drawScore(unsigned int const& currentScore);

	void									messageBox(sf::Vector2f const& position, std::string const& message, unsigned int const& fontSize);

private:

	Player const &					_player;
	sf::RenderWindow&		_win;

private:

	sf::Text								_score;
	sf::Sprite							_lifebar;
	sf::Sprite							_energyBar;

	sf::RectangleShape			_deadMask;
};

#endif								   /* !___GUI_HH___*/