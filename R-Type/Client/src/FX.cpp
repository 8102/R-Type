#include "FX.hh"
#include "GameEngine.hh"


FX::FX(std::string const & animationName, std::string const & visualRessourceName, std::string const & soundEffectName)
	: _animationName(animationName), _visualRessourceName(visualRessourceName), _soundEffectName(soundEffectName)
{
}

FX::~FX()
{
}

#include "windows.h"
void FX::trigger(sf::Vector2f const & effectPosition)
{
	AnimatedSprite*	visualEffect = new AnimatedSprite(*requestAssetManager.getTexture(_visualRessourceName),
		requestGameEngine.getAnimation(_animationName),
		sf::Color::Black);
	//OutputDebugStringA(_animationName.c_str());
	//OutputDebugStringA("\n");
	//OutputDebugStringA(_visualRessourceName.c_str());
	//OutputDebugStringA("\n");
	visualEffect->setPosition(effectPosition);
	requestAudioEngine.pushEffect(_soundEffectName);
	requestGameEngine.addFX(visualEffect, effectPosition);
	delete visualEffect;
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
