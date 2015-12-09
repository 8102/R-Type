#include          "SoundTrack.hh"

SoundTrack::SoundTrack() : sf::Music() {}

SoundTrack::~SoundTrack() {}

bool                  SoundTrack::loadFromFile(std::string const& filename) {

	return openFromFile(filename);
}
