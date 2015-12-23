#include                "AGameElement.hh"
#include                "GameEngine.hh"
#include								"FX.hh"

unsigned int counter = 0;

AGameElement::AGameElement(unsigned int zIndex) : sf::Sprite(), _zIndex(zIndex), _type(None) {
	++counter;
}

AGameElement::AGameElement(sf::Texture const& texture, unsigned int zIndex) : sf::Sprite(texture), _zIndex(zIndex), _type(None) {
	++counter;
}

AGameElement::AGameElement(AGameElement const& model)
	: sf::Sprite(model), _zIndex(model.getZIndex()), _type(None) {
	++counter;
}

AGameElement::~AGameElement() {
	--counter;
}

unsigned int              AGameElement::getZIndex() const {

	return _zIndex;
}

AGameElement::eType       AGameElement::getType() const {

	return _type;
}

void                      AGameElement::setZIndex(unsigned int zIndex) {

	_zIndex = zIndex;
}

void                      AGameElement::setType(AGameElement::eType const& type) {

	_type = type;
}

void                      AGameElement::applyFilter(sf::Color const& c) {

	sf::Image              img;
	sf::Texture            t;
	img = getTexture()->copyToImage();
	img.createMaskFromColor(c);
	if (t.loadFromImage(img))
		setTexture(t);
}

bool                      AGameElement::containsPoint(sf::Vector2i const& point) {

	if ((point.x >= getGlobalBounds().left) &&
		(point.y >= getGlobalBounds().top) &&
		(point.x <= (getGlobalBounds().left + getGlobalBounds().width)) &&
		(point.y <= (getGlobalBounds().top + getGlobalBounds().height)))
		return true;
	return false;
}

bool                      AGameElement::collide(/*_unused*/ AGameElement const& gameElement) const {

	return requestCollider.CheckCollision(*this, gameElement);
}

AGameElement&             AGameElement::operator=(AGameElement const& model) {

	if (this == &model)
		return *this;
	sf::Sprite::operator=(model);
	setZIndex(model.getZIndex());
	setType(model.getType());
	return *this;
}

bool                      AGameElement::isOutOfScreen() const {

	if (getPosition().x + getGlobalBounds().width < 0 ||
		getPosition().y + getGlobalBounds().height < 0 ||
		getPosition().x > requestGameEngine.getWindow().getSize().x ||
		getPosition().y > requestGameEngine.getWindow().getSize().y)
		return true;
	return false;
}

bool AGameElement::hasPassed() const
{
	if (getGlobalBounds().left + getGlobalBounds().width < 0)
		return true;
	return false;
}

AGameElement&             operator<(AGameElement& l, AGameElement& r) {

	return l.getZIndex() > r.getZIndex() ? r : l;
}
