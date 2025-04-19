#ifndef _MAN_TEXTURE
#define _MAN_TEXTURE

#include "../header.h"

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
  ITEMS_NULL,
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
  COINS_SILVER_NUGGET
};

// Вспомогательная структура для хранения пар TextureID -> строка
struct TextureIDMapping {
  static std::unordered_map<TextureID, std::string> idToStringMap;

  static void initialize() {
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
        {TextureID::ITEMS_NULL, "items_NULL"},
        {TextureID::ITEMS_STONE, "items_stone"},
        {TextureID::ITEMS_WOOD, "items_wood"},
        {TextureID::ITEMS_IRON_SWORD, "items_iron_sword"},
        {TextureID::ITEMS_BREAD, "items_bread"},
        {TextureID::ITEMS_LEATHER_ARMOR, "items_leather_armor"},
        {TextureID::ITEMS_HEALTH_POTION, "items_health_potion"},
        {TextureID::ITEMS_GOLD_COIN, "items_gold_coin"},
        {TextureID::ITEMS_POISON_SMALL_REGENERATION,
         "items_potion_small_regeneration"},
        {TextureID::INVENTORY_CELL_TEXTURE, "inventory_cell_texture"},
        {TextureID::COINS_GOLD_NUGGET, "coins_gold_nugget"},
        {TextureID::COINS_COPPER_NUGGET, "coins_copper_nugget"},
        {TextureID::COINS_SILVER_NUGGET, "coins_silver_nugget"}};
  }

  static std::string toString(TextureID id) {
    auto it = idToStringMap.find(id);
    if (it != idToStringMap.end()) {
      return it->second;
    } else {
      Logger::logStatic("Unknown TextureID encountered",
                        "TextureIDMapping::toString()", logType::ERROR);
      return "texture_null"; // Возвращаем дефолтное значение
    }
  }
};

class TextureManager {
public:
  // Метод для загрузки текстуры по паре ключ-значение (перечисление-путь)
  static bool loadTexture(TextureID textureID, const std::string &filePath) {
    std::string textureName = TextureIDMapping::toString(textureID);
    return loadTexture(textureName, filePath);
  }

  // Метод для загрузки текстуры (оригинальный)
  static bool loadTexture(const std::string &textureName,
                          const std::string &filePath) {
    if (m_textures.find(textureName) != m_textures.end()) {
      // Если текстура уже загружена, возвращаем true
      Logger::logStatic(textureName + " texture alrady loaded",
                        "TextureManager::loadTexture()", logType::INFO);
      return true;
    }

    sf::Texture texture;
    if (texture.loadFromFile(ApplicationsFunctions::get_resources_dir() +
                             filePath)) {
      // сохраняем текстуру в контейнер
      m_textures.emplace(textureName, std::move(texture));
      Logger::logStatic(textureName + " success load",
                        "TextureManager::loadTexture()",
                        logType::INFO); // Логируем успешную загрузку
      return true;
    } else {
      Logger::logStatic(textureName + " failed to load",
                        "TextureManager::loadTexture()",
                        logType::ERROR); // Логируем ошибку
      return false;
    }
  }

  // Метод для получения текстуры по перечислению
  static sf::Texture &getTexture(TextureID textureID) {
    std::string textureName = TextureIDMapping::toString(textureID);
    return getTexture(textureName);
  }

  // Метод для получения текстуры по имени (оригинальный)
  static sf::Texture &getTexture(const std::string &textureName) {
    if (m_textures.find(textureName) != m_textures.end()) {
      return m_textures[textureName];
    } else { // В случае отсутствия текстуры, логируем ошибку
      Logger::logStatic("Texture not found: " + textureName +
                            ", returning TEXTURE_NULL",
                        "TextureManager::getTexture()", logType::WARNING);

      // Проверяем, есть ли текстура NULL
      if (m_textures.find("texture_null") != m_textures.end()) {
        return m_textures["texture_null"];
      } else {
        // Если NULL текстуры нет, бросаем исключение
        Logger::logStatic("TEXTURE_NULL is also missing!",
                          "TextureManager::getTexture()", logType::ERROR);
        throw std::runtime_error("Critical error: Both requested texture and "
                                 "TEXTURE_NULL are missing.");
      }
    }
  }

  // Метод для проверки, существует ли текстура по перечислению
  static bool hasTexture(TextureID textureID) {
    std::string textureName = TextureIDMapping::toString(textureID);
    return hasTexture(textureName);
  }

  // Метод для проверки, существует ли текстура (оригинальный)
  static bool hasTexture(const std::string &textureName) {
    return m_textures.find(textureName) != m_textures.end();
  }

  ~TextureManager() { m_textures.clear(); }

  // Контейнер для хранения текстур (теперь это статический контейнер)
  static std::unordered_map<std::string, sf::Texture> m_textures;
};

// int main()
// {
//     TextureManager textureManager;

//     // Загружаем текстуру
//     textureManager.loadTexture("player", "path_to_player_texture.png");
//     textureManager.loadTexture("enemy", "path_to_enemy_texture.png");

//     // Получаем и используем текстуру для спрайта
//     if (textureManager.hasTexture("player")) {
//         sf::Sprite playerSprite;
//         playerSprite.setTexture(textureManager.getTexture("player"));
//         // Теперь можно использовать playerSprite
//     }

//     return 0;
// }

#endif /* _MAN_TEXTURE */
