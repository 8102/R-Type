#include "FX.hh"
#include "GameEngine.hh"


FX::FX(std::string const & animationName, std::string const & visualRessourceName, std::string const & soundEffectName, sf::Color const& colorMask)
	: _animationName(animationName), _visualRessourceName(visualRessourceName), _soundEffectName(soundEffectName), _colorMask(colorMask)
{
}

FX::FX(FX const & model)
	: _animationName(model.getAnimationName()), _visualRessourceName(model.getRessourceName()), _soundEffectName(model.getSoundEffectName()), _colorMask(model.getColorMask())
{
}


FX::~FX()
{
}

void FX::trigger(sf::Vector2f const & effectPosition)
{
	if (_soundEffectName.size() > 0 && _soundEffectName != "NO_SOUND")
		requestAudioEngine.pushEffect(_soundEffectName);
	if (_visualRessourceName.size() > 0 && _animationName.size() > 0)
	requestGameEngine.addFX(_animationName, _visualRessourceName, effectPosition, _colorMask);
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

sf::Color FX::getColorMask() const
{
	return _colorMask;
}

void FX::setAnimationName(std::string const & name)
{
	_animationName = name;
}

void FX::setRessourceName(std::string const & name)
{
	_visualRessourceName = name;
}

void FX::setEffectName(std::string const & name)
{
	_soundEffectName = name;
}

void FX::setColorMask(sf::Color const & mask)
{
	_colorMask = mask;
}
