#ifndef            ___ANIMATION_HH___
# define           ___ANIMATION_HH___

// Class Animation :
//
//   Split by rectangles the necessary frames of a sprite animation on a spritesheet
//   Give also the frame lifetime of an animation
//    Each frame will stay _lifetime cycles before being automaticlly changed if update() is called each turn
//    update() will return true while the animation is not over yet nd false when the last frame will have expire;

# include           <map>
# include           <vector>
# include           <iostream>
# include           <SFML/Graphics.hpp>

class               Animation
{
public:

	//  Enum state : render the state of the current Animation :
	//  ::current if the current frame needs to run over
	//  ::needChange if it needs to call next frame
	//  ::end if the last frame has finished.
	enum state
	{
		current = 0,
		needChange,
		end,
		notInit
	};

public:

	Animation(std::string const& animationName,
		sf::Vector2i const& frameGrid = sf::Vector2i(1, 1),
		sf::Vector2i const& frameDimensions = sf::Vector2i(1, 1),
		sf::Vector2i const& originOffset = sf::Vector2i(0, 0),
		unsigned int frameLifetime = 10);

	Animation(Animation const& modelAnimation);
	~Animation();

public:

	Animation::state  update();
	void              reset();
	void              createFrames();

public:

	void              setIndex(unsigned int index);
	void              setFrameLifetime(unsigned int lifetime);

public:

	void              setAnimationName(std::string const& animationName);
	void              setFrameGrid(sf::Vector2i const& frameGrid);
	void              setFrameDimensions(sf::Vector2i const& frameDimensions);
	void              setOriginOffset(sf::Vector2i const& originOffset);

public:

	void              setFrameAt(unsigned int index, sf::IntRect const& frame);
	void              pushFrame(sf::IntRect const& frame);

public:

	unsigned int      getIndex() const;
	unsigned int      getFrameLifetime() const;

public:

	std::string       getAnimationName() const;
	sf::Vector2i      getFrameGrid() const;
	sf::Vector2i      getFrameDimensions() const;
	sf::Vector2i      getOriginOffset() const;

public:

	sf::IntRect       getFrame() const;
	sf::IntRect       getFrameAt(unsigned int index) const;
	sf::IntRect       getNextFrame() const;

public:

	std::vector<sf::IntRect> getFrameArray() const;

private:

	unsigned int      _index;
	unsigned int      _frameLifetime;
	unsigned int      _currentFrameLifetime;

private:

	std::string       _animationName;
	sf::Vector2i      _frameGrid;
	sf::Vector2i      _frameDimensions;
	sf::Vector2i      _originOffset;

private:

	std::vector<sf::IntRect>        _frames;

public:

	Animation&       operator+=(Animation const& nextAnimation);
	Animation&       operator=(Animation const& modelAnimation);
};

Animation         operator+(Animation const& left, Animation const& right);

#endif            /* !___ANIMATION_HH___ */
