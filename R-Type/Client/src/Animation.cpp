#include              "Animation.hh"

Animation::Animation(std::string const& animationName,
	sf::Vector2i const& frameGrid,
	sf::Vector2i const& frameDimensions,
	sf::Vector2i const& originOffset,
	unsigned int frameLifetime)
	: _index(0), _frameLifetime(frameLifetime), _currentFrameLifetime(frameLifetime),
	_animationName(animationName), _frameGrid(frameGrid), _frameDimensions(frameDimensions), _originOffset(originOffset)
{
	createFrames();
}

Animation::Animation(Animation const& modelAnimation)
	: _index(modelAnimation.getIndex()),
	_frameLifetime(modelAnimation.getFrameLifetime()),
	_currentFrameLifetime(modelAnimation.getFrameLifetime()),
	_animationName(modelAnimation.getAnimationName()),
	_frameGrid(modelAnimation.getFrameGrid()),
	_frameDimensions(modelAnimation.getFrameDimensions()),
	_originOffset(modelAnimation.getOriginOffset())
{
	std::vector<sf::IntRect> modelAnimationArray;

	_currentFrameLifetime = _frameLifetime;
	modelAnimationArray = modelAnimation.getFrameArray();
	for (auto it = modelAnimationArray.begin(); it < modelAnimationArray.end(); it++) {
		pushFrame(*it);
	}
}

Animation::~Animation() {}

//public

Animation::state      Animation::update() {

	if (_currentFrameLifetime <= 0)
	{
		setIndex((getIndex() + 1) % _frames.size());
		_currentFrameLifetime = _frameLifetime;
		if (_index == 0)
			return Animation::end;
		return Animation::needChange;
	}
	_currentFrameLifetime -= 1;
	return Animation::current;
}
void                  Animation::reset() {
	setIndex(0);
	_currentFrameLifetime = _frameLifetime;
}
void                  Animation::createFrames() {

	for (auto y = 0; y < _frameGrid.y; y++)
		for (auto x = 0; x < _frameGrid.x; x++)
			_frames.push_back(sf::IntRect(_originOffset.x + (x * _frameDimensions.x),
				_originOffset.y + (y * _frameDimensions.y),
				_frameDimensions.x,
				_frameDimensions.y
				)
				);
}
//public : __SETTERS
////////////////////
void                  Animation::setIndex(unsigned int index) {
	_index = index;
}
void                  Animation::setFrameLifetime(unsigned int lifetime) {
	_frameLifetime = lifetime;
}
//
void                  Animation::setAnimationName(std::string const& animationName) {
	_animationName = animationName;
}
void                  Animation::setFrameGrid(sf::Vector2i const& frameGrid) {
	_frameGrid = frameGrid;
}
void                  Animation::setFrameDimensions(sf::Vector2i const& frameDimensions) {
	_frameDimensions = frameDimensions;
}
void                  Animation::setOriginOffset(sf::Vector2i const& originOffset) {
	_originOffset = originOffset;
}
//
void                  Animation::setFrameAt(unsigned int index, sf::IntRect const& frame) {
	_frames.at(index) = frame;
}
void                  Animation::pushFrame(sf::IntRect const& frame) {
	_frames.push_back(frame);
}
// !__SETTERS
//____________________________________________________________________
//public : __GETTERS
////////////////////
unsigned int          Animation::getIndex() const {
	return _index;
}
unsigned int          Animation::getFrameLifetime() const {
	return _frameLifetime;
}
//
std::string           Animation::getAnimationName() const {
	return _animationName;
}
sf::Vector2i          Animation::getFrameGrid() const {
	return _frameGrid;
}
sf::Vector2i          Animation::getFrameDimensions() const {
	return _frameDimensions;
}
sf::Vector2i          Animation::getOriginOffset() const {
	return _originOffset;
}
//
sf::IntRect           Animation::getFrame() const {
	return _frames.at(_index);
}
sf::IntRect           Animation::getFrameAt(unsigned int index) const {
	return _frames.at(index);
}
sf::IntRect           Animation::getNextFrame() const {
	return _frames.at((_index + 1) % _frames.size());
}

std::vector<sf::IntRect>  Animation::getFrameArray() const {
	return _frames;
}
// !__GETTERS
//____________________________________________________________________
//public:
Animation&            Animation::operator+=(Animation const& nextAnimation) {

	std::vector<sf::IntRect> nextAnimationArray;

	reset();
	setAnimationName(getAnimationName() + std::string("+") + nextAnimation.getAnimationName());
	nextAnimationArray = nextAnimation.getFrameArray();
	for (auto it = nextAnimationArray.begin(); it < nextAnimationArray.end(); it++) {
		pushFrame(*it);
	}
	return *this;
}
Animation&            Animation::operator=(Animation const& modelAnimation) {

	std::vector<sf::IntRect> modelAnimationArray;

	if (this == &modelAnimation)
		return *this;
	setAnimationName(modelAnimation.getAnimationName());
	setIndex(modelAnimation.getIndex());
	setFrameLifetime(modelAnimation.getFrameLifetime());
	setFrameGrid(modelAnimation.getFrameGrid());
	setFrameDimensions(modelAnimation.getFrameDimensions());
	setOriginOffset(modelAnimation.getOriginOffset());
	_currentFrameLifetime = _frameLifetime;
	modelAnimationArray = modelAnimation.getFrameArray();
	for (auto it = modelAnimationArray.begin(); it < modelAnimationArray.end(); it++) {
		pushFrame(*it);
	}
	return *this;
}

Animation                    operator+(Animation const& left, Animation const& right)
{
	Animation                   result(left);

	result += right;
	return result;
}
