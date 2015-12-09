#ifndef              ___CLIENT_GRAPHIC_UTILS_HH___
# define             ___CLIENT_GRAPHIC_UTILS_HH___

# include             <string>
# include             <iostream>
# include             <iomanip>
# include             <vector>
# include             <map>
# include             <memory>

#define				_USE_MATH_DEFINES
# include             <cmath>
# include             <math.h>

# include				<SFML/Graphics.hpp>

# ifndef				_WIN32
#		include             <unistd.h>
# else
#		include				<windows.h>
#endif			// !_WIN32

# define              Vi(x, y)                 (sf::Vector2i((x), (y)))
# define              Vf(x, y)                 (sf::Vector2f((x), (y)))

# ifdef					__GNUC__
#	define              _unused                   __attribute__((unused))
# endif					// !__GNUC___

# define              requestGameEngine			GameEngine::instanciate()
# define              requestAssetManager     AssetManager::instanciate()
# define              requestAudioEngine		SoundSystem::instanciate()
# define              requestCollider					GameEngine::instanciate().getCollisionManager()
# define              requestWindow				GameEngine::instanciate().getWindow()

extern unsigned int counter;

#endif               /* !___CLIENT_GRAPHIC_UTILS_HH___ */
