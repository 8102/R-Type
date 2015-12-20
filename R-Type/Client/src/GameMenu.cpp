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

	if (_focused != nullptr)
		_focused->update();
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
	_focused = target;
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

		case sf::Keyboard::Tab:
			changeFocused(1, false);
			break;

		case	sf::Keyboard::Up:
			changeFocused(-1);
			break;

		case	sf::Keyboard::Down:
			changeFocused(1);
			break;

		case sf::Keyboard::Left:
			changeFocused(-1);
			break;

		case	sf::Keyboard::Right:
			changeFocused(1);
			break;

		case sf::Keyboard::Return :
			if (_focused != nullptr)
			{
				sf::Event e;

				e.type =  sf::Event::MouseButtonPressed;
				_focused->update(e);
			}
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

sf::Vector2f					GameMenu::getTotalSize() const
{
	sf::Vector2f				totalSize(0.0f, 0.0f);

	for (auto it = _items.begin(); it != _items.end(); it++) {
		totalSize.x += (*it)->getGlobalBounds().width;
		totalSize.y += (*it)->getGlobalBounds().height;
	}
	return totalSize;
}

void                  GameMenu::addItem(MenuElement *element) {

	_items.push_back(element);
}

void                  GameMenu::setBackground(MenuElement *element) {

	sf::Vector2f	center(requestGameEngine.getWindow().getSize().x / 2, requestGameEngine.getWindow().getSize().y / 2);

	setElementScale(element);
	_background = element;
	_background->setPosition(center);
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

void GameMenu::setFocused(int const & index)
{
	_focused = (index < 0 || index >= _items.size()) ? nullptr : _items[index];
}

void GameMenu::changeFocused(int const & indexMove, bool const& limited)
{
	if (_focused != nullptr) {
		for (auto it = _items.begin(); it != _items.end(); it++)
			if (*it == _focused) {
				size_t index = std::distance(_items.begin(), it);
				if (limited == true) index = (index == 0 && indexMove < 0 ? 0 : (index + indexMove >= _items.size() ? _items.size() - 1 : index + indexMove));
				else index = (index == 0 &&  indexMove < 0 ? _items.size() - 1 : (index + indexMove >= _items.size() ? 0 : index + indexMove));
				resetElements();
				_focused = _items[index];
				break;
			}
	}
	else _focused = _items.size() > 0 ? _items[0] : nullptr;

}


void                 GameMenu::applyStyle() {

	sf::Vector2f	center(requestGameEngine.getWindow().getSize().x / 2, requestGameEngine.getWindow().getSize().y / 2);
	sf::Vector2f	totalSize = getTotalSize();
	sf::Vector2f  nextElemPosition(center.x - totalSize.x / 2, center.y - totalSize.y / 2);

	int i = 0;
	for (auto it = _items.begin(); it != _items.end(); it++)
	{
		if (_style == InLine)
		{
			(*it)->setPosition(sf::Vector2f(nextElemPosition.x + (*it)->getGlobalBounds().width / 2, center.y));
			nextElemPosition.x += (*it)->getLocalBounds().width;
		}
		if (_style == InBlock)
		{
			float f = static_cast<float>(std::sqrt(_items.size()));
			int sideSize = static_cast<int>(f);
			std::cout << sideSize << std::endl;
			std::cout << f << std::endl;
			sf::Vector2f padding(center.x / f, center.y / f);
			std::cout << padding.x << std::endl;
			sf::Vector2f position(padding.x + (static_cast<int>(i) % sideSize) * (padding.x * 2.0f), padding.y + (static_cast<int>(i) / sideSize) * (padding.y * 1.5f));
			std::cout << position.x << std::endl;
			(*it)->setPosition(position);
		}
		if (_style == InBlock_straight)
		{
			auto i = it - _items.begin();
			unsigned int sizeH = 0;
			for (auto it2 = _items.begin(); it2 != _items.end(); it2++)
				sizeH += static_cast< unsigned int >((*it2)->getGlobalBounds().height * 1.5);
			nextElemPosition = sf::Vector2f(requestGameEngine.getWindow().getSize().x / 2,
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

		if (_style == InLine_Bottom)
		{
			(*it)->setPosition(sf::Vector2f(nextElemPosition.x + (*it)->getGlobalBounds().width / 2, center.y / 3 * 5));
			nextElemPosition.x += (*it)->getLocalBounds().width;
		}
		++i;
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
	if (_focused != nullptr)
		_focused->toggle();
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
