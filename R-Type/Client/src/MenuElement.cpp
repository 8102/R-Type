#include              "MenuElement.hh"
#include              "GameEngine.hh"
#include              "SoundSystem.hh"

MenuElement::MenuElement(sf::Texture const& texture, std::string const& text, sf::Font const& textFont, sf::Vector2f const& position, sf::Color const& color)
	: AGameElement(texture, 1), _text(text), _texture(texture), _midground(nullptr), _font(textFont), _baseColor(color), _function(&MenuElement::defaultFunction), _hasBeenToggled(false) {
	setPosition(position);

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

}

void                  MenuElement::update(sf::Event const& event) {

	if (_actions[event.type] != nullptr)
		(*this.*_actions[event.type])(event);
}

void                  MenuElement::getDrawn() const {

	GameEngine& engine = GameEngine::instanciate();

	engine.draw(*this);
	if (_midground != nullptr)
		engine.draw(*_midground);
	engine.draw(_screenText);
}

void                  MenuElement::adjustScreenTextPosition() {

	sf::Vector2f        textPosition;

	textPosition.x = getPosition().x + (getGlobalBounds().width / 2) - (_screenText.getGlobalBounds().width / 2);
	textPosition.y = getPosition().y + (getGlobalBounds().height / 2) - (_screenText.getGlobalBounds().height * (float)1.5);
	_screenText.setPosition(textPosition);
}

void                  MenuElement::setFunction(void (MenuElement::*function)(sf::Event const&)) {

	_function = function;
}

void                  MenuElement::setAction(sf::Event::EventType const& actionType, void (MenuElement::* action)(sf::Event const&)) {

	_actions[actionType] = action;
}

void                  MenuElement::reset() {

	_screenText.setColor(_baseColor);
	_hasBeenToggled = false;
}

void                  MenuElement::resumeGame(/* _unused */ sf::Event const& event) {

	SoundSystem::instanciate().getCurrentMusic().pause();
	SoundSystem::instanciate().setCurrentMusic("unity.wav");
	SoundSystem::instanciate().playMusic();
	GameEngine::instanciate().pause(false);
	GameEngine::instanciate().setControllerIndex(AGameController::GameControls);
}

void                  MenuElement::setPosition(sf::Vector2f const& position) {

	AGameElement::setPosition(position);
	adjustScreenTextPosition();
	if (_midground != nullptr) {
		_midground->setPosition(getPosition());
	}
}

void                  MenuElement::setMidground(sf::Sprite *elem)
{
	_midground = elem;
}

void                  MenuElement::defaultFunction(/* _unused */ sf::Event const& event) {

	SoundSystem&        soundEngine = SoundSystem::instanciate();

	if (_hasBeenToggled == false) {
		_hasBeenToggled = true;
		soundEngine.pushEffect("blop.wav");
	}
	_screenText.setColor(sf::Color::Cyan);
}

void                  MenuElement::quitGame(/* _unused */ sf::Event const& event) {

	GameEngine::instanciate().stop();
}

void                  MenuElement::openOptionMenu(/* _unused */ sf::Event const& event) {

	GameEngine::instanciate().setControllerIndex(AGameController::OptionMenu);
}

void                  MenuElement::openMainMenu(/* _unused */ sf::Event const& event) {

	GameEngine::instanciate().setControllerIndex(AGameController::MainMenu);
}

void                  MenuElement::openConnectionMenu(/* _unused */ sf::Event const& event) {

	GameEngine::instanciate().setControllerIndex(AGameController::ConnectionMenu);
}

void                  MenuElement::openAudioMenu(/* _unused */ sf::Event const& event) {

	requestGameEngine.setControllerIndex(AGameController::AudioMenu);
}

void                  MenuElement::getIPAddrInput(sf::Event const& event) {

	switch (event.text.unicode)
	{
	case 8:
		if (_text.size() > 0) { _text.pop_back(); }
		break;
	default:
		if ((event.text.unicode >= 48 && event.text.unicode <= 57) || event.text.unicode == '.')
			if (_text.size() < 17) { _text += static_cast< char >(event.text.unicode); }
		break;
	}
	_screenText.setString(_text);
	adjustScreenTextPosition();
}

void                  MenuElement::getLoginInput(sf::Event const& event) {

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
	_screenText.setString(_text);
	adjustScreenTextPosition();
}

void                  MenuElement::setEffectVolume(/* _unused */ sf::Event const& event) {

	float               ratio = 0.0f;
	std::stringstream   ss;

	if (_hasBeenToggled == true && _midground != nullptr)
	{
		_midground->setTextureRect(sf::IntRect(0, 0, sf::Mouse::getPosition(requestGameEngine.getWindow()).x - _midground->getPosition().x , _midground->getTextureRect().height));
		ratio = _midground->getTextureRect().width * 100 / getTextureRect().width;
		requestAudioEngine.setEffectVolume(ratio);
		_screenText.setCharacterSize(25);
		_text = "Effects : ";
		ss << ratio + 1;
		_text += ss.str() + "%";
		_screenText.setString(_text);
		adjustScreenTextPosition();
	}
}

void                  MenuElement::setMusicVolume(/* _unused */ sf::Event const& event) {

	float               ratio = 0.0f;
	std::stringstream   ss;

	if (_hasBeenToggled == true && _midground != nullptr)
	{
		_midground->setTextureRect(sf::IntRect(0, 0, sf::Mouse::getPosition(requestGameEngine.getWindow()).x - _midground->getPosition().x , _midground->getTextureRect().height));
		ratio = _midground->getTextureRect().width * 100 / getTextureRect().width;
		requestAudioEngine.setMusicVolume(ratio);
		_screenText.setCharacterSize(25);
		_text = "Music : ";
		ss << ratio + 1;
		_text += ss.str() + "%";
		_screenText.setString(_text);
		adjustScreenTextPosition();
	}
}


void                  MenuElement::setMasterVolume(/* _unused */ sf::Event const& event) {

	float               ratio = 0.0f;
	std::stringstream   ss;

	if (_hasBeenToggled == true && _midground != nullptr)
	{
		_midground->setTextureRect(sf::IntRect(0, 0, sf::Mouse::getPosition(requestGameEngine.getWindow()).x - _midground->getPosition().x , _midground->getTextureRect().height));
		ratio = _midground->getTextureRect().width * 100 / getTextureRect().width;
		requestAudioEngine.setMasterVolume(ratio);
		_screenText.setCharacterSize(25);
		_text = "Master : ";
		ss << ratio + 1;
		_text += ss.str() + "%";
		_screenText.setString(_text);
		adjustScreenTextPosition();
	}
}

void                  MenuElement::toggleGauging(/* _unused */ sf::Event const& event) {

	_hasBeenToggled = !_hasBeenToggled;
}

void                  MenuElement::untoggleGauging(/* _unused */ sf::Event const& event) {

	_hasBeenToggled = false;
}
