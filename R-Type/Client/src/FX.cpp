#include "FX.hh"
#include "GameEngine.hh"


FX::FX(std::string const & animationName, std::string const & visualRessourceName, std::string const & soundEffectName)
	: _animationName(animationName), _visualRessourceName(visualRessourceName), _soundEffectName(soundEffectName)
{
}

FX::~FX()
{
}

void FX::trigger(sf::Vector2f const & effectPosition)
{
	if (_soundEffectName.size() > 0 && _soundEffectName != "NO_SOUND")
		requestAudioEngine.pushEffect(_soundEffectName);
	requestGameEngine.addFX(_animationName, _visualRessourceName, effectPosition);
}

std::string FX::getAnimationName() const
{
	return _animationName;
}

std::string FX::getRessourceName() const
{
	return _visualRessourceName;
}

std::string FX::getSoundEffectName() const
{
	return _soundEffectName;
}
