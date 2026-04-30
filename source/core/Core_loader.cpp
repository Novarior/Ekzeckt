#include <fstream>
#include <ios>
#include <istream>
#include <sstream>

#include "Core.h"
#include "dataCollector/_man_Volume.hpp"
#include "dataCollector/_man_graphics.hpp"
#include "tools/LOGGER.hpp"

bool Core::cr_LoadData(nlohmann::json &_json_object,
                       gfx::myGFXStruct &_gfx_object,
                       std::map<std::string, uint32_t> &_keys_object,
                       gfx::VolumeCollector &_vol_object) {
  // mega load stuff here
  // read the object with data and paste it to structs
  try {
    Logger::logInfo("Loading config data...", "Core::cr_LoadData()");
    Logger::logInfo("JSON Object dump: " + _json_object.dump(4),
                    "Core::cr_LoadData()");
    if (!_json_object.contains("cr_window")) {
      Logger::logError("Missing cr_window section", "Core::cr_LoadData()");
      return false;
    }

    // Проверка наличия всех необходимых полей
    const auto &window = _json_object["cr_window"];
    if (!window.contains("title") || !window.contains("resolution") ||
        !window["resolution"].contains("width") ||
        !window["resolution"].contains("height")) {
      Logger::logError("Missing required window parameters",
                       "Core::cr_LoadData()");
      return false;
    }
    // Загрузка графических настроек с проверками
    _gfx_object.title = window["title"].get<std::string>();
    _gfx_object.resolution.size.x = window["resolution"]["width"].get<float>();
    _gfx_object.resolution.size.y = window["resolution"]["height"].get<float>();
    _gfx_object.fullscreen = window.value("fullscreen", false);
    _gfx_object.frameRateLimit = window.value("frameRateLimit", 60);
    _gfx_object.verticalSync = window.value("verticalSync", false);
    _gfx_object.contextSettings.antiAliasingLevel =
        window.value("antialiasingLevel", 0);

    // _localisations data
    // add later
    // _vol_object data
    if (_json_object.contains("cr_sound_volumes")) {
      const auto &sounds = _json_object["cr_sound_volumes"];
      _vol_object.setCategoryVolume(gfx::SoundCategory::vol_MASTER,
                                    sounds["master"].get<float>());
      _vol_object.setCategoryVolume(gfx::SoundCategory::vol_SFX,
                                    sounds["sfx"].get<float>());
      _vol_object.setCategoryVolume(gfx::SoundCategory::vol_MUSIC,
                                    sounds["music"].get<float>());
      _vol_object.setCategoryVolume(gfx::SoundCategory::vol_AMBIENT,
                                    sounds["ambient"].get<float>());
      _vol_object.setCategoryVolume(gfx::SoundCategory::vol_ENTITY,
                                    sounds["entity"].get<float>());
      _vol_object.setCategoryVolume(gfx::SoundCategory::vol_UI,
                                    sounds["ui"].get<float>());
      _vol_object.setCategoryVolume(gfx::SoundCategory::vol_DIALOGUE,
                                    sounds["dialogue"].get<float>());
      _vol_object.setCategoryVolume(gfx::SoundCategory::vol_FOLEY,
                                    sounds["foley"].get<float>());
      _vol_object.setCategoryVolume(gfx::SoundCategory::vol_WEAPON,
                                    sounds["weapon"].get<float>());
      _vol_object.setCategoryVolume(gfx::SoundCategory::vol_ENVIRONMENT,
                                    sounds["environment"]);
    }
    // load keybinds
    // Проверяем, что секция существует
    if (_json_object.contains("cr_keybinds")) {
      for (const auto &[key, value] : _json_object["cr_keybinds"].items()) {
        if (!value.is_null()) {
          _keys_object[key] = value.get<uint32_t>();
          Logger::logInfo("Loaded keybind: " + key + " = " +
                              std::to_string(value.get<uint32_t>()),
                          "Core::cr_LoadData()");
        }
      }
    }
  } catch (json::type_error &e) { // catch json type errors
    Logger::logError("JSON::TYPE_ERROR: " + std::string(e.what()),
                     "Core::cr_LoadData()");
    // some arror in loading data from json
    return false;
  }
  return true; // parse and past success
}

// mega save stuff here
bool Core::cr_SaveData(gfx::myGFXStruct &_gfx_object,
                       std::map<std::string, uint32_t> &_keys_object,
                       gfx::VolumeCollector &_vol_object) {
  // save all data to json object
  // construct path to config file
  std::filesystem::path filePath = ApplicationsFunctions::getAppConfigFolder() +
                                   "save" + AppFiles::config_window;

  // open us file wz ifstream
  std::ifstream ifs(filePath);
  // check if file is open
  if (!ifs.is_open()) {
    Logger::logError("CANNOT OPEN FILE", "l:96 -> GFX::loadFromFile()");
    return false;
  }
  // create json object
  json js;
  // next we collect all data from structs
  // and writw to json object
  try {
    js["cr_window"]["title"] = _gfx_object.title;

    // after that write to file
    std::ofstream ofs(filePath);
    // check if file was opened
    if (!ofs.is_open()) {
      ofs << js.dump(4); // write data to file
      ofs.close();
    } else {
      Logger::logError("CANNOT OPEN FILE", "l:113 -> GFX::loadFromFile()");
      return false;
    }
  } catch (json::type_error &e) { // catch json type errors
    Logger::logError("GFX::JSON::TYPE_ERROR: " + std::string(e.what()),
                     "l:113 -> GFX::loadFromFile()");
    // some arror in loading data from json
    return false;
  }
  // load success
  return true;
};
