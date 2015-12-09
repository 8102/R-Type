#include          "AGameController.hh"

AGameController::AGameController() : IInteractive() {

}

AGameController::~AGameController() {

}

bool                          AGameController::handleEvent(sf::Event const& event) {

	switch (event.type) {

	case sf::Event::MouseMoved:
		return onMouseOver(event);

	case sf::Event::MouseButtonPressed:
		return onMouseClick(event);

	case sf::Event::MouseButtonReleased:
		return onMouseClickReleased(event);

	case sf::Event::KeyPressed:
		return onKeyPressed(event);

	case sf::Event::Closed:
		return onClose(event);

	case sf::Event::TextEntered:
		return onText(event);

	default:
		break;
	}
	return false;
}

bool                        AGameController::handleKeysDown() {

	return false;
}
