#ifndef                 ___ABSTRACT_GAME_CONTROLLER_HH___
# define                ___ABSTRACT_GAME_CONTROLLER_HH___

# include               "IInteractive.hh"
# include               "Client_graphicUtils.hh"
# include               "AnimatedSprite.hh"

/*
**  Abstract Class AGameController :
**
**    Serves as a layer of Event handler.
**    GameEngine switches GameController according to the menus or the game.
**    While each menu got its Own controls,
**    In-Game controls are directly linked to the Player Class GameElement
*/

class                   AGameController : public IInteractive
{

public:

	AGameController();
	virtual ~AGameController() = 0;

public:

	bool                          handleEvent(sf::Event const& event);
	virtual bool                  handleKeysDown() = 0;
	virtual void                  draw() = 0;

	virtual bool                  onMouseClickReleased(sf::Event const& event) = 0;
	virtual bool                  onMouseClick(sf::Event const& event) = 0;
	virtual bool                  onMouseOver(sf::Event const& event) = 0;
	virtual bool                  onKeyPressed(sf::Event const& event) = 0;
	virtual bool                  onClose(sf::Event const& event) = 0;
	virtual bool                  onText(sf::Event const& event) = 0;

public:

	/* this enum is used in the GameEngine which relates each element of eController to a AGameController */
	enum eController {

		GameControls = 0,
		MainMenu,
		ConnectionMenu,
		CharacterSelectionMenu,
		InGameMenu,
		OptionMenu,
		AudioMenu,
		VideoMenu,
		CreditsMenu
	};

};

#endif                  /* !___ABSTRACT_GAME_CONTROLLER_HH___ */
