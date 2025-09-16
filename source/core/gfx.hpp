#ifndef GFX
#define GFX
#include "_myConst.h"
#include "header.h"
#include "systemFunctionUNIX.hpp"
#include "tools/LOGGER.hpp"

struct myGFXStruct {
  // Variables
  std::string title;
  sf::VideoMode resolution;
  sf::Vector2u _winResolutions;
  bool fullscreen;
  bool verticalSync;
  unsigned frameRateLimit;
  sf::ContextSettings contextSettings;
  std::vector<sf::VideoMode> videoModes;
};

class GraphicsSettings {
public:
  myGFXStruct _struct;

  GraphicsSettings() {
    _struct.title = myConst::app_name;
    _struct.verticalSync = false;
    _struct.resolution = sf::VideoMode::getDesktopMode();
    _struct.videoModes = sf::VideoMode::getFullscreenModes();
    _struct.fullscreen = true;
    _struct.frameRateLimit = 120;
    _struct.contextSettings.antiAliasingLevel = 0;
  }

  void setgfxsettings(const myGFXStruct gfx) { _struct = gfx; }
  const myGFXStruct getgfxsettings() { return _struct; }

  // save to file
  const bool saveToFile() {
    json j;
    std::filesystem::path path =
        ApplicationsFunctions::getAppConfigFolder() + AppFiles::config_window;

    // Check if the file exists
    if (!std::filesystem::exists(path)) {
      // Create the file if it doesn't exist
      std::ofstream ofs(path);
      if (!ofs) {
        Logger::logStatic("GFX::COULD NOT CREATE FILE",
                          "l:64 -> GFX::saveToFile()", logType::ERROR);
        return false;
      }
    }
    // Fill the object with data
    try {
      j["window"]["title"] = _struct.title;
      j["window"]["resolution"]["width"] = _struct.resolution.size.x;
      j["window"]["resolution"]["height"] = _struct.resolution.size.y;
      j["window"]["fullscreen"] = _struct.fullscreen;
      j["window"]["frameRateLimit"] = _struct.frameRateLimit;
      j["window"]["verticalSync"] = _struct.verticalSync;
      j["window"]["antialiasingLevel"] =
          _struct.contextSettings.antiAliasingLevel;
    } catch (json::type_error &e) {
      Logger::logStatic("GFX::JSON::TYPE_ERROR: " + std::string(e.what()),
                        "GFX::saveToFile()", logType::ERROR);
      return false;
    }
    std::ofstream ofs(path, std::ios::ate);

    // Check if the file opened
    if (!ofs.is_open()) {
      Logger::logStatic("GFX::COULD NOT SAVE TO FILE",
                        "l:71 -> GFX::saveToFile()", logType::ERROR);
      return false;
    }

    // Write the JSON to the file
    ofs << j.dump(4) << std::endl;

    // Close the file
    ofs.close();

    return true;
  }

  // load from file
  const bool loadFromFile() {
    // construct path to config file
    std::filesystem::path filePath =
        ApplicationsFunctions::getAppConfigFolder() + AppFiles::config_window;

    // open us file wz ifstream
    std::ifstream ifs(filePath);

    // check if file is open
    if (!ifs.is_open()) {
      Logger::logStatic("CANNOT OPEN FILE", "l:96 -> GFX::loadFromFile()",
                        logType::ERROR);
      return false;
    }

    // json - some nolhman stuff
    json j;
    try {
      ifs >> j;
    } catch (json::exception &e) {
      Logger::logStatic("GFX::JSON::PARSE_ERROR: " + std::string(e.what()),
                        "l:104 -> GFX()", logType::ERROR);
      return false;
    }
    ifs.close();

    // insert data from json to struct
    try {
      _struct.resolution.size.x = j["window"]["resolution"]["width"];
      _struct.resolution.size.y = j["window"]["resolution"]["height"];
      _struct.fullscreen = j["window"]["fullscreen"];
      _struct.frameRateLimit = j["window"]["frameRateLimit"];
      _struct.verticalSync = j["window"]["verticalSync"];
      _struct.contextSettings.antiAliasingLevel =
          j["window"]["antialiasingLevel"];
    } catch (json::type_error &e) { // catch json type errors
      Logger::logStatic("GFX::JSON::TYPE_ERROR: " + std::string(e.what()),
                        "l:113 -> GFX::loadFromFile()", logType::ERROR);
      // some arror in loading data from json
      return false;
    }
    // load success
    return true;
  };
};

#endif /* GFX */
