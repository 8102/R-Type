#ifndef              ___GAME_DECORE_HH___
# define             ___GAME_DECORE_HH___

# include            <string>
# include            <iostream>
# include            <SFML/Graphics.hpp>

# include            "AGameElement.hh"

class                GameDecor : public AGameElement /*public sf::Sprite*/
{
public:

	GameDecor(std::string const& filename, unsigned int Zindex = 0, sf::Color const& colorMask = sf::Color::White, bool repeated = true);
	GameDecor(sf::Texture const& texture, unsigned int Zindex = 0, bool repeated = false);
	GameDecor(GameDecor const& model);
	~GameDecor();

public:

	void              update();

public:

	void              setImage(sf::Image const& image);
	void              setCadre(sf::IntRect const& cadre);
	void              setVectors(sf::Vector2i const& vector, sf::Vector2f const& move = sf::Vector2f(0.0f, 0.0f));

	//  void              setZIndex(unsigned int zIndex);

public:

	sf::Image         getImage() const;
	sf::Texture       getTexture() const;
	sf::IntRect       getCadre() const;
	sf::Vector2i      getVector1() const;
	sf::Vector2f      getVector2() const;

	//  unsigned int      getZIndex() const;

private:

	sf::Image         _image;
	sf::Texture       _texture;
	sf::IntRect       _cadre;
	sf::Vector2i      _vector;
	sf::Vector2f      _movement;

	// private:
	//
	//   unsigned int      _zIndex;

};

#endif               /* !___GAME_DECORE_HH___ */
