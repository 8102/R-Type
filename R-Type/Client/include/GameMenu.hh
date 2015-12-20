#ifndef             ___GAME_MENU_HH___
# define            ___GAME_MENU_HH___

# include           "Client_graphicUtils.hh"
# include           "AGameController.hh"
# include           "AGameElement.hh"
# include           "IInteractive.hh"
# include           "MenuElement.hh"

class               GameMenu : public AGameController
{
public:

	enum  eMenuStyle
	{
		InLine = 0,
		InGrid,
		InCircle,
		InBlock,
		InBlock_straight,
		InLine_Bottom,
		InLine_middleLoose
	};

public:

	GameMenu(std::string const& name = "Menu", eMenuStyle const& style = InBlock);
	~GameMenu();

public:

	void              draw();

public:

	bool              onMouseClickReleased(sf::Event const& event);
	bool              handleEvent(sf::Event const& event);
	bool              handleKeysDown();
	bool              onMouseClick(sf::Event const& event);
	bool              onKeyPressed(sf::Event const& event);
	bool              onClose(sf::Event const& event);
	bool              onMouseOver(sf::Event const& event);
	bool              onText(sf::Event const& event);

public:

	sf::Vector2f	getTotalSize() const;

public:

	void              addItem(MenuElement *element);
	void              setBackground(MenuElement *element);

public:

	void              setElementScale(MenuElement *element);
	void              setElementPosition(MenuElement *element);
	void					setFocused(int const& index);
	void					changeFocused(int const& indexMove, bool const& limited = true);
	void              applyStyle();

public:

	MenuElement*      getItemOnLocation(sf::Vector2i const& mousePosition);
	MenuElement*      getElementNextTo(MenuElement* element, int index);

public:

	void              resetElements();

private:

	std::string       _name;
	eMenuStyle        _style;

private:

	std::map< sf::Event, bool(*)(IInteractive&) >   _eventTable;
	std::vector<MenuElement *>                       _items;
	MenuElement*                                     _background;

	MenuElement*                                     _focused;
};

#endif              /* !___GAME_MENU_HH___ */
