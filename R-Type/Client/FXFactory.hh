#ifndef								___FX_FACTORY_HH___
# define							___FX_FACTORY_HH___

#include							"Client_graphicUtils.hh"
#include							"AnimatedSprite.hh"
#include							"FX.hh"

class FXFactory
{

	struct FXParams
	{
		std::string			animation;
		std::string			ressourceFile;
		std::string			soundEffect;
		sf::Color				colorMask;
	};

public:
	FXFactory(std::string const& filename = "");
	~FXFactory();

public:

	void							loadConfigFromFile();
	FX*							createEffect(std::string const& effectName);
	std::unique_ptr<FX>createInstance(std::string const& effectName);
private:

	std::string												_file;
	std::map<std::string, struct FXParams>	_configs;
};

#endif								/* !___FX_FACTORY_HH___*/