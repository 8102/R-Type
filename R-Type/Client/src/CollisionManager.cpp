#include            "CollisionManager.hh"

CollisionManager::CollisionManager() {}

CollisionManager::~CollisionManager() {

	for (auto it = _bitmaskLibrary.begin(); it != _bitmaskLibrary.end(); it++)
		delete[] it->second;
}

sf::Uint8           CollisionManager::getPixel(sf::Uint8 const* mask, sf::Texture const* texture, sf::Vector2u const& position) {

	size_t            pixelPosition = 0;
	if (mask == nullptr || position.x > texture->getSize().x || position.y > texture->getSize().y)
		return 0;
	pixelPosition = position.x + position.y * texture->getSize().x;
	pixelPosition = (pixelPosition >= texture->getSize().x * texture->getSize().y ? texture->getSize().x * texture->getSize().y - 1 : pixelPosition);
	return mask[pixelPosition];
}

sf::Uint8*          CollisionManager::createMaskFromTexture(sf::Texture const* texture, sf::Image const& image) {

	sf::Uint8*        mask = new sf::Uint8[texture->getSize().x * texture->getSize().y];

	for (unsigned int y = 0; y < texture->getSize().y; y++)
		for (unsigned int x = 0; x < texture->getSize().x; x++)
			mask[y * texture->getSize().x + x] = image.getPixel(x, y).a;
	_bitmaskLibrary[texture] = mask;
	return mask;
}

sf::Uint8*          CollisionManager::getTextureMask(sf::Texture const* texture) {

	sf::Uint8*        result = nullptr;
	auto it = _bitmaskLibrary.find(texture);
	if (it == _bitmaskLibrary.end()) {
		sf::Image image = texture->copyToImage();
		result = createMaskFromTexture(texture, image);
	}
	else return it->second;
	return result;
}

bool                CollisionManager::CheckCollision(sf::Sprite const& objectA, sf::Sprite const& objectB, sf::Uint8 const& alphaLimit) {

	sf::FloatRect     intersection;

	if (objectA.getGlobalBounds().intersects(objectB.getGlobalBounds(), intersection)) {
		sf::IntRect subRectA = objectA.getTextureRect();
		sf::IntRect subRectB = objectB.getTextureRect();
		sf::Uint8*  maskA = getTextureMask(objectA.getTexture());
		sf::Uint8*  maskB = getTextureMask(objectB.getTexture());

		for (auto i = intersection.left; i < intersection.left + intersection.width; i++)
			for (auto j = intersection.top; j < intersection.top + intersection.height; j++) {

				sf::Vector2f    vectorA = objectA.getInverseTransform().transformPoint(i, j);
				sf::Vector2f    vectorB = objectB.getInverseTransform().transformPoint(i, j);

				if (vectorA.x > 0 && vectorA.y > 0 && vectorB.x > 0 && vectorB.y > 0 &&
					vectorA.x < subRectA.width && vectorA.y < subRectA.height &&
					vectorA.x < subRectB.width && vectorB.y < subRectB.height &&
					getPixel(maskA, objectA.getTexture(), sf::Vector2u(static_cast<unsigned int>(vectorA.x + subRectA.left), static_cast<unsigned int>(vectorA.y + subRectA.top))) > alphaLimit &&
					getPixel(maskB, objectB.getTexture(), sf::Vector2u(static_cast<unsigned int>(vectorB.x + subRectB.left), static_cast<unsigned int>(vectorB.y + subRectB.top))) > alphaLimit)
					return true;
			}
	}
	return false;
}
