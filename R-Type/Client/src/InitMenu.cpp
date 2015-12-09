#include      "GameMenu.hh"
#include      "GameEngine.hh"

void          initMainMenu() {

	AssetManager&     a = AssetManager::instanciate();

	//create main menu and its MenuElements | By default, Inline-block display style
	GameMenu*         menu = new GameMenu("Menu");
	MenuElement*      background = new MenuElement(*a.getTexture("MainMenu.jpg"));
	MenuElement*      title = new MenuElement(*a.getTexture("title.png"), "", *a.getFont("freedom.ttf"));
	MenuElement*      button1 = new MenuElement(*a.getTexture("shadedblueButton.png"), "Play Solo", *a.getFont("freedom.ttf"), Vf(300.0f, 100.0f));
	MenuElement*      button2 = new MenuElement(*a.getTexture("shadedblueButton.png"), "Play Multi", *a.getFont("freedom.ttf"), Vf(300.0f, 300.0f));
	MenuElement*      button3 = new MenuElement(*a.getTexture("shadedblueButton.png"), "Options", *a.getFont("freedom.ttf"), Vf(300.0f, 500.0f));
	MenuElement*      button4 = new MenuElement(*a.getTexture("shadedblueButton.png"), "Quit Game", *a.getFont("freedom.ttf"), Vf(300.0f, 700.0f));

	//link MenuElements to actions (if void, link to &MenuElement::defaultFunction)
	button1->setAction(sf::Event::MouseButtonPressed, &MenuElement::openConnectionMenu);
	button1->setAction(sf::Event::MouseMoved, &MenuElement::defaultFunction);
	button2->setAction(sf::Event::MouseMoved, &MenuElement::defaultFunction);
	button3->setAction(sf::Event::MouseMoved, &MenuElement::defaultFunction);
	button3->setAction(sf::Event::MouseButtonPressed, &MenuElement::openOptionMenu);
	button4->setAction(sf::Event::MouseButtonPressed, &MenuElement::quitGame);
	button4->setAction(sf::Event::MouseMoved, &MenuElement::defaultFunction);

	//set all elements to the menu
	menu->setBackground(background);
	menu->addItem(title);
	menu->addItem(button1);
	//  menu->addItem(button2);
	menu->addItem(button3);
	menu->addItem(button4);

	//force the menu style on all elements
	menu->applyStyle();

	// link main menu to the GameEngine as MainMenuController
	requestGameEngine.setController< GameMenu >(AGameController::MainMenu, menu);
}

void                 initOptionMenu() {

	AssetManager&      a = AssetManager::instanciate();

	GameMenu*          OptionMenu = new GameMenu("Options", GameMenu::InBlock);
	MenuElement*       optionMenuBackground = new MenuElement(*a.getTexture("optionMenuBackground.jpg"));
	MenuElement*       optionButton1 = new MenuElement(*a.getTexture("shadedblueButton.png"), "Audio", *a.getFont("freedom.ttf"), Vf(300.0f, 200.0f));
	MenuElement*       optionButton2 = new MenuElement(*a.getTexture("shadedblueButton.png"), "Video", *a.getFont("freedom.ttf"), Vf(300.0f, 400.0f));
	MenuElement*       optionButton3 = new MenuElement(*a.getTexture("shadedblueButton.png"), "Back", *a.getFont("freedom.ttf"), Vf(300.0f, 600.0f));

	optionButton1->setAction(sf::Event::MouseButtonPressed, &MenuElement::openAudioMenu);
	optionButton1->setAction(sf::Event::MouseMoved, &MenuElement::defaultFunction);
	optionButton2->setAction(sf::Event::MouseButtonPressed, &MenuElement::defaultFunction);
	optionButton2->setAction(sf::Event::MouseMoved, &MenuElement::defaultFunction);
	optionButton3->setAction(sf::Event::MouseMoved, &MenuElement::defaultFunction);
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

	GameMenu*           connectionMenu = new GameMenu("Connection", GameMenu::InBlock_straight);
	MenuElement*        connectionMenuBackground = new MenuElement(*a.getTexture("MainMenu.jpg"));
	MenuElement*        connectionMenuInputField1 = new MenuElement(*a.getTexture("InputField.png"), "Server", *a.getFont("nullShock.ttf"));
	MenuElement*        connectionMenuInputField2 = new MenuElement(*a.getTexture("InputField.png"), "Login", *a.getFont("nullShock.ttf"));
	MenuElement*        connectionMenuServerText = new MenuElement(*a.getTexture("transparent.png"), "Enter Server Address", *a.getFont("freedom.ttf"));
	MenuElement*        connectionMenuLoginText = new MenuElement(*a.getTexture("transparent.png"), "Enter Login", *a.getFont("freedom.ttf"));
	MenuElement*        connectionButton1 = new MenuElement(*a.getTexture("shadedblueButton.png"), "Connect !", *a.getFont("freedom.ttf"));
	MenuElement*        connectionButton2 = new MenuElement(*a.getTexture("shadedblueButton.png"), "Back", *a.getFont("freedom.ttf"));

	MenuElement*        test = new MenuElement(*a.getTexture("transparent.png"), "Volume 50", *a.getFont("nullShock.ttf"));

	sf::Sprite* tests = new sf::Sprite;
	tests->setTexture(*a.getTexture("glowtube.png"));
	test->setMidground(tests);
	connectionMenu->setBackground(connectionMenuBackground);
	connectionButton1->setAction(sf::Event::MouseButtonPressed, &MenuElement::resumeGame);
	connectionButton1->setAction(sf::Event::MouseMoved, &MenuElement::defaultFunction);
	connectionButton2->setAction(sf::Event::MouseButtonPressed, &MenuElement::openMainMenu);
	connectionButton2->setAction(sf::Event::MouseMoved, &MenuElement::defaultFunction);
	connectionMenuInputField1->setAction(sf::Event::TextEntered, &MenuElement::getIPAddrInput);
	connectionMenuInputField2->setAction(sf::Event::TextEntered, &MenuElement::getLoginInput);
	connectionMenu->addItem(connectionMenuServerText);
	connectionMenu->addItem(connectionMenuInputField1);
	connectionMenu->addItem(connectionMenuLoginText);
	connectionMenu->addItem(connectionMenuInputField2);
	connectionMenu->addItem(connectionButton1);
	connectionMenu->addItem(connectionButton2);
	//  connectionMenu->addItem(test);
	connectionMenu->applyStyle();

	requestGameEngine.setController< GameMenu >(AGameController::ConnectionMenu, connectionMenu);
}

void              initSettingsMenu() {

	AssetManager&   a = requestAssetManager;

	GameMenu*       audioMenu = new GameMenu("audio", GameMenu::InBlock_straight);
	MenuElement*    audioBackground = new MenuElement(*a.getTexture("optionMenuBackground.jpg"));
	MenuElement*    audioButton1 = new MenuElement(*a.getTexture("fullGlowGauge.png"), "", *a.getFont("nullShock.ttf"), Vf(0, 0), sf::Color::Black);
	MenuElement*    audioButton2 = new MenuElement(*a.getTexture("fullGlowGauge.png"), "", *a.getFont("nullShock.ttf"), Vf(0, 0), sf::Color::Black);
	MenuElement*    audioButton3 = new MenuElement(*a.getTexture("fullGlowGauge.png"), "", *a.getFont("nullShock.ttf"), Vf(0, 0), sf::Color::Black);
	MenuElement*    audioButton4 = new MenuElement(*a.getTexture("shadedblueButton.png"), "Back", *a.getFont("freedom.ttf"));
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
	audioButton4->setAction(sf::Event::MouseMoved, &MenuElement::defaultFunction);
	audioButton4->setAction(sf::Event::MouseButtonPressed, &MenuElement::openOptionMenu);
	audioMenu->addItem(audioButton1);
	audioMenu->addItem(audioButton2);
	audioMenu->addItem(audioButton3);
	audioMenu->addItem(audioButton4);
	audioMenu->applyStyle();

	requestGameEngine.setController< GameMenu >(AGameController::AudioMenu, audioMenu);
}
