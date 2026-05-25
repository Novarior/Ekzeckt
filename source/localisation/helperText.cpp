#include "helperText.hpp"
// Определение статических переменных
helperText::Language helperText::ApplicationLangue::currentLanguage = helperText::Language::ENG;
nlohmann::json helperText::Localization::loadedJson;
std::filesystem::path helperText::Localization::currentFilePath;

bool helperText::Localization::loadLocalizationFile(const std::filesystem::path& _filename) {
	if (currentFilePath == _filename)
		return true; // Файл уже загружен

	std::ifstream ifs(_filename);
	if (!ifs.is_open()) {
		std::cerr << "LERROR: Could not load file: " << _filename << std::endl;
		Logger::logStatic("LERROR::COULD NOT LOAD FILE: " + _filename.string(), "Localization::loadLocalizationFile()");
		return false;
	}

	try {
		ifs >> loadedJson;
	} catch (const std::exception& e) {
		std::cerr << "LERROR: Failed to parse JSON: " << e.what() << std::endl;
		return false;
	}

	ifs.close();
	currentFilePath = _filename;
	return true;
}

bool helperText::Localization::initializeLocalization(Language language) {
	std::filesystem::path p;
	switch (language) {
	case Language::ENG:
		p = AppFn::getPathResourcesDir() / myConst::localisation::localisation_EN;
		break;
	case Language::UKR:
		p = AppFn::getPathResourcesDir() / myConst::localisation::localisation_UA;
		break;
	default:
		p = AppFn::getPathResourcesDir() / myConst::localisation::localisation_EN;

		std::cerr << "LERROR: Unsupported language!" << std::endl;
		return false;
	}

	return loadLocalizationFile(p);
}

std::string
helperText::Localization::getLocalizedString(const std::string& category,
											 const std::string& key,
											 const std::string& defaultValue) {
	if (loadedJson.contains(category))
		return loadedJson[category].value(key, defaultValue);

	else {
		std::cerr << "LERROR: Category '" << category << "' not found in localization JSON." << std::endl;
		return defaultValue;
	}
}

// struct SettingsTexts
std::string helperText::SettingsTexts::TEXT_ON = "#ON";
std::string helperText::SettingsTexts::TEXT_OFF = "#OFF";
std::string helperText::SettingsTexts::TEXT_VSYNC = "#VSYNC";
std::string helperText::SettingsTexts::TEXT_AUDIO = "#AUDIO";
std::string helperText::SettingsTexts::TEXT_CONTROLS = "#CONTROLS";
std::string helperText::SettingsTexts::TEXT_RESOLUTION = "#RESOLUTION";
std::string helperText::SettingsTexts::TEXT_FULLSCREEN = "#FULLSCREEN";
std::string helperText::SettingsTexts::TEXT_ANTIALIASING = "#ANTIALIASING";
std::string helperText::SettingsTexts::TEXT_FRAMERATE_LIMIT = "#FRAMERATE_LIMIT";
std::string helperText::SettingsTexts::TEXT_GRAPHICS = "#GRAPHICS";
std::string helperText::SettingsTexts::TEXT_GAMEPLAY = "#GAMEPLAY";
std::string helperText::SettingsTexts::TEXT_LANGUAGE = "#LANGUAGE";
std::string helperText::SettingsTexts::TEXT_CREDITS = "#CREDITS";
std::string helperText::SettingsTexts::TEXT_SAVE = "#SAVE";
std::string helperText::SettingsTexts::TEXT_LOAD = "#LOAD";
std::string helperText::SettingsTexts::TEXT_EXIT = "#EXIT";

// struct VolumeTexts
std::string helperText::VolumeTexts::VOL_MASTER = "#MASTER";
std::string helperText::VolumeTexts::VOL_SFX = "#SFX";
std::string helperText::VolumeTexts::VOL_MUSIC = "#MUSIC";
std::string helperText::VolumeTexts::VOL_UI_VOL = "#UI_VOL";
std::string helperText::VolumeTexts::VOL_AMBIENT = "#AMBIENT";
std::string helperText::VolumeTexts::VOL_FOLEYVOL = "#FOLEYVOL";
std::string helperText::VolumeTexts::VOL_WEAPONVOL = "#WEAPONVOL";
std::string helperText::VolumeTexts::VOL_ENTITYSFX = "#ENTITYSFX";
std::string helperText::VolumeTexts::VOL_DIALOGUE_VOL = "#DIALOGUE_VOL";
std::string helperText::VolumeTexts::VOL_ENVIRONMENTVOL = "#ENVIRONMENTVOL";

// struct Button
std::string helperText::Button::BUTTON_PLAY = "#PLAY";
std::string helperText::Button::BUTTON_EXIT = "#EXIT";
std::string helperText::Button::BUTTON_BACK = "#BACK";
std::string helperText::Button::BUTTON_SAVE = "#SAVE";
std::string helperText::Button::BUTTON_LOAD = "#LOAD";
std::string helperText::Button::BUTTON_PM_PAUSE = "#PAUSE";
std::string helperText::Button::BUTTON_PM_GENERATE = "#GENERATE";
std::string helperText::Button::BUTTON_APPLY = "#APPLY";
std::string helperText::Button::BUTTON_CANCEL = "#CANCEL";
std::string helperText::Button::BUTTON_OPTIONS = "#OPTIONS";
std::string helperText::Button::BUTTON_NEW_GAME = "#NEW_GAME";
std::string helperText::Button::BUTTON_CONTINUE = "#CONTINUE";
std::string helperText::Button::BUTTON_NOICE_EDITOR = "#NOICE_EDITOR";
std::string helperText::Button::BUTTON_DEBUG_ROOM_STATE = "#NOICE_EDITOR";