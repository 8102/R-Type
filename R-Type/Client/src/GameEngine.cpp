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
	_animF.loadAnimation();
	_ammoF.loadAmmoConfigFromFile();
	_playF.loadConfigs();
	//_ennemyF.loadEnnemyConfigFromFile();
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
			it = _ammos.erase(it);
			deleted = true;
		}
		else {
			if ((*it)->Ammunition::getType() == Ammunition::EnnemyShot)
			{
				if ((*it)->collide(getPlayer()) == true && deleted == false) {
					FX	 fx("explosion", "r-typesheet44.gif", "");
					sf::IntRect ir((*it)->getGlobalBounds());
					sf::Vector2f p(ir.left + ir.width / 2 - getAnimation("explosion").getFrameDimensions().x / 2, ir.top + ir.height / 2 - getAnimation("explosion").getFrameDimensions().y / 2);
					fx.trigger(p);
					it = _ammos.erase(it);
					deleted = true;
				}
			}
			else if ((*it)->Ammunition::getType() == Ammunition::friendlyShot) for (auto ennemyit = _ennemies.begin(); ennemyit != _ennemies.end(); ennemyit++)
			{
				if ((*it)->collide(*(*ennemyit)) == true && deleted == false) {
					FX	 fx("bigExplosion", "r-typesheet44.gif", "bigExplosion.wav");
					sf::IntRect ir((*it)->getGlobalBounds());
					sf::Vector2f p(ir.left + ir.width / 2 - getAnimation("bigExplosion").getFrameDimensions().x / 2, ir.top + ir.height / 2 - getAnimation("bigExplosion").getFrameDimensions().y / 2);
					fx.trigger(p);
					it = _ammos.erase(it);
					deleted = true;
				}
			}
			else if (deleted == false) for (auto objit = _gameObjects.begin(); objit != _gameObjects.end(); objit++)
			{
				if ((*it)->collide(*(*objit)) == true && deleted == false) {
					it = _ammos.erase(it);
					deleted = true;
				}
			}
		}
		if (deleted == false)
			it++;
	}

	for (auto it = _FX.begin(); it != _FX.end();)
	{
		(*it)->update();
		if ((*it)->getState() == Animation::end) {
			it = _FX.erase(it);
		}	else it++;
	}

	for (auto it = _ennemies.begin(); it != _ennemies.end(); ) {
		(*it)->move(-0.5);
		(*it)->update();
		if ((*it)->hasPassed() == true)
			it = _ennemies.erase(it);
		else ++it;
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

void                    GameEngine::addAmmo(Ammunition *amo) {

	_ammos.push_back(make_unique< Ammunition >(*amo));
}

void						GameEngine::addFX(std::string const& animationName, std::string const& ressourceName, sf::Vector2f const& position)
{
	_FX.push_back(make_unique<AnimatedSprite>(*requestAssetManager.getTexture(ressourceName), getAnimation(animationName), sf::Color::Black));
	_FX.back()->setPosition(position);
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

//return *_animFactory.getAnimation(animationName);

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
