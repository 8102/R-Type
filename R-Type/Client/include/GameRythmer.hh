#ifndef									___GAME_RYTHMER_HH___
# define								___GAME_RYTHMER_HH___

# include								"Client_graphicUtils.hh"
# include								"EnnemyFactory.hh"

class GameEngine;

class GameRythmer
{

public:

	GameRythmer(GameEngine& engine, std::string const& filename = "");
	~GameRythmer();

public:
	
	bool										start();
	void										stop();
	void										update();

public:

	void										setActionTime(std::string const& s);

	void										generateGameAsset(std::string const& s);

public:

	void										openGameMap();
	void										getNextActionBlock();
	
	template<typename T>
	sf::Vector2<T>					fillVector(std::string const& s) const {

		std::stringstream				ss;
		sf::Vector2<T>				v;

		ss.str(s.substr(0, s.find_first_of(';')));
		ss >> v.x;
		ss.clear();
		ss.str(s.substr(s.find_first_of(';') + 1, s.size()));
		ss >> v.y;
		return v;
	}

	template	<typename T>
	T											extractValue(std::string const& s) const {

		std::stringstream				ss;
		T										value;

		ss.str(s);
		ss >> value;
		return value;
	}

private:

	std::string							_fileName;
	std::fstream							_file;
	size_t									_offset;

private:

	std::vector<std::string>		_actions;
	float										_nextActionBlock;
	sf::Clock								_clock;
	float										_nextActionTime;

private:

	bool										_isReady;

};

#endif									/* !___GAME_RYTHMER_HH___ */