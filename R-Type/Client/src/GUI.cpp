#include "GUI.hh"
#include "GameEngine.hh"

GUI::GUI(Player const& player, sf::RenderWindow & window)
	:	_player(player), _win(window), _scoreTxt("0", *requestAssetManager.getFont("GUIFont.ttf"), 50),
		_score(0), _timeTxt("0:0", *requestAssetManager.getFont("GUIFont.ttf"), 50), _lifebar(), _energyBar(),
		_deadMask(), _weaponIconContainer(120.0f), _weaponIcon(100.0f)
{
	_lifebar.setTexture(*requestAssetManager.getTexture("lifebar.png"));
	_lifebar.setScale(sf::Vector2f(0.5f, 0.5f));
	_energyBar.setTexture(*requestAssetManager.getTexture("energybar.png"));
	_energyBar.setScale(sf::Vector2f(2.0f, 2.0f));
	_deadMask.setSize(sf::Vector2f(static_cast<float>(_win.getSize().x), static_cast<float>(_win.getSize().y)));
	_weaponIconContainer.setTexture(requestAssetManager.getTexture("weaponIconContainer.png"));
	_weaponIconContainer.setPosition(sf::Vector2f(100.0f, PLAY_HEIGHT - 100.0f));
	_weaponIconContainer.setOrigin(sf::Vector2f(_weaponIconContainer.getGlobalBounds().width / 2.0f, _weaponIconContainer.getGlobalBounds().height / 2.0f));
	_weaponIcon.setPosition(sf::Vector2f(0.0f, PLAY_HEIGHT / 9.0f * 7.0f));
	_weaponIcon.setTexture(requestAssetManager.getTexture("iconPlasmaCannon.png")); /**************/
	_weaponIcon.setTexture(requestAssetManager.getTexture("iconMap.jpg")); /**************/
}

GUI::~GUI()
{
}

void							GUI::drawUserInfo()
{
	sf::RectangleShape	life;
	sf::RectangleShape	energy;
	
	float						lifeRatio = static_cast<float>(_player.getLife().x) / static_cast<float>(_player.getLife().y);
	float						energyRatio = static_cast<float>(_player.getEnergy().x) / static_cast<float>(_player.getEnergy().y);

	if (_player.getLife().x <= 0)
	{
		if (_deadMask.getTexture() == nullptr) _deadMask.setTexture(requestAssetManager.getTexture("deadvision.png"));
		_win.draw(_deadMask);
	}
	_lifebar.setScale(sf::Vector2f(2.0f, 2.0f));
	_lifebar.setPosition(sf::Vector2f(_win.getSize().x / 8.0f, _win.getSize().y / 10.0f * 9.0f));
	_energyBar.setScale(sf::Vector2f(2.0f, 2.0f));
	_energyBar.setPosition(sf::Vector2f(_win.getSize().x / 8.0f, _win.getSize().y / 10.0f * 9.0f - _energyBar.getGlobalBounds().height * 1.5f));
	life.setSize(sf::Vector2f((_lifebar.getGlobalBounds().width / 20 * 19) * lifeRatio, _lifebar.getGlobalBounds().height / 10 * 8));
	life.setPosition(sf::Vector2f(_lifebar.getPosition().x, _lifebar.getPosition().y + 5));
	life.setFillColor(lifeRatio < 0.33 ? sf::Color(160, 0, 0) : (lifeRatio < 0.66 ? sf::Color(200, 120, 0) : sf::Color(0, 200, 0)));
	energy.setSize(sf::Vector2f((_energyBar.getGlobalBounds().width / 20 * 19) * energyRatio, _energyBar.getGlobalBounds().height / 10 * 6));
	energy.setPosition(sf::Vector2f(_energyBar.getPosition().x, _energyBar.getPosition().y + 5));
	energy.setFillColor(sf::Color(0, 50, 175));
	_win.draw(life);
	_win.draw(energy);
	_win.draw(_lifebar);
	_win.draw(_energyBar);
	_energyBar.setScale(sf::Vector2f(0.5f, 0.5f));
	_lifebar.setScale(sf::Vector2f(0.5f, 0.5f));
	_timeTxt.setPosition(sf::Vector2f(PLAY_WIDTH - _timeTxt.getGlobalBounds().width, 0.0f));
	_win.draw(_timeTxt);
	_scoreTxt.setPosition(sf::Vector2f(0.0f, 0.0f));
	_win.draw(_scoreTxt);
	_win.draw(_weaponIconContainer);
	_win.draw(_weaponIcon);
}

void								GUI::drawEnnemyInfo(ACharacter const & character)
{
	sf::RectangleShape	life;
	float							lifeRatio;

	lifeRatio = static_cast<float>(character.getLife().x) / static_cast<float>(character.getLife().y);
	_lifebar.setPosition(sf::Vector2f(character.getPosition().x +
		character.getGlobalBounds().width / 2 - _lifebar.getGlobalBounds().width / 2,
		character.getPosition().y - _lifebar.getGlobalBounds().height));
	life.setSize(sf::Vector2f((_lifebar.getGlobalBounds().width / 20 * 19) * lifeRatio, _lifebar.getGlobalBounds().height / 10 * 9));
	life.setPosition(_lifebar.getPosition());
	life.setFillColor(lifeRatio < 0.33 ? sf::Color(160, 0, 0) : (lifeRatio < 0.66 ? sf::Color(200, 150, 0) : sf::Color(0, 200, 0)));
	_win.draw(life);
	_win.draw(_lifebar);
}

void								GUI::drawPlayerInfo(ACharacter const & character)
{
	sf::RectangleShape	life;
	float							lifeRatio;

	lifeRatio = static_cast<float>(character.getLife().x) / static_cast<float>(character.getLife().y);
	_lifebar.setPosition(sf::Vector2f(character.getPosition().x +
		character.getGlobalBounds().width / 2 - _lifebar.getGlobalBounds().width / 2,
		character.getPosition().y - _lifebar.getGlobalBounds().height));
	life.setSize(sf::Vector2f((_lifebar.getGlobalBounds().width / 20 * 19) * lifeRatio, _lifebar.getGlobalBounds().height / 10 * 9));
	life.setPosition(_lifebar.getPosition());
	life.setFillColor(lifeRatio < 0.33 ? sf::Color(160, 0, 0) : (lifeRatio < 0.66 ? sf::Color(200, 120, 0) : sf::Color(0, 200, 0)));
	_win.draw(life);
	_win.draw(_lifebar);
}

void GUI::update()
{
	updateTime();
	_weaponIconContainer.rotate(1);
}

void									GUI::updateScore(unsigned int const & value)
{
	std::stringstream			ss;

	_score += value;
	ss << _score;
	_scoreTxt.setString(ss.str());
}

void GUI::updateTime()
{
	std::stringstream	ss;
	float						time = requestGameEngine.getTime();

	ss << std::setw(2) << std::setfill('0') << static_cast<int>(time / 60) << ":" << std::setw(2) << std::setfill('0') << static_cast<int>(time) % 60;
	_timeTxt.setString(ss.str());
}