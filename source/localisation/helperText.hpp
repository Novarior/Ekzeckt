#ifndef HELPERTEXT
#define HELPERTEXT

// здесь все тектовые наименование (названия) для всех элементов
// также служат для подсказок действий для какихто кнопок

// также учитывается что текстовые наименования могут быть на разных языках
// поэтому важно чтобы они были в отдельном файле
// и было легко их заменить на другой язык

#include "../core/header.h"
#include <string>

namespace helperText {
enum class Language { ENG, RUS };

// абстрактный класс которы хранит текущий выбраный язык
// также есть переменная (строчкая и булиевая) которая хранит то что язык
// кастомный
class Localization {
private:
  static nlohmann::json loadedJson;
  static std::string currentFilePath;

  // Метод для загрузки JSON-файла, если он не был загружен ранее
  static bool loadLocalizationFile(const std::string &filename);

public:
  // Загружает локализацию в зависимости от языка
  static bool initializeLocalization(Language language);
  static std::string getLocalizedString(const std::string &category,
                                        const std::string &key,
                                        const std::string &defaultValue);
};

// Структура с текстами для кнопок
struct Button {
  static std::string BUTTON_PLAY;
  static std::string BUTTON_OPTIONS;
  static std::string BUTTON_EXIT;
  static std::string BUTTON_BACK;
  static std::string BUTTON_APPLY;
  static std::string BUTTON_CANCEL;
  static std::string BUTTON_SAVE;
  static std::string BUTTON_LOAD;
  static std::string BUTTON_NEW_GAME;
  static std::string BUTTON_CONTINUE;
  static std::string BUTTON_NOICE_EDITOR;
  static std::string BUTTON_PM_GENERATE;
  static std::string BUTTON_PM_PAUSE;
  static std::string BUTTON_DEBUG_ROOM_STATE;

  static void initializeLocalization(Language language) {
    Localization localization;
    if (localization.initializeLocalization(language)) {
      BUTTON_PLAY = localization.getLocalizedString("BUTTONS", "LOCAL_PLAY",
                                                    "@Play Text");
      BUTTON_PM_PAUSE = localization.getLocalizedString(
          "BUTTONS", "LOCAL_PM_PAUSE", "@Pause");
      BUTTON_PM_GENERATE = localization.getLocalizedString(
          "BUTTONS", "LOCAL_PM_GENERATE", "@Generate");
      BUTTON_OPTIONS = localization.getLocalizedString(
          "BUTTONS", "LOCAL_OPTIONS", "@Options Text");
      BUTTON_EXIT = localization.getLocalizedString("BUTTONS", "LOCAL_EXIT",
                                                    "@Exit Text");
      BUTTON_BACK = localization.getLocalizedString("BUTTONS", "LOCAL_BACK",
                                                    "@Back Text");
      BUTTON_APPLY = localization.getLocalizedString("BUTTONS", "LOCAL_APPLY",
                                                     "@Apply Text");
      BUTTON_CANCEL = localization.getLocalizedString("BUTTONS", "LOCAL_CANCEL",
                                                      "@Cancel Text");
      BUTTON_SAVE = localization.getLocalizedString("BUTTONS", "LOCAL_SAVE",
                                                    "@Save Text");
      BUTTON_LOAD = localization.getLocalizedString("BUTTONS", "LOCAL_LOAD",
                                                    "@Load Text");
      BUTTON_NEW_GAME = localization.getLocalizedString(
          "BUTTONS", "LOCAL_NEW_GAME", "@New Game Text");
      BUTTON_CONTINUE = localization.getLocalizedString(
          "BUTTONS", "LOCAL_CONTINUE", "@Continue Text");
      BUTTON_NOICE_EDITOR = localization.getLocalizedString(
          "BUTTONS", "LOCAL_NOICE_EDITOR", "@Noice Editor Text");
#if __MDEBUG__ == true
      BUTTON_DEBUG_ROOM_STATE = localization.getLocalizedString(
          "BUTTONS", "LOCAL_DRS", "@Debug ROOM");
#endif
    }
  }
};

// Структура с текстами для громкости
struct VolumeTexts {
  static std::string VOL_MASTER;
  static std::string VOL_SFX;
  static std::string VOL_MUSIC;
  static std::string VOL_AMBIENT;
  static std::string VOL_ENTITYSFX;
  static std::string VOL_UI_VOL;
  static std::string VOL_DIALOGUE_VOL;
  static std::string VOL_FOLEYVOL;
  static std::string VOL_WEAPONVOL;
  static std::string VOL_ENVIRONMENTVOL;

  static void initializeLocalization(Language language) {
    Localization localization;

    if (localization.initializeLocalization(language)) {
      VOL_MASTER = localization.getLocalizedString(
          "AUDIO_OPTIONS", "LOCAL_MASTER", "@Master Volume");
      VOL_SFX = localization.getLocalizedString("AUDIO_OPTIONS", "LOCAL_SFX",
                                                "@SFX Volume");
      VOL_MUSIC = localization.getLocalizedString(
          "AUDIO_OPTIONS", "LOCAL_MUSIC", "@Music Volume");
      VOL_AMBIENT = localization.getLocalizedString(
          "AUDIO_OPTIONS", "LOCAL_AMBIENT", "@Ambient Volume");
      VOL_ENTITYSFX = localization.getLocalizedString(
          "AUDIO_OPTIONS", "LOCAL_ENTITYSFX", "@Entity SFX Volume");
      VOL_UI_VOL = localization.getLocalizedString(
          "AUDIO_OPTIONS", "LOCAL_UI_VOL", "@UI Volume");
      VOL_DIALOGUE_VOL = localization.getLocalizedString(
          "AUDIO_OPTIONS", "LOCAL_DIALOGUE_VOL", "@Dialogue Volume");
      VOL_FOLEYVOL = localization.getLocalizedString(
          "AUDIO_OPTIONS", "LOCAL_FOLEYVOL", "@Foley Volume");
      VOL_WEAPONVOL = localization.getLocalizedString(
          "AUDIO_OPTIONS", "LOCAL_WEAPONVOL", "@Weapon Volume");
      VOL_ENVIRONMENTVOL = localization.getLocalizedString(
          "AUDIO_OPTIONS", "LOCAL_ENVIRONMENTVOL", "@Environment Volume");
    }
  }
};

// Структура с текстами для настроек
struct SettingsTexts {
  static std::string TEXT_ON;
  static std::string TEXT_OFF;
  static std::string TEXT_RESOLUTION;
  static std::string TEXT_FULLSCREEN;
  static std::string TEXT_VSYNC;
  static std::string TEXT_CONTROLS;
  static std::string TEXT_AUDIO;
  static std::string TEXT_ANTIALIASING;
  static std::string TEXT_FRAMERATE_LIMIT;
  static std::string TEXT_GRAPHICS;
  static std::string TEXT_GAMEPLAY;
  static std::string TEXT_LANGUAGE;
  static std::string TEXT_CREDITS;
  static std::string TEXT_SAVE;
  static std::string TEXT_LOAD;
  static std::string TEXT_EXIT;

  static void initializeLocalization(Language language) {
    Localization localization;

    if (localization.initializeLocalization(language)) {
      TEXT_RESOLUTION = localization.getLocalizedString(
          "SETTING_OPTIONS", "LOCAL_RESOLUTION", "@Resolution Text");
      TEXT_RESOLUTION = localization.getLocalizedString(
          "SETTING_OPTIONS", "LOCAL_VAR_OFF", "@OFF");
      TEXT_RESOLUTION = localization.getLocalizedString("SETTING_OPTIONS",
                                                        "LOCAL_VAR_ON", "@ON");
      TEXT_RESOLUTION = localization.getLocalizedString(
          "SETTING_OPTIONS", "TEXT_VSYNC_DISABLE", "@vSync");
      TEXT_RESOLUTION = localization.getLocalizedString(
          "SETTING_OPTIONS", "TEXT_VSYNC_ENABLE", "@Resolution Text");
      TEXT_FULLSCREEN = localization.getLocalizedString(
          "SETTING_OPTIONS", "LOCAL_FULLSCREEN", "@Fullscreen Text");
      TEXT_VSYNC = localization.getLocalizedString(
          "SETTING_OPTIONS", "LOCAL_VSYNC", "@VSync Text");
      TEXT_CONTROLS = localization.getLocalizedString(
          "SETTING_OPTIONS", "LOCAL_CONTROLS", "@Controls Text");
      TEXT_AUDIO = localization.getLocalizedString(
          "SETTING_OPTIONS", "LOCAL_AUDIO", "@Audio Text");
      TEXT_ANTIALIASING = localization.getLocalizedString(
          "SETTING_OPTIONS", "LOCAL_ANTIALIASING", "@Antialiasing Text");
      TEXT_FRAMERATE_LIMIT = localization.getLocalizedString(
          "SETTING_OPTIONS", "LOCAL_FRAMERATE_LIMIT", "@Framerate Limit Text");
      TEXT_GRAPHICS = localization.getLocalizedString(
          "SETTING_OPTIONS", "LOCAL_GRAPHICS", "@Graphics Text");
      TEXT_GAMEPLAY = localization.getLocalizedString(
          "SETTING_OPTIONS", "LOCAL_GAMEPLAY", "@Gameplay Text");
      TEXT_LANGUAGE = localization.getLocalizedString(
          "SETTING_OPTIONS", "LOCAL_LANGUAGE", "@Language Text");
      TEXT_CREDITS = localization.getLocalizedString(
          "SETTING_OPTIONS", "LOCAL_CREDITS", "@Credits Text");
      TEXT_SAVE = localization.getLocalizedString("SETTING_OPTIONS",
                                                  "LOCAL_SAVE", "@Save Text");
      TEXT_LOAD = localization.getLocalizedString("SETTING_OPTIONS",
                                                  "LOCAL_LOAD", "@Load Text");
      TEXT_EXIT = localization.getLocalizedString("SETTING_OPTIONS",
                                                  "LOCAL_EXIT", "@Exit Text");
    }
  }
};

class ApplicationLangue {
public:
  static Language currentLanguage;

  static void setLanguage(Language language) {
    currentLanguage = language;

    helperText::Button::initializeLocalization(language);
    helperText::SettingsTexts::initializeLocalization(language);
    helperText::VolumeTexts::initializeLocalization(language);
  }
};

}; // namespace helperText

#endif /* HELPERTEXT */
