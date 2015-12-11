#ifndef              ___IINTERACTIVE_HH___
# define             ___IINTERACTIVE_HH___

# include            <SFML/Graphics.hpp>

class                IInteractive
{
public:

	IInteractive();

	virtual ~IInteractive() = 0;

public:

	virtual bool              onMouseClick(sf::Event const& event) = 0;
	virtual bool              onKeyPressed(sf::Event const& event) = 0;
	virtual bool              onClose(sf::Event const& event) = 0;

};

#endif               /* !___IINTERACTIVE_HH___ */
