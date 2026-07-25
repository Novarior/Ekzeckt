#ifndef _MAN_TEXTURE
#define _MAN_TEXTURE

#include "../header.h"
#include "../tools/LOGGER.hpp"


// Создаем перечисление для текстур, чтобы можно было использовать вместо
// строковых литералов
enum class TextureID {
	TEXTURE_NULL,
	TEXTURE_DEEP_OCEAN,
	TEXTURE_OCEAN,
	TEXTURE_SAND,
	TEXTURE_GRASS,
	TEXTURE_DIRT,
	TEXTURE_STONE,
	TEXTURE_SNOW,
	TEXTURE_PLAYER,
	TEXTURE_SLIME,
	// Текстуры интерфейса
	TEXTURE_BACKGROUND_LAY_1,
	TEXTURE_BACKGROUND_LAY_2,
	TEXTURE_BACKGROUND_LAY_3,
	// Текстуры предметов
	ITEMS_STONE,
	ITEMS_WOOD,
	ITEMS_IRON_SWORD,
	ITEMS_BREAD,
	ITEMS_LEATHER_ARMOR,
	ITEMS_HEALTH_POTION,
	ITEMS_GOLD_COIN,
	ITEMS_POISON_SMALL_REGENERATION,
	// Инвентарь
	INVENTORY_CELL_TEXTURE,
	// Монеты
	COINS_GOLD_NUGGET,
	COINS_COPPER_NUGGET,
	COINS_SILVER_NUGGET,
};

// Вспомогательная структура для хранения пар TextureID -> строка
struct TextureIDMapping {
	static std::unordered_map<TextureID, std::string> idToStringMap;

	static void initTextureIDMapping() {
		idToStringMap = {
			{TextureID::TEXTURE_NULL, "texture_null"},
			{TextureID::TEXTURE_DEEP_OCEAN, "texture_deep_ocean"},
			{TextureID::TEXTURE_OCEAN, "texture_ocean"},
			{TextureID::TEXTURE_SAND, "texture_sand"},
			{TextureID::TEXTURE_GRASS, "texture_grass"},
			{TextureID::TEXTURE_DIRT, "texture_dirt"},
			{TextureID::TEXTURE_STONE, "texture_stone"},
			{TextureID::TEXTURE_SNOW, "texture_snow"},
			{TextureID::TEXTURE_PLAYER, "texture_Player"},
			{TextureID::TEXTURE_SLIME, "texture_Slime"},
			{TextureID::TEXTURE_BACKGROUND_LAY_1, "texture_background_lay_1"},
			{TextureID::TEXTURE_BACKGROUND_LAY_2, "texture_background_lay_2"},
			{TextureID::TEXTURE_BACKGROUND_LAY_3, "texture_background_lay_3"},
			{TextureID::ITEMS_STONE, "items_stone"},
			{TextureID::ITEMS_WOOD, "items_wood"},
			{TextureID::ITEMS_IRON_SWORD, "items_iron_sword"},
			{TextureID::ITEMS_BREAD, "items_bread"},
			{TextureID::ITEMS_LEATHER_ARMOR, "items_leather_armor"},
			{TextureID::ITEMS_HEALTH_POTION, "items_health_potion"},
			{TextureID::ITEMS_GOLD_COIN, "items_gold_coin"},
			{TextureID::ITEMS_POISON_SMALL_REGENERATION, "items_potion_small_regeneration"},
			{TextureID::INVENTORY_CELL_TEXTURE, "inventory_cell_texture"},
			{TextureID::COINS_GOLD_NUGGET, "coins_gold_nugget"},
			{TextureID::COINS_COPPER_NUGGET, "coins_copper_nugget"},
			{TextureID::COINS_SILVER_NUGGET, "coins_silver_nugget"}};
	}

	static std::string toString(TextureID id) {
		auto it = idToStringMap.find(id);
		if (it != idToStringMap.end())
			return it->second;
		else
			return "texture_null";

	}
};

class TextureManager {
private:
	static inline sf::Image getDefaultNullTexture() {
		sf::Vector2u size(128, 128);
		sf::Image image(size, sf::Color::Black);
		unsigned int blockSize = 16;
		unsigned int blockX = 0;
		unsigned int blockY = 0;
		for (unsigned int x = 0; x < size.x; x++) {
			for (unsigned int y = 0; y < size.y; y++) {
				blockX = x / blockSize;
				blockY = y / blockSize;

				sf::Color color = ((blockX + blockY) % 2 == 0) ? sf::Color::Black : sf::Color(255, 0, 255);
				image.setPixel({x, y}, color);
			}
		}

		return image;
	}

public:
	static inline void initialize() {
		TextureIDMapping::initTextureIDMapping();
		initNULLTEXTURE();
	}

	static void initNULLTEXTURE() {
		sf::Texture tx;
		if (!tx.loadFromImage(getDefaultNullTexture()))
			throw std::runtime_error("Failed to create default null texture");
		m_textures.emplace(TextureIDMapping::toString(TextureID::TEXTURE_NULL), std::move(tx));
	}

	// load texture with using "textureID"
	static inline bool loadTexture(TextureID textureID, const std::string& filePath) {
		std::string textureName = TextureIDMapping::toString(textureID);
		if (textureName == "texture_null") {
			Logger::logStatic("ThrowBack TEXTURE_NAME: " + filePath, "TextureManager::loadTexture()", logType::LERROR);
			return false;
		}

		sf::Texture texture;
		if (texture.loadFromFile(AppFn::getPathResourcesDir().append(filePath))) {
			// emplase loaded texture 
			m_textures.emplace(textureName, std::move(texture));
			return true;
		} else {
			Logger::logStatic("failed to load: " + textureName, "TextureManager::loadTexture()", logType::LERROR); // Логируем ошибку
			return false;
		}
	}

	// load texture with using "textureName"
	static inline bool loadTexture(const std::string& textureName, const std::string& filePath) {
		if (m_textures.find(textureName) != m_textures.end()) {
			// if testure already exist, return true and log it
			Logger::logStatic("texture " + textureName + " already loaded", "TextureManager::loadTexture()", logType::LINFO);
			return true;
		}

		sf::Texture texture;
		if (texture.loadFromFile(AppFn::getPathResourcesDir().append(filePath))) {
			// emplase loaded texture 
			m_textures.emplace(textureName, std::move(texture));
			return true;
		} else {
			Logger::logStatic("failed to load: " + textureName, "TextureManager::loadTexture()", logType::LERROR); // Логируем ошибку
			return false;
		}
	}

	// Метод для получения текстуры по перечислению
	static inline sf::Texture& getTexture(TextureID textureID) {
		std::string textureName = TextureIDMapping::toString(textureID);

		if (m_textures.find(textureName) != m_textures.end()) {
			return m_textures[textureName];
		} else { // texture with "textureName" not exist, log this and return null
			Logger::logStatic("Texture not found: " + textureName + ", returning TEXTURE_NULL", "TextureManager::getTexture()", logType::LWARNING);
			return m_textures["texture_null"];
		}
	}

	//	get null texture
	static inline sf::Texture& getTexture() { return m_textures["texture_null"]; }

	// get texture with usage "textureName" as ref, if not exist will be get null texture
	static inline sf::Texture& getTexture(const std::string& textureName) {
		if (m_textures.find(textureName) != m_textures.end()) {
			return m_textures[textureName];
		} else { // texture with "textureName" not exist, log this and return null
			Logger::logStatic("Texture not found: " + textureName + ", returning TEXTURE_NULL", "TextureManager::getTexture()", logType::LWARNING);
			return m_textures["texture_null"];
		}
	}
	// check if some texture with ID already exist
	static inline bool hasTexture(TextureID textureID) {
		return m_textures.find(TextureIDMapping::toString(textureID)) != m_textures.end();
	}

	static inline bool hasTexture(const std::string& textureName) {
		return m_textures.find(textureName) != m_textures.end();
	}

	~TextureManager() { m_textures.clear(); }

	static std::unordered_map<std::string, sf::Texture> m_textures;
};

//	int main()
//	{
//		TextureManager textureManager;

//		// load some texture
//		textureManager.loadTexture("player", "path_to_player_texture.png");
//		textureManager.loadTexture("enemy", "path_to_enemy_texture.png");

//		sf::Sprite playerSprite;
// 
//		// get texture 
//		if (textureManager.hasTexture("player")) {
//			playerSprite.setTexture(textureManager.getTexture("player"));
//
//			// and now sprite ready to usage
//		}

//		return 0;
//	}

#endif /* _MAN_TEXTURE */
