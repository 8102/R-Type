#include              "MenuElement.hh"
#include              "GameEngine.hh"
#include              "SoundSystem.hh"

MenuElement::MenuElement(sf::Texture const& texture, std::string const& text, sf::Font const& textFont, GameMenu* container, sf::Vector2f const& position, sf::Color const& color, int const& argument)
	: AGameElement(texture, 1), _text(text), _container(container), _texture(texture), _midground(nullptr), _font(textFont), _baseColor(color), _function(&MenuElement::defaultFunction), _hasBeenToggled(false), _applyStyle(true), _argument(0), _angle(0.0f) {
	setPosition(position);

	setOrigin(sf::Vector2f(getGlobalBounds().width / 2, getGlobalBounds().height / 2));
	_screenText.setFont(_font);
	_screenText.setString(_text);
	_screenText.setCharacterSize(50);
	adjustScreenTextPosition();
}

MenuElement::~MenuElement() {

	if (_midground != nullptr)
		delete _midground;
}

void                  MenuElement::update() {

	sf::Event		e;
	e.type = sf::Event::MouseMoved;

	if (_actions[e.type] != nullptr)
		(*this.*_actions[sf::Event::MouseMoved])(e);
}

void                  MenuElement::update(sf::Event const& event) {

	if (_actions[event.type] != nullptr)
		(*this.*_actions[event.type])(event);
}

void                  MenuElement::getDrawn() {

	GameEngine& engine = GameEngine::instanciate();

	if (_angle != 0.0f)
		setRotation(getRotation() + _angle);
	engine.draw(*this);
	if (_midground != nullptr)
		engine.draw(*_midground);
	engine.draw(_screenText);
}

void                  MenuElement::adjustScreenTextPosition(bool const& up) {

	sf::Vector2f        textPosition;

	if (getOrigin().x == 0.0f && getOrigin().y == 0.0f) {
		textPosition.x = getPosition().x + (getGlobalBounds().width / 2) - (_screenText.getGlobalBounds().width / 2);
		textPosition.y = getPosition().y + (getGlobalBounds().height / 2) - (_screenText.getGlobalBounds().height * (up == true ? (float)1.5 : 1.0f));
	}
	else {
		textPosition.x = getGlobalBounds().left + getOrigin().x - _screenText.getGlobalBounds().width / 2;
		textPosition.y = getGlobalBounds().top + getOrigin().y - _screenText.getGlobalBounds().height * (up == true ? (float)1.5 : 1.0f);
	}
	_screenText.setPosition(textPosition);
}

void                  MenuElement::setFunction(void (MenuElement::*function)(sf::Event const&)) {

	_function = function;
}

void                  MenuElement::setAction(sf::Event::EventType const& actionType, void (MenuElement::* action)(sf::Event const&), int const& value) {

	_actions[actionType] = action;
	_argument = value;
}

void                  MenuElement::setAction(sf::Event::EventType const& actionType, void (MenuElement::* action)(sf::Event const&)) {

	_actions[actionType] = action;
}

void					MenuElement::setBaseColor(sf::Color const& color) {

	_baseColor = color;
}

void                  MenuElement::reset() {

	setColor(_baseColor);
	_screenText.setColor(_baseColor);
	_hasBeenToggled = false;
	_angle = 0.0f;
}

void MenuElement::toggle(bool const & toggled)
{
	_hasBeenToggled = toggled;
}

void                  MenuElement::resumeGame(_unused sf::Event const& event) {

	if (requestGameEngine.isReady()) {
		SoundSystem::instanciate().getCurrentMusic().pause();
		SoundSystem::instanciate().setCurrentMusic("unity.wav");
		SoundSystem::instanciate().playMusic();
		GameEngine::instanciate().pause(false);
		requestGameEngine.launchGame();
		GameEngine::instanciate().setControllerIndex(AGameController::GameControls);
	}
}

void                  MenuElement::setPosition(sf::Vector2f const& position) {

	AGameElement::setPosition(position);
	adjustScreenTextPosition();
	if (_midground != nullptr) {
		_midground->setPosition(getPosition());
	}
}

void					MenuElement::setArgument(int const& argument) {

	_argument = argument;
}

void                  MenuElement::setMidground(sf::Sprite *elem)
{
	_midground = elem;
//	_midground->setOrigin(sf::Vector2f(_midground->getGlobalBounds().width / 2, _midground->getGlobalBounds().height / 2));

}

void MenuElement::applyStyle(bool const & style)
{
	_applyStyle = style;
}

bool MenuElement::applyStyle() const
{
	return _applyStyle;
}

void                  MenuElement::defaultFunction(_unused sf::Event const& event) {

	SoundSystem&        soundEngine = SoundSystem::instanciate();

	if (_hasBeenToggled == false) {
		_hasBeenToggled = true;
		soundEngine.pushEffect("blop.wav");
	}
	setColor(sf::Color(255, 120, 0));
	_screenText.setColor(sf::Color(255, 120, 0));
}


void MenuElement::startingFunction(sf::Event const & event)
{
	SoundSystem&        soundEngine = SoundSystem::instanciate();

	if (_hasBeenToggled == false) {
		_hasBeenToggled = true;
		soundEngine.pushEffect("blop.wav");
	}
	setColor(requestGameEngine.isReady() == true ? sf::Color::Green : sf::Color::Red);
	_screenText.setColor(sf::Color(255, 120, 0));
	_angle = 1.0f;
}

void MenuElement::movingFunction(sf::Event const & event)
{
	defaultFunction(event);
	_angle = 1.0f;
}

void                  MenuElement::quitGame(_unused sf::Event const& event) {

	GameEngine::instanciate().stop();
}

void MenuElement::changeMenu(sf::Event const & event)
{
	if (_container != nullptr)
		_container->setFocused(-1);
	GameEngine::instanciate().setControllerIndex(static_cast<AGameController::eController>(_argument));
}

void                  MenuElement::openOptionMenu(_unused sf::Event const& event) {

	GameEngine::instanciate().setControllerIndex(AGameController::OptionMenu);
}

void                  MenuElement::openMainMenu(_unused sf::Event const& event) {

	GameEngine::instanciate().setControllerIndex(AGameController::MainMenu);
}

void                  MenuElement::openSelectionMenu(_unused sf::Event const& event) {

	GameEngine::instanciate().setControllerIndex(AGameController::CharacterSelectionMenu);
}

void                  MenuElement::openConnectionMenu(_unused sf::Event const& event) {

	GameEngine::instanciate().setControllerIndex(AGameController::ConnectionMenu);
}

void                  MenuElement::openAudioMenu(_unused sf::Event const& event) {

	requestGameEngine.setControllerIndex(AGameController::AudioMenu);
}

void                  MenuElement::getIPAddrInput(sf::Event const& event) {

	std::string	regularIPExpression = "(\\d{1,3}(\\.\\d{1,3}){3})";
	std::regex		model(regularIPExpression);

	switch (event.text.unicode)
		{
		case 8:
			if (_text.size() > 0) { _text.pop_back(); }
			break;
		default:
			if ((event.text.unicode >= 48 && event.text.unicode <= 57) || event.text.unicode == '.')
				if (_text.size() < 16) { _text += static_cast< char >(event.text.unicode); }
			break;
		}
	_screenText.setString(_text);
	adjustScreenTextPosition(false);
}

void                  MenuElement::getLoginInput(sf::Event const& event) {
	
	std::regex		model("^[a-zA-Z0-9_]*");
	switch (event.text.unicode)
	{
	case 8:
		if (_text.size() > 0) { _text.pop_back(); }
		break;
	default:
		if (event.text.unicode == 32 && _actions[sf::Event::MouseButtonPressed] != nullptr)
			(*this.*_actions[sf::Event::MouseButtonPressed])(event);
		if (_text.size() < 12) { _text += static_cast< char >(event.text.unicode); }
			break;
	}
	if (std::regex_match(_text, model))
		_screenText.setString(_text);
	else
		_text.pop_back();
	adjustScreenTextPosition(false);
}

void								MenuElement::readjustAudioGaugeToMouseClick(std::string const& gaugeText, void (SoundSystem::*audioTarget)(float const&)) {
	
	float							ratio = 0.0f;
	int							newSize = 0;
	std::stringstream		ss;

	newSize = sf::Mouse::getPosition(requestGameEngine.getWindow()).x - (static_cast<int>(_midground->getGlobalBounds().left));
	newSize = (newSize < 0 ? 0 : (newSize > getGlobalBounds().width ? static_cast<int>(getGlobalBounds().width) : newSize));
	_midground->setTextureRect(sf::IntRect(0, 0, newSize, _midground->getTextureRect().height));
	ratio = static_cast<float>(_midground->getTextureRect().width * 100 / getTextureRect().width);
	((requestAudioEngine).*(audioTarget))(ratio);
	_screenText.setCharacterSize(25);
	_text = gaugeText + std::string(" : ");
	ss << ratio;
	_text += ss.str() + "%";
	_screenText.setString(_text);
	adjustScreenTextPosition();
}

void                  MenuElement::setEffectVolume(_unused sf::Event const& event) {

	if (_hasBeenToggled == true && _midground != nullptr)
		readjustAudioGaugeToMouseClick("Effects", &SoundSystem::setEffectVolume);
}

void                  MenuElement::setMusicVolume(_unused sf::Event const& event) {

	if (_hasBeenToggled == true && _midground != nullptr)
		readjustAudioGaugeToMouseClick("Music", &SoundSystem::setMusicVolume);
}


void                  MenuElement::setMasterVolume(_unused sf::Event const& event) {

	if (_hasBeenToggled == true && _midground != nullptr)
		readjustAudioGaugeToMouseClick("Master", &SoundSystem::setMasterVolume);
}

void                  MenuElement::toggleGauging(_unused sf::Event const& event) {

	_hasBeenToggled = !_hasBeenToggled;
}

void                  MenuElement::untoggleGauging(_unused sf::Event const& event) {

	_hasBeenToggled = false;
}

void					MenuElement::selectPlayer(sf::Event const& event) {

	setBaseColor(sf::Color::Green);
	requestGameEngine.setPlayer(&requestGameEngine._playF.getPlayer(_argument));
	requestGameEngine.getPlayer().setPosition(sf::Vector2f(400.0f, _argument * 100.0f));
	requestGameEngine.setController<PlayerController >(AGameController::GameControls, new PlayerController(requestGameEngine.getPlayer()));
}