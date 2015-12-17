#ifndef             ___AMMUNITION_FACTORY_HH___
# define            ___AMMUNITION_FACTORY_HH___

# include           "Ammunition.hh"

struct		fxPrams {
	std::string animationName;
	std::string ressourceName;
	std::string effectName;
	sf::Color    colorMask;
};

class               AmmoFactory
{
public:

	struct s_ammunitionParams {

		std::string             textureFilename;
		std::string             animationName;
		unsigned int         ammoSpeed;
		int						damage;			/*negative damages correspond to healing*/
		sf::Color			     colorMask;
		sf::Vector2f			scale;
//		struct FXFactory::FXParams fx;
		struct fxPrams		fx;
	};

public:

	AmmoFactory(std::string const& configurationFileName = "");
	~AmmoFactory();

public:

	bool                      loadAmmoConfigFromFile();

public:

	void                      setConfigurationFile(std::string const& filename);
	std::string               getConfigurationFile() const;

public:

	Ammunition*               createAmmo(std::string const& ammunitionName, Ammunition::eTargets const& ammoType = Ammunition::NeutralShot);

private:

	std::string                                         _configurationFile;
	std::map< std::string, struct s_ammunitionParams >  _ammoConfigs;

};

#endif              /* !___AMMUNITION_FACTORY_HH___ */
