#include          "GameMenu.hh"
#include          "GameEngine.hh"

GameMenu::GameMenu(std::string const& name, eMenuStyle const& style)
	: AGameController(), _name(name), _style(style), _cadre(sf::Vector2f(0.0f, 0.0f), sf::Vector2f(0.0f, 0.0f)), _background(nullptr), _focused(nullptr) {

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

bool                  GameMenu::onMouseOver(_unused sf::Event const& event) {

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

bool                  GameMenu::onMouseClick(_unused sf::Event const& event) {

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

bool                  GameMenu::onKeyPressed(_unused sf::Event const& event) {

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

bool                  GameMenu::onClose(_unused sf::Event const& event) {
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
		if ((*it)->applyStyle() == true) {
			totalSize.x += (*it)->getGlobalBounds().width;
			totalSize.y += (*it)->getGlobalBounds().height;
		}
	}
	return totalSize;
}

void                  GameMenu::addItem(MenuElement *element) {

	_items.push_back(element);
}

void                  GameMenu::setBackground(MenuElement *element) {

	sf::Vector2f	center(requestGameEngine.getWindow().getSize().x / 2.0f, requestGameEngine.getWindow().getSize().y / 2.0f);

	setElementScale(element);
	_background = element;
	_background->setPosition(center);
}

void GameMenu::setStyledElementsCadre(sf::FloatRect const & cadre)
{
	_cadre = cadre;
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

void GameMenu::moveElements(sf::Vector2f const & v)
{
	sf::Vector2f	center(requestGameEngine.getWindow().getSize().x / 2.0f, requestGameEngine.getWindow().getSize().y / 2.0f);
	sf::Vector2f	totalSize = getTotalSize();

	for (auto it = _items.begin(); it != _items.end(); it++) {
		if ((*it)->applyStyle() == true) {

			float nextY = (*it)->getPosition().y + v.y + (*it)->getGlobalBounds().height + 10.0f;
			(*it)->setPosition(sf::Vector2f((*it)->getPosition().x + v.x, (*it)->getPosition().y + v.y));
			float ratio = 1.0f - ((std::abs((*it)->getPosition().y - center.y) * 100 / center.y) / 100);
			(*it)->setScale(ratio, ratio);
			(*it)->adjustScreenScale();
			(*it)->setColor(sf::Color(255, 255, 255, static_cast<int>(255 * ratio * 0.9f)));


			//std::cout << (*it)->getTextureRect().height << " --- " << (*it)->getGlobalBounds().height << std::endl;
			//sf::IntRect r = (*it)->getTextureRect();
			////sf::IntRect c(400, 300, 800, 300);
			//sf::IntRect	m(0, 0, 512, 128);
			////sf::IntRect m = r;
			//sf::FloatRect	b = (*it)->getGlobalBounds();

			//if (b.top < 400.0f) { m.top = 400.0f - b.top;  }
			//else { m.top = 0.0f;  }
			//if (b.top + b.height > 600.0f) { m.height = b.top + b.height - 600.0f;  }
			//else { m.height = 128;  }
			//
			//if (b.top < c.top) { m.top = c.top - b.top + r.top; }
			//else m.top = 0;
			//if (b.top + b.height > c.top + c.height) { m.height = c.top + c.height - b.top; }
			//else m.height = 128 - m.top;

//			(*it)->setTextureRect(m);



		}
	}
}

void GameMenu::setFocused(int const & index)
{
	_focused = (index < 0 || index >= static_cast<int>(_items.size())) ? nullptr : _items[index];
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



void GameMenu::applyInLineStyle()
{

	sf::Vector2f	center(requestGameEngine.getWindow().getSize().x / 2.0f, requestGameEngine.getWindow().getSize().y / 2.0f);
	sf::Vector2f	totalSize = getTotalSize();
	sf::Vector2f  nextElemPosition(center.x - totalSize.x / 2, center.y - totalSize.y / 2);

	for (auto it = _items.begin(); it != _items.end(); it++)
	{
		if ((*it)->applyStyle() == true) {

			(*it)->setPosition(sf::Vector2f(nextElemPosition.x + (*it)->getGlobalBounds().width / 2, center.y));
			nextElemPosition.x += (*it)->getLocalBounds().width;
		}
	}
}

void GameMenu::applyInRoundStyle()
{
	sf::Vector2f	center(requestGameEngine.getWindow().getSize().x / 2.0f, requestGameEngine.getWindow().getSize().y / 2.0f);
	sf::Vector2f	totalSize = getTotalSize();
	sf::Vector2f  nextElemPosition(center.x, center.y /*- totalSize.y / 2*/);

	for (auto it = _items.begin(); it != _items.end(); it++) {

		if ((*it)->applyStyle() == true) {
				
			float ratio = 1.0f - ((std::abs(nextElemPosition.y - center.y) * 100 / center.y) / 100);
			(*it)->setPosition(nextElemPosition);
			float nextY = nextElemPosition.y + (*it)->getGlobalBounds().height;
			(*it)->setScale(ratio, ratio);
			(*it)->adjustScreenScale();
			(*it)->adjustScreenTextPosition(false);
			nextElemPosition.y = nextY;
		}
	}
}

void GameMenu::applyInLineBottomStyle()
{

	sf::Vector2f	center(requestGameEngine.getWindow().getSize().x / 2.0f, requestGameEngine.getWindow().getSize().y / 2.0f);
	sf::Vector2f	totalSize = getTotalSize();
	sf::Vector2f  nextElemPosition(center.x - totalSize.x / 2, center.y - totalSize.y / 2);

	for (auto it = _items.begin(); it != _items.end(); it++)
	{
		if ((*it)->applyStyle() == true) {

			(*it)->setPosition(sf::Vector2f(nextElemPosition.x + (*it)->getGlobalBounds().width / 2.0f, center.y / 3  * 5.0f));
			nextElemPosition.x += (*it)->getLocalBounds().width;
		}
	}
}

void GameMenu::applyInNarrowGridStyle()
{
	sf::Vector2f	center(requestGameEngine.getWindow().getSize().x / 2.0f, requestGameEngine.getWindow().getSize().y / 2.0f);
	int i = 0;
	sf::Vector2f	width(0.0f, 0.0f);
	if (_items.size() < 3)
		return;
	width.x = _items[0]->getGlobalBounds().width + _items[1]->getGlobalBounds().width + _items[2]->getGlobalBounds().width;
	width.y = width.x / 3.0f;

	sf::Vector2f  nextElemPosition(center.x - width.x / 2.0f, _cadre.top - _items.front()->getGlobalBounds().height / 2.0f);

	for (auto it = _items.begin(); it != _items.end(); it++)
	{
		if ((*it)->applyStyle() == true) {

			(*it)->setPosition(sf::Vector2f(nextElemPosition.x + (*it)->getGlobalBounds().width / 2.0f, _cadre.top + (i / 3) * (*it)->getGlobalBounds().height));
			nextElemPosition.x = ((i + 1) % 3 != 0 ? nextElemPosition.x + (*it)->getGlobalBounds().width : center.x - width.x / 2.0f);
			++i;
		}
	}
}



void                 GameMenu::applyStyle() {


	switch (_style)
	{
	case GameMenu::InLine:
		applyInLineStyle();
		break;
	case GameMenu::InLine_Bottom:
		applyInLineBottomStyle();
		break;
	case GameMenu::InNarrowGrid:
		applyInNarrowGridStyle();
		break;
	case GameMenu::InRound:
		applyInRoundStyle();
		break;
	default:
		break;
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
