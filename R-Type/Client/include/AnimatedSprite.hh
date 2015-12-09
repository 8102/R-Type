#ifndef           ___ANIMATED_SPRITE_HH___
# define          ___ANIMATED_SPRITE_HH___

// Class AnimatedSprite :
//
//   Create an sprite and split it between multpiple Class Animations.
//   Must have at list one animation. If no animation are necessary, symply pass default animation (standing by)
//   Can choose animations by modifying its _animationIndex field
//   Can animate it by changing its _frame field by calling AnimatedSprite.nextFrame()
//


# include         <iostream>
# include         <sstream>
# include         <vector>
# include         <map>
# include         <SFML/Graphics.hpp>

# include         "Animation.hh"
# include         "AGameElement.hh"

class             AnimatedSprite : public AGameElement
{
public:

	AnimatedSprite(std::string const& filename, Animation const& animation, sf::Color const& colorMask = sf::Color::White);
	AnimatedSprite(sf::Image const& image, Animation const& animation, sf::Color const& colorMask = sf::Color::White);
	AnimatedSprite(sf::Texture const& texture, Animation const& animation, sf::Color const& colorMask = sf::Color::White);
	AnimatedSprite(AnimatedSprite const& model);
	~AnimatedSprite();

public:

	void             update();
	void             changeFrame();

	bool             loadFromFile();
	bool             loadFromImage();
	bool             loadFromTexture();

public:

	Animation&       getCurrentAnimation();
	int              findAnimationIndex(std::string const& animationName) const;

public:

	void             addAnimation(Animation const& animation);
	void             removeAnimation(std::string const& animationName);

	void             setCurrentAnimation(unsigned int index);
	void             setCurrentAnimation(std::string const& animationName);
	void             setFilename(std::string const& filename);

	std::vector<Animation> getAnimations() const;

public:

	unsigned int      getIndex() const;
	Animation::state  getState() const;

	sf::Color        getColorMask() const;
	std::string      getFilename() const;

public:

	AnimatedSprite&  operator=(AnimatedSprite const& model);

protected:

	unsigned int    _index;
	sf::Color       _colorMask;

protected:

	std::string     _filename;
	sf::Texture     _texture;
	sf::Image       _image;

protected:

	Animation::state    _animationState;

protected:

	std::vector<Animation>             _animations;
};

#endif            /* !___ANIMATED_SPRITE_HH___ */
