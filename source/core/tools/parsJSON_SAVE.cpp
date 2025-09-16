#include "parsJSON.hpp"

// SAVES
const bool ParserJson::savePlayer(Entity *player) { // save player
  // check if player is not null
  if (player == nullptr) {
    Logger::logStatic("Cant save player: player is null", "CORE->PARS",
                      logType::ERROR);
    printf("ERROR::PARSER::SAVE::PLAYER::PLAYER_IS_NULL\n");
    return false;
  }
  // save player
  json j;
  j["player"]["attribute"]["damage"] =
      player->getAttributes()->getAttributes().damage;
  j["player"]["attribute"]["experience"] =
      player->getAttributes()->getAttributes().experience;
  j["player"]["attribute"]["experience_for_level"] =
      player->getAttributes()->getAttributes().experience_for_level;
  j["player"]["attribute"]["health"] =
      player->getAttributes()->getAttributes().health;
  j["player"]["attribute"]["level"] =
      player->getAttributes()->getAttributes().level;
  j["player"]["attribute"]["mana"] =
      player->getAttributes()->getAttributes().mana;
  j["player"]["attribute"]["max_health"] =
      player->getAttributes()->getAttributes().max_health;
  j["player"]["attribute"]["max_mana"] =
      player->getAttributes()->getAttributes().max_mana;
  j["player"]["attribute"]["regeneration_health"] =
      player->getAttributes()->getAttributes().regeneration_health;
  j["player"]["attribute"]["regeneration_mana"] =
      player->getAttributes()->getAttributes().regeneration_mana;
  j["player"]["attribute"]["some_points"] =
      player->getAttributes()->getAttributes().some_points;

  j["player"]["position"]["x"] = player->e_getPosition().x;
  j["player"]["position"]["y"] = player->e_getPosition().y;
  j["player"]["entity_uid"] = player->e_getID();
  j["player"]["isAlive"] = player->e_isAlive();

  // Write the JSON object to the file
  try {
    std::ofstream ofs(ApplicationsFunctions::getDocumentsAppFolder() +
                      AppFiles::config_playerdata);
    ofs << std::setw(4) << j;
  } catch (const std::exception &e) {
    Logger::logStatic("Cant save player: " + std::string(e.what()),
                      "CORE->PARS", logType::ERROR);
    printf("ERROR::PARSER::SAVE::PLAYER::FILE_NOT_OPEN\n   %s\n",
           AppFiles::config_playerdata);
    return false;
  }

  return true;
}

const bool
ParserJson::saveInventory(const std::shared_ptr<Inventory> &inventory) {
  // Проверка, что указатель на инвентарь не пустой
  if (!inventory) {
    std::cerr << "ERROR::PARSER::SAVE::INVENTORY::INVENTORY_IS_NULL"
              << std::endl;
    return false;
  }

  // Создаем JSON-объект
  json j;

  try {
    // Сохраняем информацию об инвентаре
    j["inventory"]["size"] = inventory->getTotalSlots();
    j["inventory"]["info"] = "Static inventory size data"; // Уточняющая строка

    // Ссылаемся на инвентарь для удобства
    const auto &invArray = inventory->getInventoryArray();
    int slot = 0;

    // Получаем предмет-затычку из реестра
    auto nullItem = ItemRegistry::getItem(0);

    // Сохраняем предметы
    for (const auto &row : invArray) {
      for (const auto &item : row) {
        // Пропускаем предмет-затычку
        if (item && item != nullItem) {
          // Сохраняем шаблон предмета
          j["inventory"]["items"][slot]["template"] = "Item";

          // Сохраняем данные предмета
          j["inventory"]["items"][slot]["data"]["slot"] = slot;
          j["inventory"]["items"][slot]["data"]["name"] = item->getName();
          j["inventory"]["items"][slot]["data"]["amount"] = item->getAmount();
          j["inventory"]["items"][slot]["data"]["price"]["Gold"] =
              item->getPrice().get_GoldCointCount();
          j["inventory"]["items"][slot]["data"]["price"]["Silver"] =
              item->getPrice().get_SilverCointCount();
          j["inventory"]["items"][slot]["data"]["price"]["Copper"] =
              item->getPrice().get_CopperCointCount();
          j["inventory"]["items"][slot]["data"]["stackable"] =
              item->isStackable();
          j["inventory"]["items"][slot]["data"]["usable"] = item->isUsable();
          j["inventory"]["items"][slot]["data"]["unic ID"] = item->getID();
        }
        slot++;
      }
    }

    // Сохраняем монеты
    j["inventory"]["coins"]["gold"] =
        inventory->getCoins().get_GoldCointCount();
    j["inventory"]["coins"]["silver"] =
        inventory->getCoins().get_SilverCointCount();
    j["inventory"]["coins"]["copper"] =
        inventory->getCoins().get_CopperCointCount();
  } catch (const std::exception &e) {
    std::cerr << "ERROR::PARSER::SAVE::INVENTORY::JSON_CREATION_FAILED: "
              << e.what() << std::endl;
    return false;
  }

  // Сохраняем JSON в файл
  try {
    std::string filePath = ApplicationsFunctions::getDocumentsAppFolder() +
                           AppFiles::config_inventory;
    std::ofstream ofs(filePath, std::ios::out | std::ios::trunc);
    if (!ofs.is_open()) {
      throw std::ios_base::failure("Failed to open file: " + filePath);
    }

    // Записываем JSON в файл с отступами
    ofs << std::setw(4) << j;
    ofs.close();
  } catch (const std::exception &e) {
    Logger::logStatic("Cant save inventory: " + std::string(e.what()),
                      "CORE->PARS", logType::ERROR);
    std::cerr << "ERROR::PARSER::SAVE::INVENTORY::FILE_WRITE_FAILED: "
              << e.what() << std::endl;
    return false;
  }

  return true;
}

const bool
ParserJson::saveEntitys(std::vector<Entity *> entitys) { // save entitys
  // Create a JSON object
  json j;

  // Save entities
  size_t i = 0;
  for (const auto &entity : entitys) {
    // Check entity if null, is null continue
    if (entity == nullptr || entity->e_isAlive() == false)
      continue;

    auto &entity_js = j["entity list"][i];
    entity_js["ID_record"] = i;
    entity_js["entity_uid"] = entity->e_getID();
    entity_js["position"]["x"] = entity->e_getPosition().x;
    entity_js["position"]["y"] = entity->e_getPosition().y;
    // Save entity attributes
    const auto &attributes = entity->getAttributes()->getAttributes();
    entity_js["attributes"]["hp"] = attributes.health;
    entity_js["attributes"]["max_hp"] = attributes.max_health;
    entity_js["attributes"]["level"] = attributes.level;
    i++;
  }

  // Write the JSON object to the file
  try {
    std::ofstream ofs(ApplicationsFunctions::getDocumentsAppFolder() +
                      AppFiles::config_entitydata);
    ofs << std::setw(4) << j;
  } catch (const std::exception &e) {
    std::stringstream ss;
    ss << "Pars can't save entities"
       << ApplicationsFunctions::getDocumentsAppFolder()
       << AppFiles::config_entitydata;
    Logger::logStatic(ss.str(), "CORE->PARS", logType::ERROR);
    printf("ERROR::PARSER::SAVE::ENTITYS::FILE_NOT_OPEN\n   %s\n",
           AppFiles::config_entitydata);
    return false;
  }

  return true;
}
const bool
ParserJson::saveNoiceData(mmath::noiceData _dataNoice) { // save noicedata
  // Create a JSON object
  json j;
  j["noice"] = {{"seed", _dataNoice.seed},
                {"octaves", _dataNoice.octaves},
                {"frequency", _dataNoice.frequency},
                {"amplifire", _dataNoice.amplifire},
                {"persistence", _dataNoice.persistence},
                {"smooth", _dataNoice.smoothMode},
                {"mapSizeX", _dataNoice.mapSizeX},
                {"mapSizeY", _dataNoice.mapSizeY},
                {"fast Mode", _dataNoice.fastMode}};

  // Write the JSON object to the file
  try {
    std::ofstream ofs(ApplicationsFunctions::getDocumentsAppFolder() +
                      AppFiles::config_noicedata);
    ofs << std::setw(4) << j;
  } catch (const std::exception &e) {
    Logger::logStatic("Cant save noice data: " + std::string(e.what()),
                      "CORE->PARS", logType::ERROR);
    printf("ERROR::PARSER::OPEN::GAMEDATA::FILE_NOT_OPEN\n   %s\n",
           AppFiles::config_noicedata);
    return false;
  }

  return true;
}
const bool ParserJson::saveKeyBinds(
    std::map<std::string, uint32_t> &keyBinds) { // save keybinds
  // Create a JSON object
  json j;
  for (const auto &i : keyBinds) {
    j["key_binds"][i.first] = i.second;
  }

  // Write the JSON object to the file
  try {
    std::ofstream ofs(ApplicationsFunctions::getDocumentsAppFolder() +
                      AppFiles::config_window);
    ofs << std::setw(4) << j;
  } catch (const std::exception &e) {
    std::stringstream ss;
    ss << "Pars can't save keybinds"
       << ApplicationsFunctions::getDocumentsAppFolder()
       << AppFiles::config_window;
    Logger::logStatic(ss.str(), "CORE->PARS", logType::ERROR);
    printf("ERROR::PARSER::SAVE::KEYBINDS::FILE_NOT_OPEN\n   %s\n",
           AppFiles::config_window);
    return false;
  }

  return true;
}

const bool ParserJson::saveSoundVolumes(
    VolumeCollector *data) { // save sound volumes from VolumeManager class
  // Write the JSON object to the file
  try {
    json j;
    // Save the sound volumes to the JSON object
    for (const auto &category : data->getCategoryVolumes()) {
      j["sound_volumes"][static_cast<int>(category.first)] = category.second;
    }
    // Write the JSON object to the file
    std::ofstream ofs(ApplicationsFunctions::getDocumentsAppFolder() +
                      AppFiles::config_window);
    ofs << std::setw(4) << j;
  } catch (const std::exception &e) {
    // catch exception
    Logger::logStatic("Cant save sound volumes: " + std::string(e.what()),
                      "CORE->PARS", logType::ERROR);
    printf("ERROR::PARSER::SAVE::SOUNDVOLUMES::FILE_NOT_OPEN\n   %s\n",
           AppFiles::config_window);
    return false;
  }

  return true;
}
