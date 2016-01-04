#ifndef               ___RESSOURCE_MANAGER_HPP___
# define              ___RESSOURCE_MANAGER_HPP___

#	ifndef			_WIN32
	# include              <dirent.h>
#	endif			// _WIN32

# include              "Client_graphicUtils.hh"

# ifdef		_WIN32
#				define EFFECT_FOLDER    ".\\assets\\audio\\effects\\"
#				define ICON_FOLDER    ".\\assets\\icons\\"
#				define MUSIC_FOLDER     ".\\assets\\audio\\music\\"
#				define FONT_FOLDER      ".\\assets\\fonts\\"
#				define TEXTURE_FOLDER   ".\\assets\\sprites\\"
# else
#				define EFFECT_FOLDER    "./assets/audio/effects/"
#				define ICON_FOLDER    "./assets/icons/"
#				define MUSIC_FOLDER     "./assets/audio/music/"
#				define FONT_FOLDER      "./assets/fonts/"
#				define TEXTURE_FOLDER   "./assets/sprites/"
# endif		// !platform
// Template Class RessourceManager :
//
//     Will handle assets of type R (for Ressource) using template
//     Works for sf::SoundBuffer, SoundTrack (sf::Music), sf::Texture, sf::Fonts
//     Can load a full folder if needed, only terminating name is used, in order to weight less
//     and being esaier to handle, so be sure two assets in two differents folder don't share the same name

template <class R>
class                 RessourceManager
{

public:

	RessourceManager(std::string const& ressourceFolder)
		: _ressourceFolder(ressourceFolder) {
	}

	~RessourceManager() {

		clear();
		// for (auto it = _ressources.begin(); it != _ressources.end(); it++)
		//   if (it->second != nullptr)
		//     delete it->second;
	}

	void				clear() {

		// for (auto it = _ressources.begin(); it != _ressources.end(); it++)
		// 	it->second.reset();
	}

public:

	void              loadFolder() {

		//DIR*             pdir = NULL;
		//struct dirent   *pent = NULL;

		//if ((pdir = opendir(_ressourceFolder.c_str())) == NULL)
		//	return;
		//while ((pent = readdir(pdir)) != NULL) {
		//	if (pent->d_type == DT_REG)
		//		loadRessource(pent->d_name);
		//}
		//closedir(pdir);
	}

	bool              loadRessource(std::string const& filename) {

		std::shared_ptr< R >  ressource = std::make_shared< R >();

		if (ressource->loadFromFile(_ressourceFolder + filename) == false)
			return false;
		_ressources[filename] = ressource;
		return true;
	}


	R*                getRessource(std::string const& filename) {

		if (_ressources[filename] == nullptr) {
			loadRessource(filename);
		}
		return _ressources[filename].get();
	}

public:

	std::string       getRessourceFolder() const {

		return _ressourceFolder;
	}

	void              setRessourceFolder(std::string const& foldername) {

		_ressourceFolder = foldername;
	}

private:

	std::string       _ressourceFolder;

private:

	std::map < std::string, std::shared_ptr< R >>        _ressources;

};

#endif                /* !___RESSOURCE_MANAGER_HPP___ */
