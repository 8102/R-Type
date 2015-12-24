#ifndef          ___MENU_ELEMENT_HH___
# define         ___MENU_ELEMENT_HH___


# include        <SFML/Graphics.hpp>
# include			<regex>

# include        "AGameElement.hh"
# include        "Client_graphicUtils.hh"
# include        "AssetManager.hh"
# include			"SoundSystem.hh"

class            GameMenu;

class            MenuElement : public AGameElement
{
public:

	MenuElement(sf::Texture const& texture,
		std::string const& text = "",
		sf::Font const& textFont = *AssetManager::instanciate().getFont("font.ttf"),
		GameMenu* container = nullptr,
		sf::Vector2f const& position = Vf(0.0f, 0.0f),
		sf::Color const& color = sf::Color::White,
		int const& argument = 0);
	~MenuElement();

public:

	void                  update();
	void                  update(sf::Event const& event);
	void                  getDrawn();
	void					adjustScreenScale();
	void                  adjustScreenTextPosition(bool const& up = true);
	void                  setFunction(void (MenuElement::*)(sf::Event const& event));
	void					setBaseColor(sf::Color const & color);
	void                  reset();
	void					toggle(bool const& toggled = true);

	void                 setAction(sf::Event::EventType const& actionType, void (MenuElement::* action)(sf::Event const& event), int const& value);
	void                 setAction(sf::Event::EventType const& actionType, void (MenuElement::* action)(sf::Event const& event));
	void					setPosition(sf::Vector2f const& position);
	void					setArgument(int const& argument);
	void                 setMidground(sf::Sprite* elem);

	void					applyStyle(bool const& style);
	bool					applyStyle() const;

public:

	void					readjustAudioGaugeToMouseClick(std::string const& gaugeText, void (SoundSystem::*audioTarget)(float const&));

public:

	void						connect(sf::Event const& event);
	void						defaultFunction(sf::Event const& event);
	void						movingFunction(sf::Event const& event);
	void						startingFunction(sf::Event const& event);
	void						resumeGame(sf::Event const& event);
	void						quitGame(sf::Event const& event);
	void						changeMenu(sf::Event const& event);
	void						openOptionMenu(sf::Event const& event);
	void						openMainMenu(sf::Event const& event);
	void						openConnectionMenu(sf::Event const& event);
	void						openSelectionMenu(sf::Event const& event);
	void						openAudioMenu(sf::Event const& event);
	void						getIPAddrInput(sf::Event const& event);
	void						getLoginInput(sf::Event const& event);
	void						setEffectVolume(sf::Event const& event);
	void						setMusicVolume(sf::Event const& event);
	void						setMasterVolume(sf::Event const& event);
	void						toggleGauging(sf::Event const& event);
	void						untoggleGauging(sf::Event const& event);
	void						selectPlayer(sf::Event const& event);
	void						scroll(sf::Event const& event);
	void						toggleScrolling(sf::Event const& event);
	void						untoggleScrolling(sf::Event const& event);

private:

	std::string           _text;
	GameMenu*		_container;
	sf::Texture           _texture;
	sf::Sprite*           _midground;
	sf::Text              _screenText;
	sf::Font              _font;
	sf::Color             _baseColor;

	void                  (MenuElement::*_function)(sf::Event const& event);

	bool                  _hasBeenToggled;
	bool					_scrolling;
	bool					_applyStyle;

private:

	int					_argument;
	float					_angle;
	std::map< sf::Event::EventType, void (MenuElement::*)(sf::Event const& event) >  _actions;
};

#endif           /* !___MENU_ELEMENT_HH___ */
