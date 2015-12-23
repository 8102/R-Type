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
		InRound,
		InBlock,
		InBlock_straight,
		InLine_Bottom,
		InLine_middleLoose,
		InNarrowGrid
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

	sf::Vector2f		getTotalSize() const;

public:

	void					addItem(MenuElement *element);
	void					setBackground(MenuElement *element);
	void					setStyledElementsCadre(sf::FloatRect const& cadre);

public:

	void					setElementScale(MenuElement *element);
	void					setElementPosition(MenuElement *element);
	void					moveElements(sf::Vector2f const& v);
	void					setFocused(int const& index);
	void					changeFocused(int const& indexMove, bool const& limited = true);

public:

	void					applyInLineStyle();
	void					applyInRoundStyle();
	void					applyInLineBottomStyle();
	void					applyInNarrowGridStyle();
	void					applyStyle();

public:

	MenuElement*      getItemOnLocation(sf::Vector2i const& mousePosition);
	MenuElement*      getElementNextTo(MenuElement* element, int index);

public:

	void              resetElements();

private:

	std::string			_name;
	eMenuStyle			_style;
	sf::FloatRect			_cadre;

private:

	std::map< sf::Event, bool(*)(IInteractive&) >		_eventTable;
	std::vector<MenuElement *>								_items;
	MenuElement*													_background;

	MenuElement*													_focused;
};

#endif              /* !___GAME_MENU_HH___ */
