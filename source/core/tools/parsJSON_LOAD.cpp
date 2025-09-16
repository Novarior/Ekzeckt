#include "parsJSON.hpp"

// load playes
const bool ParserJson::loadPlayer(Entity &player) { // open json file
  std::ifstream ifs(ApplicationsFunctions::getAppConfigFolder() +
                    AppFiles::config_playerdata);
  if (!ifs.is_open()) {
    printf("ERROR::PARSER::OPEN::PLAYER::FILE_NOT_OPEN\n   %s\n",
           AppFiles::config_playerdata);
    return false;
  }
  // load from json file

  return true;
}

// there big shit for loading your inveutory in game (unrelized :c
const bool
ParserJson::loadInventory(const std::shared_ptr<Inventory> &inventory) {
  // Проверка, что указатель на инвентарь не пустой
  if (!inventory) {
    printf("ERROR::PARSER::LOAD::INVENTORY::INVENTORY_IS_NULL\n");
    return false;
  }

  // Открытие файла
  std::ifstream ifs(ApplicationsFunctions::getAppConfigFolder() +
                    AppFiles::config_inventory);

  // // Проверка, что файл открылся
  // if (!ifs.is_open()) {
  //   printf("ERROR::PARSER::LOAD::INVENTORY::FILE_NOT_OPEN\n   %s\n",
  //          AppFiles::config_inventory);®´`´´E´
  //   return false;
  // }

  // // Парсим JSON из файла
  // try {
  //   json j;
  //   if (!(ifs >> j)) {
  //     throw std::runtime_error("Failed to parse JSON from file.");
  //   }

  //   // Проверка наличия ключа "inventory" и "items"
  //   if (!j.contains("inventory") || !j["inventory"].contains("items")) {
  //     throw std::runtime_error("Missing 'inventory' or 'items' in JSON.");
  //   }

  //   // Загружаем предметы
  //   for (auto &item : j["inventory"]["items"]) {
  //     if (!item["slot"].is_null()) { // Проверяем на null
  //       // Получаем предмет по ID
  //       Item *newItem =
  //           static_cast<Item>(ItemRegistry::getItem(item["unic ID"]));

  //       // Проверка, что предмет найден
  //       if (!newItem) {
  //         printf("ERROR::PARSER::LOAD::ITEM_NOT_FOUND::ID=%d\n",
  //                item["unic ID"].get<int>());
  //         continue; // Пропускаем этот предмет
  //       }

  //       // Добавляем предмет в инвентарь
  //       if (!inventory->addItem(std::shared_ptr<Item>(newItem))) {
  //         printf("ERROR::PARSER::LOAD::ITEM_ADD_FAILED::ID=%d\n",
  //                item["unic ID"].get<int>());
  //       }
  //     }
  //   }

  //   // Проверка наличия ключа "coins"
  //   if (!j["inventory"].contains("coins")) {
  //     throw std::runtime_error("Missing 'coins' in JSON.");
  //   }

  //   // Загружаем монеты
  //   if (j["inventory"]["coins"].contains("gold")) {
  //     inventory->getCoins().set_GoldCoinCouns(
  //         j["inventory"]["coins"]["gold"].get<int>());
  //   }

  //   if (j["inventory"]["coins"].contains("silver")) {
  //     inventory->getCoins().set_SilverCoinCouns(
  //         j["inventory"]["coins"]["silver"].get<int>());
  //   }

  //   if (j["inventory"]["coins"].contains("copper")) {
  //     inventory->getCoins().set_CopperCoinCouns(
  //         j["inventory"]["coins"]["copper"].get<int>());
  //   }

  // } catch (const std::exception &e) {
  //   Logger::logStatic("Cant load inventory: " + std::string(e.what()),
  //                     "CORE->PARS", logType::ERROR);
  //   printf("ERROR::PARSER::LOAD::INVENTORY::UNKNOWN_LINE\n   %s\n",
  //   e.what()); return false;
  // }

  return true;
}

// load  entitys
const bool
ParserJson::loadEntitys(std::vector<Entity *> &entitys) { // open json file

  return false;
}
// load key binds from json file
const bool ParserJson::loadKeyBinds(std::map<std::string, uint32_t> &keyBinds) {
  // merge strngs for path and put in ifstream
  std::ifstream ifs(ApplicationsFunctions::getAppConfigFolder() +
                    AppFiles::config_window);
  // we have this file?
  if (!ifs.is_open()) { // no?
                        // say about it in console and log
    printf("PARSER cant open file: %s\n",
           std::string(ApplicationsFunctions::getAppConfigFolder() +
                       AppFiles::config_window)
               .c_str());
    Logger::logStatic("Parcer cant open file: " +
                          ApplicationsFunctions::getAppConfigFolder() +
                          AppFiles::config_window,
                      "CORE->PARS", logType::ERROR);

    // go init this sheet with default keys
    keyBinds["Escape"] = kHIDUsage_KeyboardEscape;
    keyBinds["A"] = kHIDUsage_KeyboardA;
    keyBinds["C"] = kHIDUsage_KeyboardC;
    keyBinds["D"] = kHIDUsage_KeyboardD;
    keyBinds["E"] = kHIDUsage_KeyboardE;
    keyBinds["F"] = kHIDUsage_KeyboardF;
    keyBinds["Q"] = kHIDUsage_KeyboardQ;
    keyBinds["R"] = kHIDUsage_KeyboardR;
    keyBinds["S"] = kHIDUsage_KeyboardS;
    keyBinds["W"] = kHIDUsage_KeyboardW;
    keyBinds["X"] = kHIDUsage_KeyboardX;
    keyBinds["Z"] = kHIDUsage_KeyboardZ;
    keyBinds["1"] = kHIDUsage_Keyboard1;
    keyBinds["2"] = kHIDUsage_Keyboard2;
    keyBinds["3"] = kHIDUsage_Keyboard3;
    keyBinds["4"] = kHIDUsage_Keyboard4;
    keyBinds["5"] = kHIDUsage_Keyboard5;
    keyBinds["6"] = kHIDUsage_Keyboard6;
    keyBinds["7"] = kHIDUsage_Keyboard7;
    keyBinds["8"] = kHIDUsage_Keyboard8;
    keyBinds["9"] = kHIDUsage_Keyboard9;
    keyBinds["0"] = kHIDUsage_Keyboard0;
    keyBinds["Space"] = kHIDUsage_KeyboardSpacebar;
    keyBinds["Enter"] = kHIDUsage_KeyboardReturnOrEnter;
    keyBinds["BackSpace"] = kHIDUsage_KeyboardDeleteOrBackspace;
    keyBinds["Slash"] = kHIDUsage_KeyboardSlash;
    keyBinds["Tab"] = kHIDUsage_KeyboardTab;
    keyBinds["F1"] = kHIDUsage_KeyboardF1;
    keyBinds["F2"] = kHIDUsage_KeyboardF2;
    keyBinds["F3"] = kHIDUsage_KeyboardF3;
    // ok^_^ we did it sheeet
    // and now need save it
    saveKeyBinds(keyBinds);
  }
  // ok^ file was found
  // so
  // let load data)
  try {
    json j;   // json object?
    ifs >> j; // we put data to data)))
              // next we pars it
              // and put in our map

    // map is empty?
    if (!keyBinds.empty())
      keyBinds.clear(); // must be cleared

    // ok lets go load key binds from json bObject)
    for (auto &element : j["key_binds"].items()) { // we going cycles
      std::string name = element.key();
      int value = element.value();
      keyBinds[name] = value;
    }
  } catch (json::parse_error &e) { // yoMan we have error
    // say about it in console and log
    Logger::logStatic("JSON parse error: " + std::string(e.what()),
                      "CORE->PARS", logType::ERROR);
    return false; // again eror man but we cant do anything becoz file was
                  //  opened but have eroor(( check for format, type data, etc
  }
  ifs.close();
  return true;
}

// load noice data
const bool ParserJson::loadNoiceData(mmath::noiceData &data) {
  // Open the file
  std::ifstream ifs(ApplicationsFunctions::getAppConfigFolder() +
                    AppFiles::config_noicedata);

  // Check if the file is open
  if (!ifs.is_open()) {
    printf("ERROR::PARSER::OPEN::NOICEDATA::FILE_NOT_OPEN\n   %s\n",
           AppFiles::config_playerdata);
    return false;
  }

  // Parse the JSON from the file
  try {
    json j;
    ifs >> j;

    // Read the noise data from the JSON
    data.seed = j["noice"]["seed"];
    data.octaves = j["noice"]["octaves"];
    data.frequency = j["noice"]["frequency"];
    data.amplifire = j["noice"]["amplifire"];
    data.persistence = j["noice"]["persistence"];
    data.smoothMode = j["noice"]["smooth"];
  } catch (const std::exception &e) {
    printf("ERROR::PARSER::LOAD::NOICEDATA::UNKNOWN_LINE\n   %s\n", e.what());
    return false;
  }

  return true;
}

// loading volumes from window config file in vol
const bool ParserJson::loadSoundVolumes(VolumeCollector *data) {
  try {
    json j;
    // Open the file and load the JSON object from it
    std::ifstream ifs(ApplicationsFunctions::getAppConfigFolder() +
                      AppFiles::config_window);
    ifs >> j;

    // Create a temporary VolumeManager object
    VolumeCollector tempData;

    // Load the sound volumes into the temporary object
    int categoryIndex = 0;
    for (json::iterator it = j["sound_volumes"].begin();
         it != j["sound_volumes"].end(); ++it) {
      tempData.setCategoryVolume(static_cast<SoundCategory>(categoryIndex),
                                 it.value());
      categoryIndex++;
    }

    // Assign the temporary object to your main data object
    *data = tempData;
  } catch (const std::exception &e) {
    // catch exception
    Logger::logStatic("Cant load sound volumes: " + std::string(e.what()),
                      "CORE->PARS", logType::ERROR);
    return false;
  }
  return true;
}
