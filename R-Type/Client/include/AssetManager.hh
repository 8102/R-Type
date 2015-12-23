#ifndef                   ___ASSET_MANAGER_HH___
# define                  ___ASSET_MANAGER_HH___

# include                 <SFML/Graphics.hpp>
# include                 <SFML/Audio/SoundBuffer.hpp>
# include                 <SFML/Audio/Sound.hpp>
# include                 <SFML/Audio/Music.hpp>

# include                 "Client_graphicUtils.hh"
# include                 "RessourceManager.hpp"
# include                 "SoundTrack.hh"

class                     AssetManager
{
public:

	static AssetManager&           instanciate();

private:

	AssetManager();

public:

	~AssetManager();
	void											clear();

public:

	sf::SoundBuffer*				getSoundBuffer(std::string const& filename);
	sf::Music*							getMusic(std::string const& filename);
	sf::Texture*						getTexture(std::string const& filename);
	sf::Font*							getFont(std::string const& filename);

private:

	RessourceManager< sf::SoundBuffer >					_audioEffects;
	RessourceManager< sf::Texture >							_textures;
	RessourceManager< SoundTrack >						_musics;
	RessourceManager< sf::Font >								_fonts;

};

#endif                    /* !___ASSET_MANAGER_HH___ */
