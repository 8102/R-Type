#ifndef												___ANIMATION_FACTORY_HH___
# define											___ANIMATION_FACTORY_HH___

#include											"Animation.hh"
#include											"Client_graphicUtils.hh"

class													AnimationFactory
{

	struct					AnimationParam {
		
		std::string		animationName;
		sf::Vector2i		frameGrid;
		sf::Vector2i		frameDimensions;
		sf::Vector2i		originOffset;
		unsigned int	frameLifetime;
	};

public:
	AnimationFactory(std::string const& filename ="");
	~AnimationFactory();

public:

	void												loadAnimation();
	std::unique_ptr<Animation>		createAnimation(struct AnimationParam p);
	Animation*									getAnimation(std::string const& name);

private:

	std::string																	_file;
	std::map<std::string,	
					std::pair<struct AnimationParam, std::unique_ptr<Animation>>>	_configs;
};

#endif											 /* !___ANIMATION_FACTORY_HH___ */