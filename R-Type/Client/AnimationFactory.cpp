#include "AnimationFactory.hh"
#include "Player.hpp"

AnimationFactory::AnimationFactory(std::string const & filename)
	: _file(filename)
{
	loadAnimation();
}

AnimationFactory::~AnimationFactory()
{
}

void AnimationFactory::loadAnimation()
{
	_configs["boss1"].first = { "boss1", Vi(1, 4), Vi(260, 145), Vi(0, 0), 50 };
	_configs["boss1"].second = createAnimation(_configs["boss1"].first);
	//	Animation         anim1{"boss1", Vi(1, 4), Vi(260, 145), Vi(0, 0), 50);
	_configs["loadingLaser"].first = { "loadingLaser", Vi(8, 1), Vi(32, 32), Vi(0, 48), 5 };
	_configs["loadingLaser"].second = createAnimation(_configs["loadingLaser"].first);
	_configs["explosion"].first = {"explosion", Vi(6, 1), Vi(32, 32), Vi(130, 0), 5};
	_configs["explosion"].second = createAnimation(_configs["explosion"].first);
	_configs["ship"].first = {"ship", Vi(1, 1), Vi(32, 17), Vi(0, 0), 100};
	_configs["ship"].second = createAnimation(_configs["ship"].first);
	_configs["void"].first = {"void", Vi(1, 1), Vi(1768, 140), Vi(168, 16), 800};
	_configs["void"].second = createAnimation(_configs["void"].first);
	_configs["mainmenu"].first = {"mainmenu", Vi(1, 1), Vi(1920, 1200), Vi(0, 0), 150654};
	_configs["mainmenu"].second = createAnimation(_configs["mainmenu"].first);
	_configs["bullet"].first = {"bullet", Vi(4, 1), Vi(17, 6), Vi(130, 0), 5};
	_configs["bullet"].second = createAnimation(_configs["bullet"].first);
	_configs["rocket"].first = {"rocket", Vi(1, 12), Vi(162, 35), Vi(00, 0), 1};
	_configs["rocket"].second = createAnimation(_configs["rocket"].first);
	_configs["spaceBomb"].first = {"spaceBomb", Vi(12, 1), Vi(17, 18), Vi(0, 0), 15};
	_configs["spaceBomb"].second = createAnimation(_configs["spaceBomb"].first);
	_configs["flyingSaucer"].first = {"flyingSaucer", Vi(1, 6), Vi(40, 30), Vi(0, 0), 5};
	_configs["flyingSaucer"].second = createAnimation(_configs["flyingSaucer"].first);
	_configs["bountyHunter"].first = {"bountyHunter", Vi(4, 1), Vi(64, 64), Vi(0, 0), 50};
	_configs["bountyHunter"].second = createAnimation(_configs["bountyHunter"].first);
	_configs["alienJet"].first = {"alienJet", Vi(5, 1), Vi(56, 47), Vi(0, 0), 10};
	_configs["alienJet"].second = createAnimation(_configs["alienJet"].first);
	_configs["ufo"].first = {"ufo", Vi(6, 2), Vi(56, 42), Vi(5, 0), 15};
	_configs["ufo"].second = createAnimation(_configs["ufo"].first);
	_configs["BossDeath"].first = {"BossDeath", Vi(4, 6), Vi(50, 50), Vi(0, 0)};
	_configs["BossDeath"].second = createAnimation(_configs["BossDeath"].first);
	_configs["spaceFighter"].first = { "spaceFighter", Vi(1, 1), Vi(150, 55), Vi(0, 0), 8000};
	_configs["spaceFighter"].second = createAnimation(_configs["spaceFighter"].first);
}

std::unique_ptr<Animation>				AnimationFactory::createAnimation(struct AnimationParam p) {

	return std::make_unique<Animation>(p.animationName, p.frameGrid, p.frameDimensions, p.originOffset, p.frameLifetime);
}

Animation*					AnimationFactory::getAnimation(std::string const & name)
{
	struct AnimationParam	p;

	if (_configs.find(name) == _configs.end())
		std::cerr << "error on animation";
	return _configs[name].second.get();
//	p = _configs[name].first;
//	return Animation(p.animationName, p.frameGrid, p.frameDimensions, p.originOffset, p.frameLifetime);
}
