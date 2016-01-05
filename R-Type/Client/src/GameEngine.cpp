#include                "GameEngine.hh"
#include                "Player.hpp"
#include				  			"FX.hh"
#include					"GUI.hh"
GameEngine&             GameEngine::instanciate() {

	static GameEngine     instance;

	return instance;
}

GameEngine::GameEngine()
	: _isRunning(false), _isPaused(true), _win(nullptr), _collisionChecker(), _clock(), _controlerIndex(AGameController::MainMenu), _player(nullptr),
	_network(), _mode(GameEngine::offline)
{

}

GameEngine::~GameEngine() {

	clear();
}

void GameEngine::clear()
{
	_ammos.clear();
	_bonus.clear();
	_bonusF.clear();
	_collisionChecker.clear();
	_ennemies.clear();
	_gameObjects.clear();
	_gameControllers.clear();
	_players.clear();
	requestAssetManager.clear();
}

void                    GameEngine::start() {

	_isRunning = true;
	_win = make_unique< sf::RenderWindow >(sf::VideoMode(WIN_W, WIN_H), WINDOW_TITLE/*, sf::Style::None*/);
	_win->setFramerateLimit(WINDOW_FRAME_LIMIT);
	_ammoF.loadAmmoConfigFromFile();
	_playF.loadConfigs();
	_bonusF.loadConfig();
	
	for (int i = 1; i < 5; i++)
	{
		_players.push_back(make_unique<Player>(_playF.getPlayer(i)));
		_players.back().get()->setPosition(sf::Vector2f(400.0f, i * 100.0f));
	}
}

void							GameEngine::run() {

	GameRythmer		rythmer(*this, "C:\\Users\\Jamais\\Documents\\GitHubVisualStudio\\R-Type\\R-Type\\Client\\x64\\Release\\configuration.txt");

	if (!rythmer.start())
		std::cout << "Error opening file" << std::endl;
	rythmer.getNextActionBlock();
	_clock.start();

	while (isRunning() == true) {

		rythmer.update();
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

void GameEngine::launchGame()
{
	if (_mode == GameEngine::online)
		initPlayed();
	_GUI = make_unique< GUI >(*_player, *_win.get());
}

void GameEngine::pause()
{
	_clock.pause();
	_isPaused = true;
}

void GameEngine::resume()
{
	_isPaused = false;
	_clock.start();
}

void                    GameEngine::stop() {

	_isRunning = false;
}

void                    GameEngine::exit() {

	stop();
	_win.get()->close();
}

void GameEngine::updateDecors()
{

	for (auto it = _gameObjects.begin(); it < _gameObjects.end(); /* (void) */) {
		(*it)->update();
		if ((*it)->hasPassed() == true) {
			it = _gameObjects.erase(it); std::cout << "Erasing Decor ! " << std::endl; }
		else ++it;
	}

}

void GameEngine::updateBonus()
{

	for (auto it = _bonus.begin(); it < _bonus.end(); /* (void) */) {

		(*it)->move(sf::Vector2f(-0.3f, 0.0f));
		(*it)->update();
		for (auto playerIt = _players.begin(); playerIt < _players.end(); playerIt++) {
			
			if ((*playerIt)->isPlayed() && (*playerIt)->collide(*(*it), false) == true) {
				(*it)->trigger(*(*playerIt));
				it = _bonus.erase(it);
				goto end_of_main_loop;
			}
		}
		if ((*it)->hasPassed() == true)
			it = _bonus.erase(it);
		else ++it;
		end_of_main_loop: {}
	}
}

void GameEngine::updateAmmos()
{

	for (auto it = _ammos.begin(); it != _ammos.end(); /* (void) */) {
		(*it)->update();
		if ((*it)->isOutOfScreen() == true) goto delete_and_next;
		else if ((*it)->getType() == Ammunition::EnnemyShot) {
			for (auto playerIt = _players.begin(); playerIt != _players.end(); playerIt++) {
				if ((*playerIt)->isPlayed() == true && (*(*playerIt)).collide(*(*it), true) == true) {
					(*playerIt)->receiveDamage((*(*it)));
					(*it)->trigger();
					goto delete_and_next;
				}
			}
		}
		else if ((*it)->getType() == Ammunition::friendlyShot) {
			for (auto ennemyIt = _ennemies.begin(); ennemyIt != _ennemies.end(); ennemyIt++) {
				if ((*it)->collide(*(*ennemyIt)) == true) {
					getGUI().updateScore(5);
					if ((*it)->dealDamage(*(*ennemyIt)) == true)
						getGUI().updateScore(30);
					(*it)->trigger();
					goto delete_and_next;
				}
			}
		}

		++it;
		goto end_of_for_loop;
		delete_and_next: { it = _ammos.erase(it); }
		end_of_for_loop: {}
	}
}

void GameEngine::updateFXs()
{

	for (auto it = _FX.begin(); it != _FX.end(); /* (void) */)
	{
		(*it)->update();
		if ((*it)->getState() == Animation::end)
			it = _FX.erase(it);
		else ++it;
	}
}

void GameEngine::updateEnnemies()
{

	for (auto it = _ennemies.begin(); it != _ennemies.end(); /* (void) */) {
		(*it)->move(-0.5); /* to be replaced by server updates */
		(*it)->update();
		for (auto playerIt = _players.begin(); playerIt != _players.end(); playerIt++)
		{
			if ((*playerIt)->isPlayed() == true && (*it)->collide(*(*playerIt)))
				(*playerIt)->setLife(sf::Vector2i(0, (*playerIt)->getLife().y));
		}
		if ((*it)->hasPassed() == true || (*it)->getLife().x <= 0) /* order to die from server */ {
			(*it)->die();
			it = _ennemies.erase(it);
		}
		else ++it;
	}
}

void GameEngine::updatePlayers()
{
	for (auto it = _players.begin(); it != _players.end(); it++)
		(*it)->update();
}

void                    GameEngine::update() {

	updateDecors();
	updateBonus();
	updateAmmos();
	updateFXs();
	updateEnnemies();
	updatePlayers();
	getGUI().update();
	requestAudioEngine.update();
}

void                    GameEngine::draw() {

	_win->clear();
	for (auto it = _gameObjects.begin(); it != _gameObjects.end(); it++)
		_win->draw(*(*it));
	for (auto it = _ennemies.begin(); it != _ennemies.end(); it++)
	{
		_win->draw(*(*it));
		getGUI().drawEnnemyInfo(*(*it));
	}
	for (auto it = _bonus.begin(); it != _bonus.end(); it++)
		_win->draw(*(*it));
	for (auto it = _ammos.begin(); it != _ammos.end(); it++)
		_win->draw(*(*it));

	for (auto it = _players.begin(); it != _players.end(); it++)
	{
		if ((*it)->isPlayed() == true)
		{
			(*it)->getDrawn(*_win);
			if ((*it).get() != _player)
				getGUI().drawPlayerInfo(*(*it).get());
		}
	}
	for (auto it = _FX.begin(); it != _FX.end(); it++)
		_win->draw(*(*it));

	_player->indicateCurrentPlayer(*_win.get());
	getGUI().drawUserInfo();
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

bool GameEngine::isReady() const
{
	if (_player == nullptr)
		return false;
	return _player->isPlayed();
}

void                    GameEngine::addAnimation(Animation* animation) {

	_animations[animation->getAnimationName()] = make_unique< Animation >(*animation);
}

void                    GameEngine::addAmmo(Ammunition *amo) {

	_ammos.push_back(make_unique< Ammunition >(*amo));
}

void						GameEngine::addFX(std::string const& animationName, std::string const& ressourceName, sf::Vector2f const& position, sf::Color const& colormask)
{
	_FX.push_back(make_unique<AnimatedSprite>(*requestAssetManager.getTexture(ressourceName), getAnimation(animationName), colormask));
	_FX.back()->setPosition(position);
}

void                    GameEngine::addEnnemy(Ennemy *ennemy) {

	_ennemies.push_back(make_unique< Ennemy >(*ennemy));
}

void GameEngine::addBonus(Bonus const & b)
{
	_bonus.push_back(make_unique< Bonus >(b));
}

void GameEngine::setPlayer(int const & index)
{
	if (index < 1 || index > _players.size())
		return;
	if (_player != nullptr)
		_player->isPlayed(false);
	_player = _players[index - 1].get();
	_player->isPlayed(true);
}

void GameEngine::initPlayed()
{
	struct Client::GameInfos		gameInfo = requestNetwork.getCurrentGameInfos();

	for (auto it = gameInfo.playersInGame.begin(); it != gameInfo.playersInGame.end(); it++)
	{
		if (*it > 0 && *it < 5)
			_players[*it - 1]->isPlayed(true);
	}
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

void GameEngine::startClock()
{
	_clock.restart();
}

float GameEngine::getTime()
{
	return _clock.getElapsedTimeAsSeconds();
}


Player&                 GameEngine::getPlayer() {

	return *_player;
}

Player & GameEngine::getPlayer(int const & playerID)
{
	return *_players[playerID].get();
}

CollisionManager&       GameEngine::getCollisionManager() {

	return _collisionChecker;
}

GUI & GameEngine::getGUI()
{
	return	*_GUI.get();
}

AGameController * GameEngine::getController(AGameController::eController const & index)
{
	if (_gameControllers.find(index) == _gameControllers.end())
		return nullptr;
	return _gameControllers[index].get();
}
