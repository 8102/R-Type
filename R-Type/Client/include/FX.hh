#ifndef						___FX_HH___
# define					___FX_HH___

# include					"Client_graphicUtils.hh"
# include					"AnimatedSprite.hh"
# include					"AssetManager.hh"

class FX
{
public:

	FX(std::string const& animationName, std::string const& visualRessourceName, std::string const& soundEffectName);
	~FX();

public:

	void						trigger(sf::Vector2f const& effectPosition);

public:

	std::string				getAnimationName() const;
	std::string				getRessourceName() const;
	std::string				getSoundEffectName() const;

private:

	std::string			_animationName;
	std::string			_visualRessourceName;
	std::string			_soundEffectName;

	std::shared_ptr<AnimatedSprite>		_visualEffect;
};

#endif						/* !___FX_HH___ */