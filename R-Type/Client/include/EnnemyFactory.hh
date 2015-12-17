#ifndef                 ___ENNEMY_FACTORY_HH___
# define                ___ENNEMY_FACTORY_HH___

# include               "Ennemy.hh"
# include				  "AmmoFactory.hh"

class                   EnnemyFactory
{

public:

	struct    s_ennemyParams {

		std::string           textureFilename;
		std::string           animationName;
		std::string           ammunitionName;
		sf::Color             colorMask;
		std::vector< sf::Vector2f>  shotOriginVertices;
		// std::string  const          deathEffectName;
		struct fxPrams		fx;
	};

public:

	EnnemyFactory(std::string const& configurationFileName = "");
	~EnnemyFactory();

public:

	bool                  loadEnnemyConfigFromFile();

public:

	void                  setConfigurationFile(std::string const& configurationFileName);
	std::string           getConfigurationFile() const;

public:

	Ennemy*               createEnnemy(std::string const& ennemyName, sf::Vector2f const& ennemyPosition = sf::Vector2f(0.0f, 0.0f), bool const& relativePosition = false);

private:

	std::string           _configurationFile;

	std::map< std::string, struct s_ennemyParams >  _ennemyConfigs;

};

#endif                  /* !___ENNEMY_FACTORY_HH___ */
