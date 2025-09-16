#ifndef PARSJSON
#define PARSJSON

// #include "../../Content/ItemsStuff/Inventory.hpp"
#include "../../core/dataCollector/_man_Volume.hpp"
// #include "../../../entitys/entity.hpp"
// #include "../../../entitys/player.hpp"
// #include "../../../math/ProcessGenerationNoice.hpp"

class Gamedata;
class NodeViewer;

// The ParserJson class provides methods for loading and saving game data
// to/from a JSON file
class ParserJson {
public:
  ParserJson() {}
  virtual ~ParserJson() {}

  // // Save\Load player data
  // static const bool savePlayer(Entity *player); // Save player data
  // static const bool loadPlayer(Entity &player); // Load player data

  // // data for noice generators
  // static const bool loadNoiceData(mmath::noiceData &data); // Load noise data
  // static const bool saveNoiceData(mmath::noiceData data);  // Save noise data

  // // Save\Load inventory data
  // static const bool loadInventory(const std::shared_ptr<Inventory>
  // &inventory); static const bool saveInventory(const
  // std::shared_ptr<Inventory> &inventory);

  // // Save\Load entities data
  // static const bool saveEntitys(std::vector<Entity *> entitys);
  // static const bool loadEntitys(std::vector<Entity *> &entitys);

  // Save\Load key bindings
  static const bool saveKeyBinds(std::map<std::string, uint32_t> &keyBinds);
  static const bool loadKeyBinds(std::map<std::string, uint32_t> &keyBinds);

  // Save\Load other data
  static const bool loadSoundVolumes(VolumeCollector *data); // Load game data
  static const bool saveSoundVolumes(VolumeCollector *data); // Save game data
};

#endif /* PARSJSON */
