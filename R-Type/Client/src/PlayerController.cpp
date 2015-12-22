#include      "PlayerController.hh"
#include      "GameEngine.hh"

PlayerController::PlayerController(Player& player) : AGameController(), _player(player) {

}

PlayerController::~PlayerController() {}

bool                                PlayerController::onMouseOver(_unused sf::Event const& event) {

	return false;
}

bool                                PlayerController::onMouseClick(_unused sf::Event const& event) {

	_player.shoot();
	return false;
}

bool                                PlayerController::onMouseClickReleased(_unused sf::Event const& event) {

	return false;
}

void                                PlayerController::openMainMenu() {

	GameEngine&                       engine = requestGameEngine;
	SoundSystem&                      audioEngine = requestAudioEngine;

	engine.pause(true);
	audioEngine.getCurrentMusic().pause();
	audioEngine.setCurrentMusic("menuMusic.wav");
	audioEngine.playMusic();
	engine.setControllerIndex(AGameController::MainMenu);
}

bool                                PlayerController::onKeyPressed(_unused sf::Event const& event) {

	switch (event.key.code) {

	case sf::Keyboard::Escape:
		// engine.pause(true);
		// engine.setControllerIndex(AGameController::MainMenu);
		openMainMenu();
		break;

	case sf::Keyboard::Space:
		_player.shoot();
		break;

	case sf::Keyboard::LShift:
		_player.switchWeapon();
		break;
		// case sf::Keyboard::Z :
		//   _player.move(0, -1);
		//   break;
		//
		// case sf::Keyboard::S :
		//   _player.move(0, 1);
		//   break;
		//
		// case sf::Keyboard::Q :
		//   _player.move(-1, 0);
		//   break;
		//
		// case sf::Keyboard::D :
		//   _player.move(1, 0);
		//   break;

	default:
		return false;
	}
	return true;
}

bool                                PlayerController::handleKeysDown() {

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
		_player.shoot();

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Z) || sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
		_player.move(0, -1);

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S) || sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
		_player.move(0, 1);

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q) || sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
		_player.move(-1, 0);

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) || sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
		_player.move(1, 0);

	return true;
}

bool                                PlayerController::onClose(_unused sf::Event const& event) {

	return false;
}

bool                                PlayerController::onText(_unused sf::Event const& event) {

	return false;
}
