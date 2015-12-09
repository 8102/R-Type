#include          "AnimatedSprite.hh"
#include          "AssetManager.hh"
//#include          "UnitTest.hh"

AnimatedSprite::AnimatedSprite(std::string const& filename, Animation const& animation, sf::Color const& colorMask)
	: AGameElement(2), _index(0), _colorMask(colorMask), _filename(filename), _animationState(Animation::notInit)
{
	addAnimation(animation);
	loadFromFile();
}

AnimatedSprite::AnimatedSprite(sf::Image const& image, Animation const& animation, sf::Color const& colorMask)
	: AGameElement(2), _index(0), _colorMask(colorMask), _filename(""), _image(image), _animationState(Animation::notInit)
{
	addAnimation(animation);
	loadFromImage();
}

AnimatedSprite::AnimatedSprite(sf::Texture const& texture, Animation const& animation, sf::Color const& colorMask)
	: AGameElement(2), _index(0), _colorMask(colorMask), _filename(""), _texture(texture), _image(texture.copyToImage()), _animationState(Animation::notInit)
{
	addAnimation(animation);
	loadFromTexture();
}

AnimatedSprite::AnimatedSprite(AnimatedSprite const& model)
	: AGameElement(model), _index(model.getIndex()), _colorMask(model.getColorMask()), _filename(model.getFilename()), _animationState(model.getState())
{
	std::vector<Animation> const& v = model.getAnimations();

	for (auto it = v.begin(); it != v.end(); it++)
		_animations.push_back(Animation(*it));
}

AnimatedSprite::~AnimatedSprite() {}

void                            AnimatedSprite::update() {

	_animationState = getCurrentAnimation().update();
	if (_animationState != Animation::current)
		changeFrame();
}

void                            AnimatedSprite::changeFrame() {

	setTextureRect(getCurrentAnimation().getFrame());
}

bool                            AnimatedSprite::loadFromFile() {

	sf::Texture*                  tex;

	if ((tex = AssetManager::instanciate().getTexture(_filename)) == nullptr)
		return false;
	_image = tex->copyToImage();
	return loadFromImage();
}

bool                            AnimatedSprite::loadFromImage() {

	_image.createMaskFromColor(_colorMask);
	if (_texture.loadFromImage(_image) == false)
		return false;
	_texture.setSmooth(true);
	setTexture(_texture);
	setTextureRect(getCurrentAnimation().getFrame());
	return true;
}

bool                            AnimatedSprite::loadFromTexture() {

	_image = _texture.copyToImage();
	_image.createMaskFromColor(_colorMask);
	return loadFromImage();
}

Animation&                      AnimatedSprite::getCurrentAnimation() {

	return _animations[_index % _animations.size()];
}

int                             AnimatedSprite::findAnimationIndex(std::string const& animationName) const {

	int                    targetIndex = -1;

	for (auto it = _animations.begin(); it != _animations.end(); it++)
	{
		if (it->getAnimationName() == animationName)
			break;
		++targetIndex;
	}
	return targetIndex;
}

void                            AnimatedSprite::addAnimation(Animation const& animation) {
	_animations.push_back(animation);
}

void                            AnimatedSprite::removeAnimation(std::string const& animationName) {

	for (auto it = _animations.begin(); it < _animations.end(); it++)
		if (it->getAnimationName() == animationName) {
			_animations.erase(it);
			break;
		}
}

void                            AnimatedSprite::setCurrentAnimation(unsigned int index) {
	_index = (index % _animations.size());
}

void                            AnimatedSprite::setCurrentAnimation(std::string const& animationName) {

	int                           newIndex;

	if ((newIndex = findAnimationIndex(animationName)) >= 0)
		_index = (newIndex % _animations.size());
}



unsigned int                    AnimatedSprite::getIndex() const {

	return _index;
}

Animation::state                AnimatedSprite::getState() const {

	return _animationState;
}

sf::Color                       AnimatedSprite::getColorMask() const {

	return _colorMask;
}

std::string                     AnimatedSprite::getFilename() const {

	return _filename;
}

std::vector<Animation>         AnimatedSprite::getAnimations() const {

	return _animations;
}

void                           AnimatedSprite::setFilename(std::string const& filename) {

	_filename = filename;
}

AnimatedSprite&                AnimatedSprite::operator=(AnimatedSprite const& model) {

	if (this == &model)
		return *this;
	AGameElement::operator=(model);
	_filename = model.getFilename();
	_animationState = model.getState();
	std::vector<Animation> const& v = model.getAnimations();

	for (auto it = v.begin(); it != v.end(); it++)
		_animations.push_back(Animation(*it));
	setCurrentAnimation(model.getIndex());
	return *this;
}
