#include      "GameMenu.hh"
#include      "GameEngine.hh"

void          initMainMenu() {

	AssetManager&     a = AssetManager::instanciate();

	//create main menu and its MenuElements | By default, Inline-block display style
	GameMenu*         menu = new GameMenu("Menu", GameMenu::InLine);
	MenuElement*      background = new MenuElement(*a.getTexture("MainMenu.jpg"));
//	MenuElement*      title = new MenuElement(*a.getTexture("title.png"), "", *a.getFont("freedom.ttf"));
	MenuElement*      button1 = new MenuElement(*a.getTexture("half.png"), "solo", *a.getFont("freedom.ttf"), Vf(300.0f, 100.0f));
	MenuElement*      button2 = new MenuElement(*a.getTexture("half.png"), "online", *a.getFont("freedom.ttf"), Vf(300.0f, 300.0f));
	MenuElement*      button3 = new MenuElement(*a.getTexture("half.png"), "settings", *a.getFont("freedom.ttf"), Vf(300.0f, 500.0f));
	MenuElement*      button4 = new MenuElement(*a.getTexture("half.png"), "Exit", *a.getFont("freedom.ttf"), Vf(300.0f, 700.0f));

	//link MenuElements to actions (if void, link to &MenuElement::defaultFunction)
	button1->setAction(sf::Event::MouseButtonPressed, &MenuElement::openSelectionMenu);
	button1->setAction(sf::Event::MouseMoved, &MenuElement::movingFunction);
	button2->setAction(sf::Event::MouseMoved, &MenuElement::movingFunction);
	button2->setAction(sf::Event::MouseButtonPressed, &MenuElement::openConnectionMenu);
	button3->setAction(sf::Event::MouseMoved, &MenuElement::movingFunction);
	button3->setAction(sf::Event::MouseButtonPressed, &MenuElement::openOptionMenu);
	button4->setAction(sf::Event::MouseButtonPressed, &MenuElement::quitGame);
	button4->setAction(sf::Event::MouseMoved, &MenuElement::movingFunction);

	//set all elements to the menu
	menu->setBackground(background);
	menu->addItem(button1);
	 menu->addItem(button2);
	menu->addItem(button3);
	menu->addItem(button4);

	//force the menu style on all elements
	menu->applyStyle();
	//title->setPosition(sf::Vector2f(requestGameEngine.getWindow().getSize().x / 2 - title->getGlobalBounds().width / 2, 100.0f));
	//menu->addItem(title);


	// link main menu to the GameEngine as MainMenuController
	requestGameEngine.setController< GameMenu >(AGameController::MainMenu, menu);
}

void                 initOptionMenu() {

	AssetManager&      a = AssetManager::instanciate();

	GameMenu*          OptionMenu = new GameMenu("Options", GameMenu::InLine_Bottom);
	MenuElement*       optionMenuBackground = new MenuElement(*a.getTexture("desert_world.jpg"));
	MenuElement*       optionButton1 = new MenuElement(*a.getTexture("half.png"), "Audio", *a.getFont("freedom.ttf"), Vf(300.0f, 200.0f));
	MenuElement*       optionButton2 = new MenuElement(*a.getTexture("half.png"), "Video", *a.getFont("freedom.ttf"), Vf(300.0f, 400.0f));
	MenuElement*       optionButton3 = new MenuElement(*a.getTexture("half.png"), "Back", *a.getFont("freedom.ttf"), Vf(300.0f, 600.0f));

	optionButton1->setAction(sf::Event::MouseButtonPressed, &MenuElement::openAudioMenu);
	optionButton1->setAction(sf::Event::MouseMoved, &MenuElement::movingFunction);
	optionButton2->setAction(sf::Event::MouseButtonPressed, &MenuElement::defaultFunction);
	optionButton2->setAction(sf::Event::MouseMoved, &MenuElement::movingFunction);
	optionButton3->setAction(sf::Event::MouseMoved, &MenuElement::movingFunction);
	optionButton3->setAction(sf::Event::MouseButtonPressed, &MenuElement::openMainMenu);
	OptionMenu->setBackground(optionMenuBackground);
	OptionMenu->addItem(optionButton1);
	OptionMenu->addItem(optionButton2);
	OptionMenu->addItem(optionButton3);

	OptionMenu->applyStyle();

	requestGameEngine.setController< GameMenu >(AGameController::OptionMenu, OptionMenu);
}

void                  initConnectionMenu() {

	AssetManager&       a = requestAssetManager;

	GameMenu*           connectionMenu = new GameMenu("Connection", GameMenu::InBlock);
	MenuElement*        connectionMenuBackground = new MenuElement(*a.getTexture("spaceShipTravel.jpg"));
	MenuElement*        connectionMenuInputField1 = new MenuElement(*a.getTexture("input.png"), "Server", *a.getFont("nullShock.ttf"));
	MenuElement*        connectionMenuInputField2 = new MenuElement(*a.getTexture("input.png"), "Login", *a.getFont("nullShock.ttf"));
	MenuElement*        connectionMenuServerText = new MenuElement(*a.getTexture("transparent.png"), "Enter Server Address", *a.getFont("freedom.ttf"));
	MenuElement*        connectionMenuLoginText = new MenuElement(*a.getTexture("transparent.png"), "Enter Login", *a.getFont("freedom.ttf"));
	MenuElement*        connectionButton1 = new MenuElement(*a.getTexture("half.png"), "Connect !", *a.getFont("freedom.ttf"));
	MenuElement*        connectionButton2 = new MenuElement(*a.getTexture("half.png"), "Back", *a.getFont("freedom.ttf"));

	connectionMenu->setBackground(connectionMenuBackground);
	connectionButton1->setAction(sf::Event::MouseButtonPressed, &MenuElement::openSelectionMenu);
	connectionButton1->setAction(sf::Event::MouseMoved, &MenuElement::startingFunction);
	connectionButton2->setAction(sf::Event::MouseButtonPressed, &MenuElement::openMainMenu);
	connectionButton2->setAction(sf::Event::MouseMoved, &MenuElement::movingFunction);
	connectionMenuInputField1->setAction(sf::Event::TextEntered, &MenuElement::getIPAddrInput);
	connectionMenuInputField2->setAction(sf::Event::TextEntered, &MenuElement::getLoginInput);
	connectionMenu->addItem(connectionMenuServerText);
	connectionMenu->addItem(connectionMenuInputField1);
	connectionMenu->addItem(connectionMenuLoginText);
	connectionMenu->addItem(connectionMenuInputField2);
	connectionMenu->addItem(connectionButton1);
	connectionMenu->addItem(connectionButton2);
	connectionMenu->applyStyle();

	requestGameEngine.setController< GameMenu >(AGameController::ConnectionMenu, connectionMenu);
}

void              initSettingsMenu() {

	AssetManager&   a = requestAssetManager;

	GameMenu*       audioMenu = new GameMenu("audio", GameMenu::InBlock_straight);
	MenuElement*    audioBackground = new MenuElement(*a.getTexture("blackhole.jpg"));
	MenuElement*    audioButton1 = new MenuElement(*a.getTexture("fullGlowGauge.png"), "", *a.getFont("nullShock.ttf"), Vf(0, 0), sf::Color::Black);
	MenuElement*    audioButton2 = new MenuElement(*a.getTexture("fullGlowGauge.png"), "", *a.getFont("nullShock.ttf"), Vf(0, 0), sf::Color::Black);
	MenuElement*    audioButton3 = new MenuElement(*a.getTexture("fullGlowGauge.png"), "", *a.getFont("nullShock.ttf"), Vf(0, 0), sf::Color::Black);
	MenuElement*    audioButton4 = new MenuElement(*a.getTexture("half.png"), "Back", *a.getFont("freedom.ttf"));
	MenuElement*    mid1 = new MenuElement(*a.getTexture("emptyGlowGauge.png"), "", *a.getFont("freedom.ttf"));
	MenuElement*    mid2 = new MenuElement(*a.getTexture("emptyGlowGauge.png"), "", *a.getFont("freedom.ttf"));
	MenuElement*    mid3 = new MenuElement(*a.getTexture("emptyGlowGauge.png"), "", *a.getFont("freedom.ttf"));

	audioMenu->setBackground(audioBackground);
	audioButton1->setMidground(mid1);
	audioButton1->setAction(sf::Event::MouseMoved, &MenuElement::setEffectVolume);
	audioButton1->setAction(sf::Event::MouseButtonPressed, &MenuElement::toggleGauging);
	audioButton2->setMidground(mid2);
	audioButton2->setAction(sf::Event::MouseMoved, &MenuElement::setMusicVolume);
	audioButton2->setAction(sf::Event::MouseButtonPressed, &MenuElement::toggleGauging);
	audioButton3->setMidground(mid3);
	audioButton3->setAction(sf::Event::MouseMoved, &MenuElement::setMasterVolume);
	audioButton3->setAction(sf::Event::MouseButtonPressed, &MenuElement::toggleGauging);
	audioButton3->setAction(sf::Event::MouseButtonReleased, &MenuElement::untoggleGauging);
	audioButton4->setAction(sf::Event::MouseMoved, &MenuElement::movingFunction);
	audioButton4->setAction(sf::Event::MouseButtonPressed, &MenuElement::openOptionMenu);
	audioMenu->addItem(audioButton1);
	audioMenu->addItem(audioButton2);
	audioMenu->addItem(audioButton3);
	audioMenu->addItem(audioButton4);
	audioMenu->applyStyle();

	requestGameEngine.setController< GameMenu >(AGameController::AudioMenu, audioMenu);
}

void								initCharacterSelectionMenu() {

	AssetManager&		a = requestAssetManager;

	GameMenu*			selectionMenu = new GameMenu("Character Selection", GameMenu::InLine);
	MenuElement*		text = new MenuElement(*a.getTexture("transparent.png"), "choose your ship", *a.getFont("nullShock.ttf"));
	MenuElement*		playButton = new MenuElement(*a.getTexture("half.png"), "START", *a.getFont("nullShock.ttf"));
	MenuElement*		character1 = new MenuElement(*a.getTexture("player1Selector.png"), "", *a.getFont("nullShock.ttf"));
	MenuElement*		character2 = new MenuElement(*a.getTexture("player2Selector.png"), "", *a.getFont("nullShock.ttf"));
	MenuElement*		character3 = new MenuElement(*a.getTexture("player3Selector.png"), "", *a.getFont("nullShock.ttf"));
	MenuElement*		character4 = new MenuElement(*a.getTexture("player4Selector.png"), "", *a.getFont("nullShock.ttf"));

	playButton->setPosition(Vf(requestGameEngine.getWindow().getSize().x / 2 - playButton->getGlobalBounds().width / 2, 640));
	text->setPosition(Vf(requestGameEngine.getWindow().getSize().x / 2 - text->getGlobalBounds().width / 2, 150));
	selectionMenu->setBackground(new MenuElement(*a.getTexture("b9.png")));
	playButton->setOrigin(sf::Vector2f(playButton->getGlobalBounds().width / 2, playButton->getGlobalBounds().height / 2));
	playButton->setAction(sf::Event::MouseButtonPressed, &MenuElement::resumeGame);
	playButton->setAction(sf::Event::MouseMoved, &MenuElement::startingFunction);
	character1->setAction(sf::Event::MouseMoved, &MenuElement::defaultFunction);
	character1->setAction(sf::Event::MouseButtonPressed, &MenuElement::selectPlayer, 1);
	character2->setAction(sf::Event::MouseMoved, &MenuElement::defaultFunction);
	character2->setAction(sf::Event::MouseButtonPressed, &MenuElement::selectPlayer, 2);
	character3->setAction(sf::Event::MouseMoved, &MenuElement::defaultFunction);
	character3->setAction(sf::Event::MouseButtonPressed, &MenuElement::selectPlayer, 3);
	character4->setAction(sf::Event::MouseMoved, &MenuElement::defaultFunction);
	character4->setAction(sf::Event::MouseButtonPressed, &MenuElement::selectPlayer, 4);

	selectionMenu->addItem(character1);
	selectionMenu->addItem(character2);
	selectionMenu->addItem(character3);
	selectionMenu->addItem(character4);

	selectionMenu->applyStyle();
	playButton->setPosition(sf::Vector2f(playButton->getPosition().x + playButton->getGlobalBounds().width / 2, playButton->getPosition().y + playButton->getGlobalBounds().height / 2));
	selectionMenu->addItem(text);
	selectionMenu->addItem(playButton);
	requestGameEngine.setController< GameMenu >(AGameController::CharacterSelectionMenu, selectionMenu);
}