#include          "GameMenu.hh"
#include          "GameEngine.hh"

GameMenu::GameMenu(std::string const& name, eMenuStyle const& style)
	: AGameController(), _name(name), _style(style), _background(nullptr), _focused(nullptr) {

}

GameMenu::~GameMenu() {

	for (auto it = _items.begin(); it != _items.end(); it++)
		delete *it;
	if (_background != nullptr)
		delete _background;
};

void                  GameMenu::draw() {

	if (_background)
		_background->getDrawn();
	for (auto it = _items.begin(); it != _items.end(); it++) {
		{
			(*it)->getDrawn();
		}
	}
}


bool                  GameMenu::handleKeysDown() { return false; }

bool                  GameMenu::onMouseOver(/* _unused */ sf::Event const& event) {

	MenuElement*        target;

	if ((target = getItemOnLocation(sf::Mouse::getPosition(GameEngine::instanciate().getWindow()))) == nullptr)
	{
		resetElements();
		return false;
	}
	for (auto it = _items.begin(); it != _items.end(); it++)
	{
		if (*it != target)
			(*it)->reset();
	}
	target->update(event);
	return true;
}

bool                  GameMenu::onMouseClick(/* _unused */ sf::Event const& event) {

	MenuElement*        target;

	if ((target = getItemOnLocation(sf::Mouse::getPosition(GameEngine::instanciate().getWindow()))) == nullptr)
		return false;
	target->update(event);
	for (auto it = _items.begin(); it != _items.end(); it++)
		if (*it != target)
			(*it)->setBaseColor(sf::Color::White);

	_focused = target;
	return true;
}

bool                  GameMenu::onMouseClickReleased(sf::Event const& event) {

	MenuElement*        target;

	if ((target = getItemOnLocation(sf::Mouse::getPosition(GameEngine::instanciate().getWindow()))) == nullptr)
		return false;
	target->update(event);
	_focused = target;
	return true;
}

bool                  GameMenu::onKeyPressed(/* _unused */ sf::Event const& event) {

	GameEngine&         engine = GameEngine::instanciate();

	switch (event.key.code)
	{
	case sf::Keyboard::Escape:
		engine.stop();
		break;
	default:
		break;
	}
	return true;
}

bool                  GameMenu::onClose(/* _unused */ sf::Event const& event) {
	return true;
}

bool                  GameMenu::onText(sf::Event const& event)
{
	if (_focused != nullptr)
		_focused->update(event);
	return true;
}

void                  GameMenu::addItem(MenuElement *element) {

	_items.push_back(element);
}

void                  GameMenu::setBackground(MenuElement *element) {

	setElementScale(element);
	_background = element;
}

void                  GameMenu::setElementScale(MenuElement *element) {

	sf::Vector2f      newScale;
	sf::Vector2u      winSize = requestGameEngine.getWindow().getSize();

	newScale = sf::Vector2f(winSize.x / element->getLocalBounds().width,
		winSize.y / element->getLocalBounds().height);
	element->setScale(newScale);
}

void                 GameMenu::setElementPosition(MenuElement *element) {

	(void)element;
}

void                 GameMenu::applyStyle() {

	sf::Vector2f       nextElemPosition;
	for (auto it = _items.begin(); it != _items.end(); it++)
	{
		if (_style == InLine)
		{
			sf::Vector2f		 total(0, 0);
			for (auto i = _items.begin(); i != _items.end(); i++) {
				total.x += (*it)->getGlobalBounds().width;
				total.y += (*it)->getGlobalBounds().height;
			}
			sf::Vector2f anchor(requestGameEngine.getWindow().getSize().x / 2 - total.x / 2, requestGameEngine.getWindow().getSize().y / 2);
			auto xStart = anchor.x;
			for (auto it = _items.begin(); it != _items.end(); it++) {
				std::cout << "position : " << xStart << " , " << "anchor.y" << std::endl;
				(*it)->setPosition(Vf(xStart, anchor.y - (*it)->getGlobalBounds().height / 2));
				xStart += (*it)->getGlobalBounds().width;
			}
		}
		if (_style == InBlock)
		{
			auto i = it - _items.begin();
			nextElemPosition = sf::Vector2f(requestGameEngine.getWindow().getSize().x / 2 - (*it)->getGlobalBounds().width / 2,
				(requestGameEngine.getWindow().getSize().y / _items.size()) * i + (*it)->getGlobalBounds().height / _items.size());
			(*it)->setPosition(nextElemPosition);
		}
		if (_style == InBlock_straight)
		{
			auto i = it - _items.begin();
			unsigned int sizeH = 0;
			for (auto it2 = _items.begin(); it2 != _items.end(); it2++)
				sizeH += static_cast< unsigned int >((*it2)->getGlobalBounds().height * 1.5);
			nextElemPosition = sf::Vector2f(requestGameEngine.getWindow().getSize().x / 2 - (*it)->getGlobalBounds().width / 2,
				static_cast<float>(((requestGameEngine.getWindow().getSize().y / 2) - sizeH / 2) + (sizeH / _items.size() * i)));
			(*it)->setPosition(nextElemPosition);
		}
		if (_style == InCircle)
		{
			auto i = it - _items.begin();
			float x = static_cast<float>(requestGameEngine.getWindow().getSize().x / 4),
					y = static_cast<float>(requestGameEngine.getWindow().getSize().y / 2),
					rx = static_cast<float>(requestGameEngine.getWindow().getSize().x / 4),
					ry = static_cast<float>(requestGameEngine.getWindow().getSize().y / 4),
					a = static_cast<float>((M_PI * ((360 / _items.size()) * i)) / 180);
			nextElemPosition = sf::Vector2f(x + rx * std::cos(a), y + ry * std::sin(a));
			(*it)->setPosition(nextElemPosition);
		}
	}
}

MenuElement*         GameMenu::getItemOnLocation(sf::Vector2i const& mousePosition) {

	for (auto it = _items.begin(); it != _items.end(); it++)
		if ((*it)->containsPoint(mousePosition) == true)
			return *it;
	return nullptr;
}

void                 GameMenu::resetElements() {

	for (auto it = _items.begin(); it != _items.end(); it++)
	{
		(*it)->reset();
	}
}

MenuElement*        GameMenu::getElementNextTo(MenuElement* element, int index)
{

	int newIndex = 0;

	for (auto it = _items.begin(); it != _items.end(); it++)
	{
		if (*it == element)
			return newIndex + index < 0 ? _items[0] : (static_cast<size_t>(newIndex) > _items.size() ? _items[_items.size()] : _items[newIndex + index]);
		++newIndex;
	}
	return element;
}
