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

///* will be replaced by named class calling GameEngine to add own animations */
void                setupAnimations() {



  GameEngine&       engine = GameEngine::instanciate();

  Animation         anim1("boss1", Vi(1, 4), Vi(260, 145), Vi(0, 0), 50);
  Animation         anim2("loadingShot", Vi(8, 1), Vi(32, 32), Vi(0, 48), 5);
  Animation         anim3("explosion", Vi(6, 1), Vi(32, 32), Vi(130, 0), 5);
  Animation         anim4("ship", Vi(1, 1), Vi(32, 17), Vi(0, 0), 100);
  Animation         anim5("void", Vi(1, 1), Vi(1768, 140), Vi(168, 16), 800);
  Animation         anim6("mainmenu", Vi(1, 1), Vi(1920, 1200), Vi(0, 0), 150654);
  Animation         anim7("bullet", Vi(4, 1), Vi(17, 6), Vi(130, 0), 5);
  Animation         anim8("rocket", Vi(1, 12), Vi(162, 35), Vi(00, 0), 5);
  Animation         anim9("spaceBomb", Vi(1, 12), Vi(17, 18), Vi(0, 0), 50);
  Animation         flyingSaucerAnimation("flyingSaucer", Vi(1, 6), Vi(40, 30), Vi(0, 0), 5);

  Animation         anim33("a", Vi(3, 1), Vi(64, 64), Vi(132, 36), 15);
  Animation         anim34("b", Vi(5, 1), Vi(64, 64), Vi(0, 100), 500);

  Animation         toto = anim33 + anim34;
  Animation         anim35(toto);

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

  AnimatedSprite  animSprite1(*a.getTexture("r-typesheet34.gif"), e.getAnimation("boss1"), sf::Color::Blue);
  AnimatedSprite  animSprite2(*a.getTexture("r-typesheet1.gif"), e.getAnimation("loadingShot"), sf::Color::Black);
  AnimatedSprite  animSprite3(*a.getTexture("r-typesheet44.gif"), e.getAnimation("explosion"), sf::Color::Black);
  AnimatedSprite  animSprite4(*a.getTexture("r-typesheet42.gif"), e.getAnimation("ship"), sf::Color::Black);
  AnimatedSprite  animSprite5(*a.getTexture("AlienShip.png"), e.getAnimation("void"), sf::Color::Black);
  AnimatedSprite  flyingSaucer(*a.getTexture("flyingSaucer.png"), e.getAnimation("flyingSaucer"), sf::Color::Black);


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

  animSprite1.setPosition(PLAY_WIDTH - e.getAnimation("boss1").getFrameDimensions().x + 0.0f, PLAY_HEIGHT - e.getAnimation("boss1").getFrameDimensions().y + 1.0f);
  animSprite3.setPosition(500.0f, 500.0f);
  animSprite4.setPosition(200, PLAY_HEIGHT / 2);
  animSprite2.setPosition(animSprite4.getPosition().x + 90, animSprite4.getPosition().y + 20);
  animSprite4.scale(Vf(3.0f, 3.0f));
  flyingSaucer.setPosition(400, 400);

  e.addGameObject<GameDecor>(background);
  e.addGameObject<GameDecor>(DecorShip);
  e.addGameObject<GameDecor>(littlePlanet);
  e.addGameObject<GameDecor>(planet);
  e.addGameObject<GameDecor>(littleDestroyedPlanet);
  e.addGameObject<GameDecor>(bigGreenPlanet);
//  e.addGameObject(alienship);

 // Ammunition*           amo = new Ammunition(*a.getTexture("rocket.png"), e.getAnimation("rocket"), 1000, sf::Color::White);
//  Ammunition*           bull = new Ammunition(*a.getTexture("r-typesheet43.gif"), e.getAnimation("bullet"), 1000, sf::Color::White);

  //amo->setScale(0.5f, 0.5f);
  //amo->setFilename("theRocket");
  //bull->setFilename("theBullet");
  EnnemyFactory               ef;
  AmmoFactory                 af;

  ef.loadEnnemyConfigFromFile();
  af.loadAmmoConfigFromFile();

  Ennemy*             ennemy = new Ennemy(animSprite1, *af.createAmmo("simpleBullet"));
  Ennemy*             alienShip = new Ennemy(animSprite5, *af.createAmmo("simpleBullet"));
  Ennemy*             example = new Ennemy(*a.getTexture("r-typesheet34.gif"), e.getAnimation("boss1"), *af.createAmmo("simpleBullet"), sf::Color::Blue);

  example->setPosition(Vf(600, 200));

 /* AnimatedSprite*        bulletAnim = new AnimatedSprite(*a.getTexture("r-typesheet43.gif"), e.getAnimation("bullet"), sf::Color::White);
  AnimatedSprite*        bulletAnim2 = new AnimatedSprite(*bulletAnim);

  bulletAnim->setPosition(Vf(300, 300));
  bulletAnim2->setPosition(Vf(300, 350));
  Ammunition*           bullet3 = new Ammunition(*a.getTexture("r-typesheet43.gif"), e.getAnimation("bullet"), 100000, sf::Color::White);

  bullet3->setPosition(Vf(250, 250));
 */ // e.addGameObject(bulletAnim);
  // e.addGameObject(bulletAnim2);
  // e.addAmmo(bullet3);

  alienShip->addShotVertex(Vf(alienShip->getGlobalBounds().width / 7 + 5, alienShip->getGlobalBounds().height - 20));
  alienShip->addShotVertex(Vf(alienShip->getGlobalBounds().width / 4 + 20, alienShip->getGlobalBounds().height - 30));
  alienShip->addShotVertex(Vf(alienShip->getGlobalBounds().width / 4 + 90, alienShip->getGlobalBounds().height - 30));
  alienShip->addShotVertex(Vf(alienShip->getGlobalBounds().width / 4 + 150, alienShip->getGlobalBounds().height - 30));
  alienShip->addShotVertex(Vf(alienShip->getGlobalBounds().width / 4 + 220, alienShip->getGlobalBounds().height - 30));

  ennemy->addShotVertex(Vf(0, ennemy->getGlobalBounds().height / 2 + 10));
  ennemy->addShotVertex(Vf(ennemy->getGlobalBounds().width / 4, 5));
  ennemy->addShotVertex(Vf(ennemy->getGlobalBounds().width / 4 * 3, 15));

//  e.addEnnemy(ennemy);
  // e.addEnnemy(alienShip);
  // e.addEnnemy(example);
  e.setPlayer(new Player(flyingSaucer, *af.createAmmo("simpleBullet")));
  e.getPlayer().setSpeed(2);
  e.getPlayer().setTexture(*a.getTexture("flyingSaucer.png"));
  e.getPlayer().addWeapon(af.createAmmo("rocket"));

  e.getPlayer().switchWeapon();

//  delete animSprite4;
  PlayerController*           playerC = new PlayerController(e.getPlayer());
  e.setController< PlayerController >(AGameController::GameControls, playerC);
//  delete flyingSaucer;

  //EnnemyFactory               ef;
  //AmmoFactory                 af;

  //ef.loadEnnemyConfigFromFile();
  //af.loadAmmoConfigFromFile();

  Ammunition*                BULLET = af.createAmmo("simpleBullet");
  Ennemy*                     TEST = ef.createEnnemy("boss1", Vf(PLAY_WIDTH, PLAY_HEIGHT), true);
  Ennemy*                     TEST2 = ef.createEnnemy("boss1", Vf(PLAY_WIDTH * 1.5f, PLAY_HEIGHT), true);
  Ennemy*                     TEST3 = ef.createEnnemy("boss1", Vf(PLAY_WIDTH * 2, PLAY_HEIGHT), true);
  Ennemy*                     BOSS = ef.createEnnemy("alienShipBoss", Vf(500, 0), false);

  BOSS->setSpeed(1);
  e.addEnnemy(TEST);
  e.addEnnemy(TEST2);
  e.addEnnemy(TEST3);
  e.addEnnemy(BOSS);
}

void                setupAmmos()
{
  AssetManager&     a = AssetManager::instanciate();
  GameEngine&       e = GameEngine::instanciate();

  Ammunition*       a1 = new Ammunition(*a.getTexture("r-typesheet43.gif"), e.getAnimation("bullet"), 10000, sf::Color::White);
  a1->setPosition(600.0f, 300.0f);
  a1->setTargetPosition(Vf(50.0f, 250.0f));
  e.addAmmo(a1);
}

void initMainMenu();
void initOptionMenu();
void initSettingsMenu();
void initConnectionMenu();


#ifdef			_WIN32
int WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PSTR lpCmdLine, int nCmdShow) {
#else
int main() {
#endif

  GameEngine&       engine = GameEngine::instanciate();
  SoundSystem&      audioEngine = SoundSystem::instanciate();

  AllocConsole();
  freopen("conin$", "r", stdin);
  freopen("conout$", "w", stdout);
  freopen("conout$", "w", stderr);

  engine.start();

  setupAnimations();
  setupAnimatedSprites();

  initMainMenu();
  initOptionMenu();
  initConnectionMenu();
  initSettingsMenu();

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
