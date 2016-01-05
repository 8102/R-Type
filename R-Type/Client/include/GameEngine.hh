#ifndef               ___GAME_ENGINE_HH___
# define              ___GAME_ENGINE_HH___

# include				"Client.hh"

# include             "Ammunition.hh"
# include             "Animation.hh"
# include             "AnimatedSprite.hh"
# include             "Client_graphicUtils.hh"
# include             "IInteractive.hh"
# include             "SoundSystem.hh"
# include             "GameDecor.hh"
# include             "AGameController.hh"
# include             "GameMenu.hh"
# include             "PlayerController.hh"
# include             "CollisionManager.hh"
# include             "Ennemy.hh"
//# include				"AnimationFactory.hh"
# include				"AmmoFactory.hh"
# include				"EnnemyFactory.hh"
# include				"PlayerFactory.hh"
# include				"BonusFactory.hh"
# include				"GameRythmer.hh"
# include				"Timer.hh"
# include				"GUI.hh"


#define             PLAY_WIDTH    1600
#define             PLAY_HEIGHT   900
#define             INTERFACE_WIDTH 1200;
#define             INTERFACE_HEIGHT 0
# define            WIN_W PLAY_WIDTH
# define            WIN_H PLAY_HEIGHT + INTERFACE_HEIGHT
# define            WINDOW_FRAME_LIMIT  120

# define			requestNetwork			GameEngine::instanciate()._network

# define              WINDOW_TITLE        "R-{PROTO}-TYPE"

// Singleton GameEngine
//   Will manage all GameElements as well as sounds and Menus
//   Will handle connections through NetworkInterface station
//   Handles the calls to AssetManager

class                GameEngine
{
public:

	static GameEngine&        instanciate();

private:

	GameEngine();

public:

	~GameEngine();
	void									clear();

public:

	/*
	** Engine behavior methods */
	void					start();
	void					run();
	void					launchGame();
	void					pause();
	void					resume();
	void					stop();
	void					exit();

public:

	/*
	** Game - modifier methods */
	void					updateDecors();
	void					updateBonus();
	void					updateAmmos();
	void					updateFXs();
	void					updateEnnemies();
	void					updatePlayers();
	void					update();

public:

	/*
	** rendering functions */
	void					draw();
	void					draw(sf::Drawable const& target);

public:

	bool					isRunning() const;
	bool					isPaused() const;
	void					pause(bool pauseFlag);
	bool					isReady() const;

public:

	void                addAnimation(Animation* animation);
	void                addGameObject(AGameElement *gameObject);

	template< class T >
	void                addGameObject(T *gameObject) {
		_gameObjects.push_back(make_unique< T >(*gameObject));
	}

	template< class T >
	void                setController(AGameController::eController const& slot, T* controller) {
		_gameControllers[slot] = make_unique< T >(*controller);
	}

	void                setControllerIndex(AGameController::eController const& index);

	void					addFX(AnimatedSprite *FX, sf::Vector2f const& position = Vf(0.0f, 0.0f));
	void					addFX(AnimatedSprite *FX, Ammunition const& ammo);
	void					addFX(std::string const& FXName, sf::Vector2f const& position = Vf(0.0f, 0.0f));
	void					addFX(std::string const&, std::string const&, sf::Vector2f const&, sf::Color const& colormask = sf::Color::Black);
	void					addAmmo(Ammunition *ammo);
	void					addEnnemy(Ennemy *ennemy);
	void					addBonus(Bonus const& b);

	//void					setPlayer(Player* player);
	void					setPlayer(int const& index);
	void					initPlayed();

public:

	Animation&							getAnimation(std::string const& animationName);
	AGameElement&					getGameObject(unsigned int index);
	Player&								getPlayer();
	Player&								getPlayer(int const& playerID);

public:

	sf::RenderWindow&			getWindow() const;
	CollisionManager&				getCollisionManager();
	GUI&									getGUI();
	AGameController*				getController(AGameController::eController const& index);

public:

	void										startClock();
	float										getTime();

private:

	/*
	** From start of GameEngine to its destruction */
	bool                _isRunning;
	/*
	** Needs the game to be updated ? */
	bool                _isPaused;

private:

	/*
	** Game Window, initialised in GameEngine::start() |
	** shortcut : requestWindow */
	std::unique_ptr< sf::RenderWindow >            _win;

	/*
	** PixelCollisionManager, initialised at creation of GameEngine
	** | shortcut : requestCollider */
	CollisionManager											_collisionChecker;
	
	std::unique_ptr< GUI >									_GUI;
	
	Timer																_clock;

private:

	/*
	** For event loop */
	sf::Event															 _eventCatcher;
	/*
	** indicates which of _gameControllers directs actions
	** according to user's inputs */
	AGameController::eController							_controlerIndex;

	std::map< AGameController::eController,
		std::unique_ptr< AGameController >>		_gameControllers;

private:

	std::vector< std::unique_ptr< AGameElement >>			_gameObjects;
	std::vector< std::unique_ptr< Ammunition >>				_ammos;
	std::vector< std::unique_ptr< Ennemy >>						_ennemies;
	std::vector< std::unique_ptr< Bonus >>						_bonus;
	std::vector< std::unique_ptr< Player >>						_players;
	/*
	** Player on this client */
//	std::unique_ptr< Player >												 _player;
	Player*																				_player;

private:

	std::vector< std::unique_ptr < AnimatedSprite > >		_FX;
	std::map<std::string, std::unique_ptr< Animation >>  _animations;

public:

	AmmoFactory											_ammoF;
//	AnimationFactory									_animF;
	EnnemyFactory										_ennemyF;
	PlayerFactory											_playF;
	BonusFactory											_bonusF;

public:

	
	Client														_network;

	enum eClientMode
	{
		online = 0,
		offline
	};

	eClientMode											_mode;

};

#endif                /* !___GAME_ENGINE_HH___ */
