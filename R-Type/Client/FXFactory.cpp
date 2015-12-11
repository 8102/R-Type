#include "FXFactory.hh"
#include "Player.hpp"


FXFactory::FXFactory(std::string const & filename) 
	: _file(filename) {
}

FXFactory::~FXFactory()
{
}

void FXFactory::loadConfigFromFile()
{
	_configs["bigExplosion"] = {
		"bigExplosion",
		"r-typesheet44.gif",
		"bigExplosion.wav"
	};

}

FX * FXFactory::createEffect(std::string const & effectName)
{

	return nullptr;
}

std::unique_ptr<FX> FXFactory::createInstance(std::string const & effectName)
{
	//struct FXParams	  p;

	//if (_configs.find(effectName) == _configs.end()) {
	//	std::cout << "Bad" << std::endl;
	//	/* throw exception */
	//}
	//p = _configs[effectName];
	//return make_unique<FX>(p.animation, p.ressourceFile, p.soundEffect);
}
