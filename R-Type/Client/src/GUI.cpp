#include "GUI.hh"
#include "GameEngine.hh"

GUI::GUI(Player const& player, sf::RenderWindow & window)
	: _player(player), _win(window), _score("", *requestAssetManager.getFont("GUIFont.ttf"), 50), _lifebar(), _energyBar(), _deadMask()
{
	_lifebar.setTexture(*requestAssetManager.getTexture("lifebar.png"));
	_lifebar.setScale(sf::Vector2f(0.5f, 0.5f));
	_energyBar.setTexture(*requestAssetManager.getTexture("energyBar.png"));
	_energyBar.setScale(sf::Vector2f(2.0f, 2.0f));
	_deadMask.setSize(sf::Vector2f(static_cast<float>(_win.getSize().x), static_cast<float>(_win.getSize().y)));
}

GUI::~GUI()
{
}

void							GUI::drawUserInfo()
{
	sf::RectangleShape	life;
	sf::RectangleShape	energy;
	float						lifeRatio = static_cast<float>(_player.getLife().x) / static_cast<float>(_player.getLife().y);

	if (_player.getLife().x <= 0)
	{
		if (_deadMask.getTexture() == nullptr) _deadMask.setTexture(requestAssetManager.getTexture("deadvision.png"));
		_win.draw(_deadMask);
	}
	_lifebar.setScale(sf::Vector2f(2.0f, 2.0f));
	_lifebar.setPosition(sf::Vector2f(_win.getSize().x / 8.0f, _win.getSize().y / 10.0f * 9.0f));
	_energyBar.setPosition(sf::Vector2f(_win.getSize().x / 8.0f, _win.getSize().y / 10.0f * 9.0f - _energyBar.getGlobalBounds().height * 1.5f));
	life.setSize(sf::Vector2f((_lifebar.getGlobalBounds().width / 20 * 19) * lifeRatio, _lifebar.getGlobalBounds().height / 10 * 8));
	life.setPosition(sf::Vector2f(_lifebar.getPosition().x, _lifebar.getPosition().y + 5));
	life.setFillColor(lifeRatio < 0.33 ? sf::Color(160, 0, 0) : (lifeRatio < 0.66 ? sf::Color(200, 120, 0) : sf::Color(0, 200, 0)));
	energy.setSize(sf::Vector2f((_energyBar.getGlobalBounds().width / 20 * 19) * lifeRatio, _energyBar.getGlobalBounds().height / 10 * 6));
	energy.setPosition(sf::Vector2f(_energyBar.getPosition().x, _energyBar.getPosition().y + 5));
	energy.setFillColor(sf::Color(0, 50, 175));
	_win.draw(life);
	_win.draw(energy);
	_win.draw(_lifebar);
	_win.draw(_energyBar);
	_energyBar.setScale(sf::Vector2f(0.5f, 0.5f));
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
