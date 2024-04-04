#include "TextureCache.h"


#pragma region Constructor/Destructor
TextureCache* TextureCache::instance = nullptr;

TextureCache::TextureCache() {
}

TextureCache::~TextureCache() {
}
#pragma endregion

#pragma region Instance
TextureCache* TextureCache::GetInstance() {
	if (instance == nullptr)
		instance = new TextureCache();
	return instance;
}

#pragma endregion

#pragma region Methods
//<----------------------------------------------------------------------------------------------------------- needs testing 
sf::Texture& TextureCache::GetTexture(const std::string& pTextureAdress) {
	if (textures.contains(pTextureAdress)) {
		useCount[pTextureAdress]++;
	} else {
		textures[pTextureAdress] = std::shared_ptr<sf::Texture>();
		textures[pTextureAdress]->loadFromFile(pTextureAdress);
		useCount[pTextureAdress] = 0;
		useCount[pTextureAdress]++;
	}
	return (*(textures[pTextureAdress].get()));
}
//<----------------------------------------------------------------------------------------------------------- needs testing 
void TextureCache::DecreaseTextureCount(const std::string& pTextureAdress) {
	useCount[pTextureAdress]--;
	if (useCount[pTextureAdress] != 0)
		return;
	textures.erase(pTextureAdress);
	useCount.erase(pTextureAdress);
}
//<----------------------------------------------------------------------------------------------------------- needs testing 
#pragma endregion