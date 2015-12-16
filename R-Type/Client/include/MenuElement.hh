#ifndef          ___MENU_ELEMENT_HH___
# define         ___MENU_ELEMENT_HH___


# include        <SFML/Graphics.hpp>
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
		sf::Vector2f const& position = Vf(0.0f, 0.0f),
		sf::Color const& color = sf::Color::White,
		int const& argument = 0);
	~MenuElement();

public:

	void                  update();
	void                  update(sf::Event const& event);
	void                  getDrawn() const;
	void                  adjustScreenTextPosition();
	void                  setFunction(void (MenuElement::*)(sf::Event const& event));
	void					setBaseColor(sf::Color const & color);
	void                  reset();

	void                  setAction(sf::Event::EventType const& actionType, void (MenuElement::* action)(sf::Event const& event), int const& value);
	void                  setAction(sf::Event::EventType const& actionType, void (MenuElement::* action)(sf::Event const& event));
	void                  setPosition(sf::Vector2f const& position);
	void					setArgument(int const& argument);
	void                  setMidground(sf::Sprite* elem);

public:

	void					readjustAudioGaugeToMouseClick(std::string const& gaugeText, void (SoundSystem::*audioTarget)(float const&));

public:

	void                  defaultFunction(sf::Event const& event);
	void                  resumeGame(sf::Event const& event);
	void                  quitGame(sf::Event const& event);
	void                  openOptionMenu(sf::Event const& event);
	void                  openMainMenu(sf::Event const& event);
	void                  openConnectionMenu(sf::Event const& event);
	void                  openSelectionMenu(sf::Event const& event);
	void                  openAudioMenu(sf::Event const& event);
	void                  getIPAddrInput(sf::Event const& event);
	void                  getLoginInput(sf::Event const& event);
	void                  setEffectVolume(sf::Event const& event);
	void                  setMusicVolume(sf::Event const& event);
	void                  setMasterVolume(sf::Event const& event);
	void                  toggleGauging(sf::Event const& event);
	void                  untoggleGauging(sf::Event const& event);
	void					selectPlayer(sf::Event const& event);

private:

	std::string           _text;
	sf::Texture           _texture;
	sf::Sprite*           _midground;
	sf::Text              _screenText;
	sf::Font              _font;
	sf::Color             _baseColor;

	void                  (MenuElement::*_function)(sf::Event const& event);

	bool                  _hasBeenToggled;

private:

	int					_argument;
	std::map< sf::Event::EventType, void (MenuElement::*)(sf::Event const& event) >  _actions;
};

#endif           /* !___MENU_ELEMENT_HH___ */
