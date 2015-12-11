#include            "GameDecor.hh"
#include            "GameEngine.hh"

GameDecor::GameDecor(std::string const& filename, unsigned int Zindex, sf::Color const& colorMask, bool repeated)
	: AGameElement(Zindex)
{
	_image.loadFromFile(filename);
	_image.createMaskFromColor(colorMask);
	_texture.loadFromImage(_image);
	_texture.setRepeated(repeated);
	_texture.setSmooth(true);
	setTexture(_texture);
	_cadre = sf::IntRect(0, 0, _texture.getSize().x, _texture.getSize().y);
	_vector = sf::Vector2i(1, 1);
	setTextureRect(_cadre);
}

GameDecor::GameDecor(sf::Texture const& texture, unsigned int Zindex, bool repeated)
	: AGameElement(texture, Zindex) {
	_cadre = sf::IntRect(0, 0, _texture.getSize().x, _texture.getSize().y);
	_vector = sf::Vector2i(1, 1);
	setTextureRect(_cadre);
}

GameDecor::GameDecor(GameDecor const& model)
	: AGameElement(model),/* _image(model.getImage()),*/ _cadre(model.getCadre()), _vector(model.getVector1()), _movement(model.getVector2()) {

	// _texture.loadFromImage(_image);
	// _texture.setRepeated(model.sf::Sprite::getTexture()->isRepeated());
	// _texture.setSmooth(true);
	// setTexture(_texture);
	setTextureRect(_cadre);
}

GameDecor::~GameDecor() {}

void                  GameDecor::update() {
	_cadre.top += _vector.y;
	_cadre.left += _vector.x;
	_cadre.width += _vector.x;
	_cadre.height += _vector.y;
	setPosition(getPosition().x + _movement.x, getPosition().y + _movement.y);
	setTextureRect(_cadre);
}


void                  GameDecor::setImage(sf::Image const& image) {
	_image = image;
	_texture.loadFromImage(_image);
}

void                  GameDecor::setCadre(sf::IntRect const& cadre) {
	_cadre = cadre;
}


void                  GameDecor::setVectors(sf::Vector2i const& vector, sf::Vector2f const& move) {
	_vector = vector;
	_movement = move;
}

sf::Image             GameDecor::getImage() const {
	return _image;
}

sf::IntRect           GameDecor::getCadre() const {
	return _cadre;
}

sf::Vector2i          GameDecor::getVector1() const {
	return _vector;
}

sf::Vector2f          GameDecor::getVector2() const {
	return _movement;
}
