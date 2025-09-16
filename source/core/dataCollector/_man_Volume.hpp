#ifndef AUDIO_MANAGER_HPP
#define AUDIO_MANAGER_HPP

#include "../tools/LOGGER.hpp"
#include <map>

enum class SoundCategory {
  vol_MASTER,
  vol_SFX,         // Звуковые эффекты
  vol_MUSIC,       // Музыка
  vol_AMBIENT,     // Фоновые звуки
  vol_ENTITY,      // Звуки, связанные с другими сущностями в игре
  vol_UI,          // Звуки пользовательского интерфейса
  vol_DIALOGUE,    // Диалоги или голосовые звуки
  vol_FOLEY,       // Звуки движения персонажей или предметов
  vol_WEAPON,      // Звуки оружия
  vol_ENVIRONMENT, // Звуки окружающей среды
  vol_COUNT
};

class VolumeCollector {
private:
  // Громкости
  std::map<SoundCategory, float> categoryVolumes = {
      {SoundCategory::vol_MASTER, 50.f},
      {SoundCategory::vol_SFX, 50.f},
      {SoundCategory::vol_MUSIC, 50.f},
      {SoundCategory::vol_AMBIENT, 50.f},
      {SoundCategory::vol_ENTITY, 50.f},
      {SoundCategory::vol_UI, 50.f},
      {SoundCategory::vol_DIALOGUE, 50.f},
      {SoundCategory::vol_FOLEY, 50.f},
      {SoundCategory::vol_WEAPON, 50.f},
      {SoundCategory::vol_ENVIRONMENT, 50.f}};

public:
  VolumeCollector() {
    // write log message what im here doing something
    Logger::logStatic("Start initilization VolumeCollector",
                      "VolumeCollector::VolumeCollector()");
  }
  // set value Volume by category
  void setCategoryVolume(SoundCategory category, float volume) {
    if (category != SoundCategory::vol_MASTER)
      categoryVolumes[category] =
          volume * categoryVolumes[SoundCategory::vol_MASTER] / 100.f;
    else
      categoryVolumes[category] = volume;
  }

  // get value Volume by category
  float getCategoryVolume(SoundCategory category) const {
    auto it = categoryVolumes.find(category);
    return it != categoryVolumes.end() ? it->second : 100.f;
  }

  // get all categories for next save to file
  const std::map<SoundCategory, float> getCategoryVolumes() const {
    return categoryVolumes;
  }

  // set all categories from other map
  void
  setCategoryVolumes(const std::map<SoundCategory, float> &categoryVolumes) {
    this->categoryVolumes = categoryVolumes;
  }
  // get size of map categoryVolumes
  const unsigned int getCategoriesSize() const {
    return static_cast<unsigned int>(SoundCategory::vol_COUNT);
  }
};

#endif // !AUDIO_MANAGER_HPP