#include <SFML/Graphics.hpp>

#include            "Client_graphicUtils.hh"
#include            "SoundSystem.hh"
#include            "GameDecor.hh"
#include            "RessourceManager.hpp"
#include            "AssetManager.hh"
#include            "GameEngine.hh"
#include            "GameMenu.hh"
#include            "Player.hpp"
#include            "Ennemy.hh"
#include            "EnnemyFactory.hh"
#include            "AmmoFactory.hh"
//#include				"AnimationFactory.hh"
#include			"PlayerFactory.hh"

void                setupAnimations() {

  GameEngine&       engine = GameEngine::instanciate();

  Animation         anim1("boss1", Vi(1, 4), Vi(260, 145), Vi(0, 0), 50);
  Animation         anim2("loadingShot", Vi(8, 1), Vi(32, 32), Vi(0, 48), 1	);
  Animation         anim3("explosion", Vi(6, 1), Vi(32, 32), Vi(130, 0), 5);
  Animation         anim4("ship", Vi(1, 1), Vi(32, 17), Vi(0, 0), 100);
  Animation         anim5("void", Vi(1, 1), Vi(1768, 140), Vi(168, 16), 800);
  Animation         anim6("mainmenu", Vi(1, 1), Vi(1920, 1200), Vi(0, 0), 150654);
  Animation         anim7("bullet", Vi(4, 1), Vi(17, 6), Vi(130, 0), 5);
  Animation         anim8("rocket", Vi(1, 12), Vi(162, 35), Vi(00, 0), 1);
  Animation         anim9("spaceBomb", Vi(12, 1), Vi(17, 18), Vi(0, 0), 15);
  Animation         flyingSaucerAnimation("flyingSaucer", Vi(1, 6), Vi(40, 30), Vi(0, 0), 5);
  Animation			bountyHunter("bountyHunter", Vi(4, 1), Vi(64, 64), Vi(0, 0), 50);
  Animation			jet("alienJet", Vi(5, 1), Vi(56, 47), Vi(0, 0), 10);
  Animation			UFO("ufo", Vi(6, 2), Vi(56, 42), Vi(5, 0), 15);
  Animation			BossDeath("BossDeath", Vi(4, 6), Vi(50, 50), Vi(0, 0));
  Animation			bubbleShield("bubbleShield", Vi(3, 2), Vi(211, 192), Vi(0, 0), 5);
  Animation			plasmaBoom("plasmaBoom", Vi(4, 2), Vi(128, 128), Vi(0, 0), 1);
  Animation         anim33("a", Vi(3, 1), Vi(64, 64), Vi(132, 36), 15);
  Animation         anim34("b", Vi(5, 1), Vi(64, 64), Vi(0, 100), 500);
  Animation			plasmaBullet( "plasmaBullet", Vi(2, 1), Vi(16, 15), Vi(232, 100), 5);
  Animation			HBomb("HBomb", Vi(8, 1), Vi(15, 15), Vi(0, 0), 10);
  Animation			Atom("atom", Vi(4, 4), Vi(64, 64), Vi(0, 0), 15);
  Animation			plasmaExplosion("plasmaExplosion", Vi(6, 1), Vi(32, 32), Vi(72, 342), 5);
  Animation         toto = anim33 + anim34;
  Animation         anim35(toto);
  Animation			plaer3("attackShip", Vi(4, 3), Vi(42, 37), Vi(0, 0), 15);
  Animation			spacePiggy("spacePig", Vi(4, 3), Vi(50, 50), Vi(0, 0), 5);
  Animation			smallExplosion("smallExplosion", Vi(6, 1), Vi(32, 30), Vi(0, 0), 12);
  Animation        flyingMinion("flyingMinion", Vi(3, 1), Vi(32, 32), Vi(16, 64), 25);
  Animation			icon("icon", Vi(4, 2), Vi(64, 64), Vi(0, 0), 5);
  Animation			fire("fireshot", Vi(2, 1), Vi(32, 16), Vi(0, 0), 1);

  engine.addAnimation(&fire);
  engine.addAnimation(&flyingMinion);
  engine.addAnimation(&smallExplosion);
  Animation			mediumExplosion("mediumExplosion", Vi(8, 5), Vi(55, 55), Vi(0, 0), 2);

  // AnimationFactory	f;
  // f.loadAnimation();

  engine.addAnimation(&icon);
  engine.addAnimation(&mediumExplosion);
  engine.addAnimation(&spacePiggy);
  engine.addAnimation(&plaer3);
  engine.addAnimation(&HBomb);
  engine.addAnimation(&Atom);
  engine.addAnimation(&bubbleShield);
  engine.addAnimation(&plasmaBoom);
  engine.addAnimation(&plasmaBullet);
  engine.addAnimation(&plasmaExplosion);
  anim35.setAnimationName("bigExplosion");
  engine.addAnimation(&anim1);
  engine.addAnimation(&anim2);
  engine.addAnimation(&anim3);
  engine.addAnimation(&anim35);
  engine.addAnimation(&anim4);
  engine.addAnimation(&anim5);
  engine.addAnimation(&anim6);
  engine.addAnimation(&anim7);
  engine.addAnimation(&anim8);
  engine.addAnimation(&anim9);
  engine.addAnimation(&flyingSaucerAnimation);
  engine.addAnimation(&bountyHunter);
  engine.addAnimation(&jet);
  // engine.addAnimation(f.getAnimation("ufo"));
  // engine.addAnimation(f.getAnimation("spaceFighter"));
  engine.addAnimation(&UFO);
  engine.addAnimation(&BossDeath);
}

void               setupAnimatedSprites() {

  GameEngine&      e = GameEngine::instanciate();
  AssetManager&    a = AssetManager::instanciate();

  GameDecor*       background = new GameDecor("./assets/sprites/starybackgrnd.jpg");
  GameDecor*       DecorShip = new GameDecor("./assets/sprites/r-typesheet37.gif", 1, sf::Color::Black, false);
  GameDecor*       planet = new GameDecor("./assets/sprites/planet.png", 1, sf::Color::Black, false);
  GameDecor*       littlePlanet = new GameDecor("./assets/sprites/littlePlanet.png", 1, sf::Color::Black, false);
  GameDecor*       alienship = new GameDecor("./assets/sprites/AlienShip.png", 1, sf::Color::Black, false);
  GameDecor*       bigGreenPlanet = new GameDecor("./assets/sprites/bigGreenPlanet.png", 1, sf::Color::Black, false);
  GameDecor*       littleDestroyedPlanet = new GameDecor("./assets/sprites/littleDestroyedPlanet.png", 1, sf::Color::Black, false);

  background->setCadre(sf::IntRect(0, 0, PLAY_WIDTH, PLAY_HEIGHT));
  background->setVectors(sf::Vector2i(1, 0));
  DecorShip->setCadre(sf::IntRect(0, 0, 590, 170));
  DecorShip->setPosition(PLAY_WIDTH, PLAY_HEIGHT - 150);
  DecorShip->setVectors(sf::Vector2i(0, 0), sf::Vector2f(-0.5, 0));
  planet->setPosition(PLAY_WIDTH, PLAY_HEIGHT / 2);
  planet->setVectors(Vi(0, 0), Vf(-0.2f, 0.0f));
  littlePlanet->setPosition(PLAY_WIDTH, PLAY_HEIGHT / 2);
  littlePlanet->setVectors(Vi(0, 0), Vf(-0.1f, 0.0f));
  bigGreenPlanet->setPosition(PLAY_WIDTH * 2.5, PLAY_HEIGHT / 4);
  bigGreenPlanet->setVectors(Vi(0, 0), Vf(-0.2f, 0.0f));
  littleDestroyedPlanet->setPosition(PLAY_WIDTH * 3, PLAY_HEIGHT / 4);
  littleDestroyedPlanet->setVectors(Vi(0, 0), Vf(-0.1f, 0.0f));
  alienship->setCadre(sf::IntRect(25, 0, static_cast <int >(alienship->getGlobalBounds().width), static_cast< int> (alienship->getGlobalBounds().height)));
  alienship->setVectors(Vi(0, 0), sf::Vector2f(0.5f, 0.0f));

  e.addGameObject<GameDecor>(background);
  e.addGameObject<GameDecor>(DecorShip);
  e.addGameObject<GameDecor>(littlePlanet);
  e.addGameObject<GameDecor>(planet);
  e.addGameObject<GameDecor>(littleDestroyedPlanet);
  e.addGameObject<GameDecor>(bigGreenPlanet);

  EnnemyFactory               ef;
  AmmoFactory                 af;

  ef.loadEnnemyConfigFromFile();
  af.loadAmmoConfigFromFile();

  Ennemy*			Boss = ef.createEnnemy("boss1", Vf(PLAY_WIDTH - 300, PLAY_HEIGHT), true);

  Boss->setLife(sf::Vector2i(5000, 5000));
  Boss->setSpeed(0);
  Boss->setScale(sf::Vector2f(1.5f, 1.5f));
  Boss->setPosition(sf::Vector2f(PLAY_WIDTH - Boss->getGlobalBounds().width, PLAY_HEIGHT - Boss->getGlobalBounds().height));

 e.addEnnemy(Boss);

 Boss = ef.createEnnemy("alienJet", Vf(3000, 450), false);
 Boss->setSpeed(4);
 e.addEnnemy(Boss);
 Boss = ef.createEnnemy("alienJet", Vf(3100, 400), false);
 Boss->setSpeed(4);
 e.addEnnemy(Boss);
 Boss = ef.createEnnemy("alienJet", Vf(3100, 500), false);
 Boss->setSpeed(4);
 e.addEnnemy(Boss);
 //e.addEnnemy(ef.createEnnemy("boss1", Vf(PLAY_WIDTH, PLAY_HEIGHT), true));
  //e.addEnnemy(ef.createEnnemy("boss1", Vf(PLAY_WIDTH * 1.5f, PLAY_HEIGHT), true));
  //e.addEnnemy(ef.createEnnemy("boss1", Vf(PLAY_WIDTH * 2, PLAY_HEIGHT), true));
  e.addEnnemy(ef.createEnnemy("alienShipBoss", Vf(500, 0), false));
  e.addEnnemy(ef.createEnnemy("bountyHunter", Vf(1500, PLAY_HEIGHT - 64), false));
  e.addEnnemy(ef.createEnnemy("alienJet", Vf(1500, 400), false));
  e.addEnnemy(ef.createEnnemy("alienJet", Vf(1600, 450), false));
  e.addEnnemy(ef.createEnnemy("alienJet", Vf(1600, 350), false));
  e.addEnnemy(ef.createEnnemy("ufo", Vf(2500, 250), false));
  e.addEnnemy(ef.createEnnemy("flyingMinion", Vf(2000, 600), false));
  e.addEnnemy(ef.createEnnemy("flyingMinion", Vf(2050, 620), false));
  e.addEnnemy(ef.createEnnemy("flyingMinion", Vf(2100, 600), false));
  e.addEnnemy(ef.createEnnemy("flyingMinion", Vf(2150, 580), false));
  e.addEnnemy(ef.createEnnemy("flyingMinion", Vf(2200, 600), false));
  e.addEnnemy(ef.createEnnemy("flyingMinion", Vf(2250, 620), false));

  e.addEnnemy(ef.createEnnemy("bubbleShield", Vf(1000, 500), false));

  e.addEnnemy(ef.createEnnemy("flyingMinion", Vf(4000, 600), false));
  e.addEnnemy(ef.createEnnemy("flyingMinion", Vf(4050, 620), false));
  e.addEnnemy(ef.createEnnemy("flyingMinion", Vf(4100, 600), false));
  e.addEnnemy(ef.createEnnemy("flyingMinion", Vf(4150, 580), false));
  e.addEnnemy(ef.createEnnemy("flyingMinion", Vf(4200, 600), false));
  e.addEnnemy(ef.createEnnemy("flyingMinion", Vf(4250, 620), false));


  e.addEnnemy(ef.createEnnemy("flyingMinion", Vf(6000, 600), false));
  e.addEnnemy(ef.createEnnemy("flyingMinion", Vf(6050, 620), false));
  e.addEnnemy(ef.createEnnemy("flyingMinion", Vf(6100, 600), false));
  e.addEnnemy(ef.createEnnemy("flyingMinion", Vf(6150, 580), false));
  e.addEnnemy(ef.createEnnemy("flyingMinion", Vf(6200, 600), false));
  e.addEnnemy(ef.createEnnemy("flyingMinion", Vf(6250, 620), false));

  e.addBonus(*(e._bonusF.createBonus("speedBonus", Vf(500, 500), 3)));
  e.addBonus(*(e._bonusF.createBonus("minigunBonus", Vf(1000, 500), 3)));

}


void initMainMenu();
void initOptionMenu();
void initSettingsMenu();
void initConnectionMenu();
void initCharacterSelectionMenu();


#ifdef			_WIN32
int WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PSTR lpCmdLine, int nCmdShow) {
#else
int main() {
#endif

  GameEngine&       engine = GameEngine::instanciate();
  SoundSystem&      audioEngine = SoundSystem::instanciate();
  AssetManager::instanciate();
#ifdef _WIN32
  AllocConsole();
  freopen("conin$", "r", stdin);
  freopen("conout$", "w", stdout);
  freopen("conout$", "w", stderr);
#endif
  engine.start();

  setupAnimations();
  setupAnimatedSprites();

  initMainMenu();
  initOptionMenu();
  initConnectionMenu();
  initSettingsMenu();
  initCharacterSelectionMenu();
  audioEngine.addMusic("unity.wav");
  audioEngine.addMusic("menuMusic.wav");
  audioEngine.setCurrentMusic("menuMusic.wav");
  SoundSystem::instanciate().playMusic();
  audioEngine.addEffect("blop.wav");
  audioEngine.addEffect("bigExplosion.wav");
  audioEngine.addEffect("pulseShot.wav");

  engine.run();
  return 0;
}
