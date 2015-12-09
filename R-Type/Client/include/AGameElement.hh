#ifndef         ___ABSTRACT_GAME_ELEMENT_HH___
# define        ___ABSTRACT_GAME_ELEMENT_HH___

# include        <SFML/Graphics.hpp>

# include       "Client_graphicUtils.hh"
# include       "CollisionManager.hh"

class                 AGameElement : public sf::Sprite
{
public:

	enum eType
	{
		None = 0,
		Neutral = 1,
		Friendly = 3,
		Ennemy = 5
	};

public:

	AGameElement(unsigned int zIndex = 0);
	AGameElement(sf::Texture const& texture, unsigned int zIndex = 0);
	AGameElement(AGameElement const& model);

	/*virtual*/ ~AGameElement() /*{}*/;

public:

	virtual void        update() = 0;

public:

	unsigned int        getZIndex() const;
	eType               getType() const;

public:

	void                setZIndex(unsigned int zIndex);
	void                setType(eType const& type);
	void                applyFilter(sf::Color const& c);

	bool                containsPoint(sf::Vector2i const& point);
	bool                collide(AGameElement const& gameElement) const;

	bool                isOutOfScreen() const;
	bool					hasPassed() const;

public:

	AGameElement&       operator=(AGameElement const& model);

protected:

	unsigned int        _zIndex;
	eType               _type;
};

AGameElement&         operator<(AGameElement& l, AGameElement& r);

#endif          /* !___ABSTRACT_GAME_ELEMENT_HH___ */
