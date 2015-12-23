#include "GameRythmer.hh"
#include	"GameEngine.hh"

GameRythmer::GameRythmer(GameEngine &engine, std::string const & filename)
	: _engine(engine), _fileName(filename), _file(), _offset(0), _actions(), _nextActionBlock(0.0f), _clock(), _nextActionTime(0.0f), _isReady(false)
{

}

GameRythmer::~GameRythmer()
{
}

bool GameRythmer::start()
{
	_file.open(_fileName);
	if (_file.is_open() == false)
		return false;
	std::cout << "OK" << std::endl;
	_clock.restart();
	_isReady = true;
	return true;
}

void GameRythmer::update()
{
	if (_clock.getElapsedTime().asSeconds() >= _nextActionTime)
	{
		for (auto it = _actions.begin(); it != _actions.end(); it++)
			generateGameAsset((*it));
		getNextActionBlock();
	}
}

void									GameRythmer::setActionTime(std::string const & s)
{
	std::stringstream			ss;

	ss << s.substr(s.find_first_of('[') + 1, s.find_last_of(']') - 1);
	ss >> _nextActionTime;
}

void									GameRythmer::generateGameAsset(std::string const & s)
{
	std::regex							format("(\\[(.*?)\\])");
	std::smatch						match;
	std::vector<std::string>	v;
	try {
		const std::sregex_token_iterator	end;
		for (std::sregex_token_iterator i(s.cbegin(), s.cend(), format); i != end; i++)
		{
			std::string sk = *i;
			if (std::regex_search(sk, match, format))
				v.push_back(match[2]);
		}
			if (v[0] == "Ennemy")
			requestGameEngine.addEnnemy(requestGameEngine._ennemyF.createEnnemy(v[1], fillVector<float>(v[2]), false));
		else if (v[0] == "Bonus")
		{
			if (v.size() >= 3)
				requestGameEngine.addBonus(*requestGameEngine._bonusF.createBonus(v[1], fillVector<float>(v[3]), extractValue<int>(v[2])));
		}
		else if (v[0] == "Decor")
		{
			GameDecor*			g = new GameDecor(std::string("./assets/sprites/") + std::string(v[1]), 1, sf::Color::Black, false);
			g->setPosition(fillVector< float >(v[2]));
			g->setVectors(fillVector<int>(v[3]), fillVector<float>(v[4]));
			requestGameEngine.addGameObject<GameDecor>(g);
		}
	}
	catch (std::exception e) { std::cerr << "# - " << e.what() << std::endl; }
}

void								GameRythmer::getNextActionBlock()
{
	std::string				line;

	_actions.clear();
	std::getline(_file, line);
	setActionTime(line);
	while (std::getline(_file, line) && line != "!EndBlock")
	{
		_actions.push_back(line);
	}
}
