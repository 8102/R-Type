#include      "GameMenu.hh"
#include      "GameEngine.hh"

void          initMainMenu() {

	AssetManager&     a = AssetManager::instanciate();

	//create main menu and its MenuElements | By default, Inline-block display style
	GameMenu*         menu = new GameMenu("Menu", GameMenu::InLine);
	MenuElement*      background = new MenuElement(*a.getTexture("MainMenu.jpg"));
//	MenuElement*      title = new MenuElement(*a.getTexture("title.png"), "", *a.getFont("freedom.ttf"));
	MenuElement*      button1 = new MenuElement(*a.getTexture("half.png"), "solo", *a.getFont("freedom.ttf"), nullptr, Vf(300.0f, 100.0f));
	MenuElement*      button2 = new MenuElement(*a.getTexture("half.png"), "online", *a.getFont("freedom.ttf"), nullptr, Vf(300.0f, 300.0f));
	MenuElement*      button3 = new MenuElement(*a.getTexture("half.png"), "settings", *a.getFont("freedom.ttf"), nullptr, Vf(300.0f, 500.0f));
	MenuElement*      button4 = new MenuElement(*a.getTexture("half.png"), "Exit", *a.getFont("freedom.ttf"), nullptr, Vf(300.0f, 700.0f));

	//link MenuElements to actions (if void, link to &MenuElement::defaultFunction)
	button1->setAction(sf::Event::MouseButtonPressed, &MenuElement::changeMenu, AGameController::CharacterSelectionMenu);
	button1->setAction(sf::Event::MouseMoved, &MenuElement::movingFunction);
	button2->setAction(sf::Event::MouseMoved, &MenuElement::movingFunction);
	button2->setAction(sf::Event::MouseButtonPressed, &MenuElement::changeMenu, AGameController::ConnectionMenu);
	button3->setAction(sf::Event::MouseMoved, &MenuElement::movingFunction);
	button3->setAction(sf::Event::MouseButtonPressed, &MenuElement::changeMenu, AGameController::OptionMenu);
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
	MenuElement*       optionButton1 = new MenuElement(*a.getTexture("half.png"), "Audio", *a.getFont("freedom.ttf"), nullptr, Vf(300.0f, 200.0f));
	MenuElement*       optionButton2 = new MenuElement(*a.getTexture("half.png"), "Video", *a.getFont("freedom.ttf"), nullptr, Vf(300.0f, 400.0f));
	MenuElement*       optionButton3 = new MenuElement(*a.getTexture("half.png"), "Back", *a.getFont("freedom.ttf"), nullptr, Vf(300.0f, 600.0f));

	optionButton1->setAction(sf::Event::MouseButtonPressed, &MenuElement::changeMenu, AGameController::AudioMenu);
	optionButton1->setAction(sf::Event::MouseMoved, &MenuElement::movingFunction);
	optionButton2->setAction(sf::Event::MouseButtonPressed, &MenuElement::defaultFunction);
	optionButton2->setAction(sf::Event::MouseMoved, &MenuElement::movingFunction);
	optionButton3->setAction(sf::Event::MouseMoved, &MenuElement::movingFunction);
	optionButton3->setAction(sf::Event::MouseButtonPressed, &MenuElement::changeMenu, AGameController::MainMenu);
	OptionMenu->setBackground(optionMenuBackground);
	OptionMenu->addItem(optionButton1);
	OptionMenu->addItem(optionButton2);
	OptionMenu->addItem(optionButton3);

	OptionMenu->applyStyle();

	requestGameEngine.setController< GameMenu >(AGameController::OptionMenu, OptionMenu);
}

void                  initConnectionMenu() {

	AssetManager&       a = requestAssetManager;

	GameMenu*           connectionMenu = new GameMenu("Connection", GameMenu::InLine_Bottom);
	MenuElement*        connectionMenuBackground = new MenuElement(*a.getTexture("connectionMenu.jpg"));
	MenuElement*        connectionMenuInputField1 = new MenuElement(*a.getTexture("transparent.png"), "", *a.getFont("nullShock.ttf"));
	MenuElement*        connectionMenuInputField2 = new MenuElement(*a.getTexture("transparent.png"), "R-Prototyper", *a.getFont("nullShock.ttf"));
	MenuElement*        connectionButton1 = new MenuElement(*a.getTexture("half.png"), "Connect !", *a.getFont("freedom.ttf"));
	MenuElement*        connectionButton2 = new MenuElement(*a.getTexture("half.png"), "Back", *a.getFont("freedom.ttf"));

	connectionMenu->setBackground(connectionMenuBackground);
	connectionButton1->setAction(sf::Event::MouseButtonPressed, &MenuElement::changeMenu, AGameController::MapSelectionMenu);
	connectionButton1->setAction(sf::Event::MouseMoved, &MenuElement::startingFunction);
	connectionButton2->setAction(sf::Event::MouseButtonPressed, &MenuElement::changeMenu, AGameController::MainMenu);
	connectionButton2->setAction(sf::Event::MouseMoved, &MenuElement::movingFunction);
	connectionMenuInputField1->setAction(sf::Event::TextEntered, &MenuElement::getIPAddrInput);
	connectionMenuInputField1->setAction(sf::Event::MouseButtonPressed, &MenuElement::defaultFunction);
	connectionMenuInputField1->setAction(sf::Event::MouseMoved, &MenuElement::defaultFunction);
	connectionMenuInputField2->setAction(sf::Event::TextEntered, &MenuElement::getLoginInput);
	connectionMenuInputField2->setAction(sf::Event::MouseButtonPressed, &MenuElement::defaultFunction);
	connectionMenuInputField2->setAction(sf::Event::MouseMoved, &MenuElement::defaultFunction);
	connectionMenu->addItem(connectionButton1);
	connectionMenu->applyStyle();
	connectionButton2->setPosition(sf::Vector2f(1500.0f, 800.0f));
	connectionMenu->addItem(connectionButton2);
	connectionMenuInputField1->setPosition(sf::Vector2f(772.0f, 345.0f));
	connectionMenu->addItem(connectionMenuInputField1);
	connectionMenuInputField2->setPosition(sf::Vector2f(772.0f, 530.0f));
	connectionMenu->addItem(connectionMenuInputField2);

	requestGameEngine.setController< GameMenu >(AGameController::ConnectionMenu, connectionMenu);
}

void              initSettingsMenu() {

	AssetManager&   a = requestAssetManager;

	GameMenu*       audioMenu = new GameMenu("audio", GameMenu::InBlock_straight);
	MenuElement*    audioBackground = new MenuElement(*a.getTexture("blackhole.jpg"));
	MenuElement*    audioButton1 = new MenuElement(*a.getTexture("emptyGauge.png"), "", *a.getFont("nullShock.ttf"), nullptr, Vf(0, 0), sf::Color::Black);
	MenuElement*    audioButton2 = new MenuElement(*a.getTexture("emptyGauge.png"), "", *a.getFont("nullShock.ttf"), nullptr, Vf(0, 0), sf::Color::Black);
	MenuElement*    audioButton3 = new MenuElement(*a.getTexture("emptyGauge.png"), "", *a.getFont("nullShock.ttf"), nullptr, Vf(0, 0), sf::Color::Black);
	MenuElement*    audioButton4 = new MenuElement(*a.getTexture("half.png"), "Back", *a.getFont("freedom.ttf"));
	MenuElement*    mid1 = new MenuElement(*a.getTexture("fullGaugeBlue.png"), "", *a.getFont("freedom.ttf"));
	MenuElement*    mid2 = new MenuElement(*a.getTexture("fullGaugeBlue.png"), "", *a.getFont("freedom.ttf"));
	MenuElement*    mid3 = new MenuElement(*a.getTexture("fullGaugeBlue.png"), "", *a.getFont("freedom.ttf"));

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
	audioButton4->setAction(sf::Event::MouseButtonPressed, &MenuElement::changeMenu, AGameController::OptionMenu);
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

	playButton->setPosition(sf::Vector2f(playButton->getPosition().x + playButton->getGlobalBounds().width / 2, playButton->getPosition().y + playButton->getGlobalBounds().height / 2));
	playButton->applyStyle(false);
	//	playButton->setPosition(sf::Vector2f(playButton->getPosition().x + playButton->getGlobalBounds().width / 2, playButton->getPosition().y + playButton->getGlobalBounds().height / 2));
	selectionMenu->addItem(playButton);
	selectionMenu->applyStyle();
	//	selectionMenu->addItem(text);
	requestGameEngine.setController< GameMenu >(AGameController::CharacterSelectionMenu, selectionMenu);
}

void			initMapSelectionMenu()
{
	AssetManager&		a = requestAssetManager;

	GameMenu*			selectionMenu = new GameMenu("MapSelection", GameMenu::InRound);
	MenuElement*		playButton = new MenuElement(*a.getTexture("half.png"), "NEXT", *a.getFont("nullShock.ttf"));
//	MenuElement*		name = new MenuElement(*a.getTexture("mapName.png"), "Endor", *a.getFont("nullShock.ttf"));
	
	MenuElement*		scrollingBar = new MenuElement(*a.getTexture("scrollingBar.png"), "", *a.getFont("nullShock.ttf"), selectionMenu);
	MenuElement*		scrollingBubble = new MenuElement(*a.getTexture("scrollingBubble.png"), "", *a.getFont("nullShock.ttf"));

	selectionMenu->setBackground(new MenuElement(*a.getTexture("desert_world.jpg")));
	scrollingBar->setMidground(scrollingBubble);
	scrollingBar->applyStyle(false);
	selectionMenu->addItem(scrollingBar);
	scrollingBar->setPosition(sf::Vector2f(1200.0f, 450.0f));
	scrollingBubble->setPosition(sf::Vector2f(scrollingBubble->getPosition().x, scrollingBar->getGlobalBounds().top + scrollingBubble->getGlobalBounds().height / 2.0f));
	playButton->setOrigin(sf::Vector2f(playButton->getGlobalBounds().width / 2, playButton->getGlobalBounds().height / 2));
	playButton->setPosition(Vf(requestGameEngine.getWindow().getSize().x / 2.0f, 800.0f));
	playButton->setAction(sf::Event::MouseButtonPressed, &MenuElement::changeMenu, AGameController::CharacterSelectionMenu);
	playButton->setAction(sf::Event::MouseMoved, &MenuElement::startingFunction);

	playButton->applyStyle(false);
	selectionMenu->setStyledElementsCadre(sf::FloatRect(sf::Vector2f(494.0f, 267.0f), sf::Vector2f(641.0f, 408.0f)));
	scrollingBar->setAction(sf::Event::MouseButtonPressed, &MenuElement::toggleScrolling);
	scrollingBar->setAction(sf::Event::MouseMoved, &MenuElement::scroll);
	scrollingBar->setAction(sf::Event::MouseButtonReleased, &MenuElement::untoggleScrolling);
	selectionMenu->addItem(new MenuElement(*a.getTexture("mapName.png"), "wonderland", *a.getFont("nullShock.ttf")));
	selectionMenu->addItem(new MenuElement(*a.getTexture("mapName.png"), "Some Bad Neighbourhood\nroom 3 / 4", *a.getFont("nullShock.ttf")));
	selectionMenu->addItem(new MenuElement(*a.getTexture("mapName.png"), "", *a.getFont("nullShock.ttf")));
	selectionMenu->addItem(new MenuElement(*a.getTexture("mapName.png"), "", *a.getFont("nullShock.ttf")));
	//selectionMenu->addItem(new MenuElement(*a.getTexture("mapName.png"), "", *a.getFont("nullShock.ttf")));
	//selectionMenu->addItem(new MenuElement(*a.getTexture("mapName.png"), "", *a.getFont("nullShock.ttf")));
	//selectionMenu->addItem(new MenuElement(*a.getTexture("mapName.png"), "", *a.getFont("nullShock.ttf")));
	//selectionMenu->addItem(new MenuElement(*a.getTexture("mapName.png"), "", *a.getFont("nullShock.ttf")));
	//selectionMenu->addItem(new MenuElement(*a.getTexture("mapName.png"), "", *a.getFont("nullShock.ttf")));
	//selectionMenu->addItem(new MenuElement(*a.getTexture("mapName.png"), "", *a.getFont("nullShock.ttf")));
	//selectionMenu->addItem(new MenuElement(*a.getTexture("mapName.png"), "", *a.getFont("nullShock.ttf")));
	//selectionMenu->addItem(new MenuElement(*a.getTexture("mapName.png"), "", *a.getFont("nullShock.ttf")));
	//selectionMenu->addItem(new MenuElement(*a.getTexture("mapName.png"), "", *a.getFont("nullShock.ttf")));
	selectionMenu->applyStyle();
	selectionMenu->addItem(playButton);
	requestGameEngine.setController< GameMenu >(AGameController::MapSelectionMenu, selectionMenu);
}