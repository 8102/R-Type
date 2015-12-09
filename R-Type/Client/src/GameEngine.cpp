#include                "GameEngine.hh"
#include                "Player.hpp"
#include				  "FX.hh"

GameEngine&             GameEngine::instanciate() {

	static GameEngine     instance;

	return instance;
}

GameEngine::GameEngine()
	: _isRunning(false), _isPaused(true), _win(nullptr), _controlerIndex(AGameController::MainMenu), _player(nullptr) {

}

GameEngine::~GameEngine() {
}

void                    GameEngine::start() {

	_isRunning = true;
	_win = make_unique< sf::RenderWindow >(sf::VideoMode(WIN_W, WIN_H), WINDOW_TITLE, sf::Style::None);
	_win->setFramerateLimit(WINDOW_FRAME_LIMIT);
	sf::Image		winIcon;
	if (winIcon.loadFromFile(std::string(ICON_FOLDER) + std::string("gameIcon.gif")) == true)
	_win->setIcon(150, 150, winIcon.getPixelsPtr());
}

void                    GameEngine::run() {

	while (isRunning() == true) {

		_win->clear();

		while (_win->pollEvent(_eventCatcher)) {
			_gameControllers[_controlerIndex]->handleEvent(_eventCatcher);
		}
		if (_controlerIndex == AGameController::GameControls)
			_gameControllers[_controlerIndex]->handleKeysDown();
		if (isPaused() == false) {
			update();
			draw();
		}
		else
			_gameControllers[_controlerIndex]->draw();

		_win->display();
	}
	exit();
}

void                    GameEngine::stop() {

	_isRunning = false;
}

void                    GameEngine::exit() {

	stop();
	_win.get()->close();
}

void                    GameEngine::update() {

	for (auto it = _gameObjects.begin(); it != _gameObjects.end(); it++) {
		(*it)->update();
		if ((*it)->hasPassed() == true) {
			(*it)->setPosition(PLAY_WIDTH * (rand() % 3 + 1), (*it)->getPosition().y); 
		}
	}
	for (auto it = _ammos.begin(); it != _ammos.end();) {

		bool deleted = false;

		(*it)->update();
		if ((*it)->isOutOfScreen() == true) {
			//delete *it;
			it = _ammos.erase(it);
			deleted = true;
		}
		else {
			if ((*it)->Ammunition::getType() == Ammunition::EnnemyShot)
			{
				if ((*it)->collide(getPlayer()) == true && deleted == false) {
					 AnimatedSprite*  fx = new AnimatedSprite(*requestAssetManager.getTexture("r-typesheet44.gif"), getAnimation("explosion"), sf::Color::Black);
					 addFX(fx, (*it)->getPosition());
					//          delete *it;
					it = _ammos.erase(it);
					deleted = true;
				}
			}
			else if ((*it)->Ammunition::getType() == Ammunition::friendlyShot) for (auto ennemyit = _ennemies.begin(); ennemyit != _ennemies.end(); ennemyit++)
			{
				if ((*it)->collide(*(*ennemyit)) == true && deleted == false) {
//					FX				specialEffect("bigExplosion", "r-typesheet44.gif", "bigExplosion.wav");
//					AnimatedSprite*  fx = new AnimatedSprite(*requestAssetManager.getTexture(specialEffect.getRessourceName()), getAnimation("bigExplosion"), sf::Color::Black);
//					 requestAudioEngine.playEffect("bigExplosion.wav");
					//requestAudioEngine.pushEffect("bigExplosion.wav");
					// addFX(fx, (*it)->getPosition());
//					addFX(fx, *(*it));

//					specialEffect.trigger((*it)->getPosition());
					//              delete *it;
					it = _ammos.erase(it);
					deleted = true;
				}
			}
			else if (deleted == false) for (auto objit = _gameObjects.begin(); objit != _gameObjects.end(); objit++)
			{
				if ((*it)->collide(*(*objit)) == true && deleted == false) {
					//AnimatedSprite*  fx = new AnimatedSprite(*requestAssetManager.getTexture("r-typesheet44.gif"), getAnimation("explosion"), sf::Color::Black);
					//addFX(fx, (*it)->getPosition());
					//            delete *it;
					it = _ammos.erase(it);
					deleted = true;
				}
			}
		}
		if (deleted == false)
			it++;
	}

	for (auto it = _FX.begin(); it != _FX.end(); /*it++*/)
	{
		(*it)->update();
		if ((*it)->getState() == Animation::end) {
			it = _FX.erase(it);
		}
		else it++;
	}

	for (auto it = _ennemies.begin(); it != _ennemies.end(); it++) {
		(*it)->move(-0.5);
		(*it)->update();
		if ((*it)->hasPassed() == true)
			((*it)->setPosition(PLAY_WIDTH, (*it)->getPosition().y));
	}
	_player->update();
	requestAudioEngine.update();
}

void                    GameEngine::draw() {

	_win->clear();
	for (auto it = _gameObjects.begin(); it != _gameObjects.end(); it++)
		_win->draw(*(*it));
	for (auto it = _ennemies.begin(); it != _ennemies.end(); it++)
		_win->draw(*(*it));
	for (auto it = _ammos.begin(); it != _ammos.end(); it++)
		_win->draw(*(*it));
	for (auto it = _FX.begin(); it != _FX.end(); it++)
		_win->draw(*(*it));
	_win->draw(*_player);
}

void                    GameEngine::draw(sf::Drawable const& target) {

	_win->draw(target);
}

bool                    GameEngine::isRunning() const {

	return _isRunning;
}

bool                    GameEngine::isPaused() const {

	return _isPaused;
}

void                    GameEngine::pause(bool pauseFlag) {

	_isPaused = pauseFlag;
}

void                    GameEngine::addAnimation(Animation* animation) {

	_animations[animation->getAnimationName()] = make_unique< Animation >(*animation);
}

// template< class T >
// void                    GameEngine::addGameObject(T* gameObject) {
//
//   _gameObjects.push_back( make_unique< T >(gameObject));
// }

void                    GameEngine::addAmmo(Ammunition *amo) {

	_ammos.push_back(make_unique< Ammunition >(*amo));
}

void                    GameEngine::addFX(AnimatedSprite* FX, sf::Vector2f const& position) {

	FX->setPosition(position - Vf(FX->getGlobalBounds().width / 2, FX->getGlobalBounds().height / 2));
	_FX.push_back(make_unique< AnimatedSprite >(*FX));
}

void                    GameEngine::addFX(AnimatedSprite* FX, Ammunition const& ammo) {

	sf::Vector2f          reajust = sf::Vector2f(/*ammo.getMovement().x + */FX->getGlobalBounds().width, ammo.getMovement().y - FX->getGlobalBounds().height / 2);

	FX->setPosition(ammo.getPosition() + reajust);
	_FX.push_back(make_unique< AnimatedSprite >(*FX));
}

void                    GameEngine::addEnnemy(Ennemy *ennemy) {

	_ennemies.push_back(make_unique< Ennemy >(*ennemy));
}

void                    GameEngine::setPlayer(Player *player) {

	_player = make_unique< Player >((*player));
}

void                    GameEngine::setControllerIndex(AGameController::eController const& index) {

	_controlerIndex = index;
}

Animation&              GameEngine::getAnimation(std::string const& animationName) {

	return *_animations[animationName];
}

AGameElement&           GameEngine::getGameObject(unsigned int index) {

	return *_gameObjects[index];
}

sf::RenderWindow&       GameEngine::getWindow() const {

	return *_win.get();
}

Player&                 GameEngine::getPlayer() {

	return *_player;
}

CollisionManager&       GameEngine::getCollisionManager() {

	return _collisionChecker;
}
