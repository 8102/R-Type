#ifndef						___FX_HH___
# define					___FX_HH___

# include					"Client_graphicUtils.hh"
# include					"AnimatedSprite.hh"
# include					"AssetManager.hh"

class FX
{
public:

	FX(std::string const& animationName, std::string const& visualRessourceName, std::string const& soundEffectName = "", sf::Color const& colorMask = sf::Color::White);
	FX(FX const& model);

	~FX();

public:

	void						trigger(sf::Vector2f const& effectPosition);

public:

	std::string				getAnimationName() const;
	std::string				getRessourceName() const;
	std::string				getSoundEffectName() const;
	sf::Color				getColorMask() const;

public:

	void						setAnimationName(std::string const& name);
	void						setRessourceName(std::string const& name);
	void						setEffectName(std::string const& name);
	void						setColorMask(sf::Color const& mask);

private:

	std::string			_animationName;
	std::string			_visualRessourceName;
	std::string			_soundEffectName;
	sf::Color			_colorMask;
//	std::shared_ptr<AnimatedSprite>		_visualEffect;
};

#endif						/* !___FX_HH___ */
