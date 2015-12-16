#include "AnimationFactory.hh"





AnimationFactory::AnimationFactory(std::string const & filename)
	: _file(filename)
{
}

AnimationFactory::~AnimationFactory()
{
}

void AnimationFactory::loadAnimation()
{
	_configs["boss1"] = { "boss1", Vi(1, 4), Vi(260, 145), Vi(0, 0), 50 };
	//	Animation         anim1{"boss1", Vi(1, 4), Vi(260, 145), Vi(0, 0), 50);
	_configs["loadingLaser"] = { "loadingShot", Vi(8, 1), Vi(32, 32), Vi(0, 48), 5 };
	_configs["explosion"] = {"explosion", Vi(6, 1), Vi(32, 32), Vi(130, 0), 5};
	_configs["ship"] = {"ship", Vi(1, 1), Vi(32, 17), Vi(0, 0), 100};
	_configs["void"] = {"void", Vi(1, 1), Vi(1768, 140), Vi(168, 16), 800};
	_configs["mainmenu"] = {"mainmenu", Vi(1, 1), Vi(1920, 1200), Vi(0, 0), 150654};
	_configs["bullet"] = { "bullet", Vi(4, 1), Vi(17, 6), Vi(130, 0), 5 };
	_configs["plasmaBullet"] = { "plasmaBullet", Vi(2, 1), Vi(16, 15), Vi(232, 100), 5 };
	_configs["rocket"] = {"rocket", Vi(1, 12), Vi(162, 35), Vi(00, 0), 1};
	_configs["spaceBomb"] = {"spaceBomb", Vi(12, 1), Vi(17, 18), Vi(0, 0), 15};
	_configs["flyingSaucer"] = {"flyingSaucer", Vi(1, 6), Vi(40, 30), Vi(0, 0), 5};
	_configs["bountyHunter"] = {"bountyHunter", Vi(4, 1), Vi(64, 64), Vi(0, 0), 50};
	_configs["alienJet"] = {"alienJet", Vi(5, 1), Vi(56, 47), Vi(0, 0), 10};
	_configs["ufo"] = {"ufo", Vi(6, 2), Vi(56, 42), Vi(5, 0), 15};
	_configs["BossDeath"] = {"BossDeath", Vi(4, 6), Vi(50, 50), Vi(0, 0)};

}

Animation					AnimationFactory::getAnimation(std::string const & name)
{
	struct AnimationParam	p;

	if (_configs.find(name) == _configs.end())
		std::cerr << "error on animation";
	p = _configs[name];
	return Animation(p.animationName, p.frameGrid, p.frameDimensions, p.originOffset, p.frameLifetime);
}
