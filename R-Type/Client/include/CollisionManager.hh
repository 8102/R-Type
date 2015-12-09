#ifndef                    ___COLLISION_MANAGER_HH___
# define                   ___COLLISION_MANAGER_HH___

# include                  <SFML/Graphics.hpp>
# include                  "Client_graphicUtils.hh"

class                       CollisionManager
{

public:

	CollisionManager();
	~CollisionManager();

public:

	sf::Uint8                 getPixel(sf::Uint8 const* mask, sf::Texture const* texture, sf::Vector2u const& position);
	sf::Uint8*                getTextureMask(sf::Texture const* texture);
	sf::Uint8*                createMaskFromTexture(sf::Texture const* texture, sf::Image const& image);

public:

	bool                      CheckCollision(sf::Sprite const& objectA, sf::Sprite const& objectB, sf::Uint8 const& alphaLimit = 0);

private:

	std::map<const sf::Texture*, sf::Uint8*>  _bitmaskLibrary;

};

#endif                     /* !___COLLISION_MANAGER_HH___ */
