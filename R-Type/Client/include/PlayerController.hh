#ifndef             ___PLAYER_CONTROLLER_HH___
# define            ___PLAYER_CONTROLLER_HH___

#include            "AGameController.hh"
#include            "Player.hpp"

class               PlayerController : public AGameController
{

public:

	PlayerController(Player& player);
	~PlayerController();

public:

	bool              handleKeysDown();
	void              draw() {};

	bool              onMouseClickReleased(sf::Event const& event);
	bool              onMouseClick(sf::Event const& event);
	bool              onMouseOver(sf::Event const& event);
	bool              onKeyPressed(sf::Event const& event);
	bool              onClose(sf::Event const& event);
	bool              onText(sf::Event const& event);

public:

	void              openMainMenu();

private:

	Player&  _player;

};

#endif              /* !___PLAYER_CONTROLLER_HH___ */
