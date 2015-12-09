#ifndef             ___SOUNDTRACK_HH___
# define            ___SOUNDTRACK_HH___

# include           <SFML/Audio/Music.hpp>

/*
**  Class SoundTrack :
**
**    Simple layer of sf::Music Class in order to be used in a RessourceManager<SoundTrack>
**    due to the openFromFIle method of sf::Music differents from loadFromFile() methods of other
**    types of assets.
*/

class SoundTrack : public sf::Music
{
public:

	SoundTrack();
	~SoundTrack();

public:

	bool          loadFromFile(std::string const& filename);
};

#endif              /* !___SOUNDTRACK_HH___ */
