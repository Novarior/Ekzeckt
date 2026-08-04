#include "Core.h"

// mega load stuff here
// read the object with data and paste it to structs
bool Core::cr_LoadData() {
	auto a_gfx = cr_gfxSettings.get();
	auto a_vol = cr_VolumeCollector.get();

	try {
#ifdef __MDEBUG__
		appfn::Logger::logStatic("Loading config data...", "Core::cr_LoadData()");
#endif // __MDEBUG__
		if (!jsonBuffer.contains("cr_window")) {
			appfn::Logger::logStatic("Missing cr_window section", "Core::cr_LoadData()");
			return false;
		}
		// bind &window
		const auto& window = jsonBuffer["cr_window"];

		// load data to gfx struct
		a_gfx->title = window["title"].get<std::string>();
		a_gfx->resolution.size.x = window["resolution"]["width"].get<unsigned>();
		a_gfx->resolution.size.y = window["resolution"]["height"].get<unsigned>();
		a_gfx->fullscreen = window.value("fullscreen", false);
		a_gfx->frameRateLimit = window.value("frameRateLimit", 60);
		a_gfx->verticalSync = window.value("verticalSync", false);
		a_gfx->contextSettings.antiAliasingLevel = window.value("antialiasingLevel", 0);

		// load sound volumes
		if (!jsonBuffer.contains("cr_sound_volumes"))
			return false; // check if section exists

		const auto& sounds = jsonBuffer["cr_sound_volumes"];
		a_vol->setCategoryVolume(gfx::SoundCategory::vol_MASTER, sounds["master"].get<float>());
		a_vol->setCategoryVolume(gfx::SoundCategory::vol_SFX, sounds["sfx"].get<float>());
		a_vol->setCategoryVolume(gfx::SoundCategory::vol_MUSIC, sounds["music"].get<float>());
		a_vol->setCategoryVolume(gfx::SoundCategory::vol_AMBIENT, sounds["ambient"].get<float>());
		a_vol->setCategoryVolume(gfx::SoundCategory::vol_ENTITY, sounds["entity"].get<float>());
		a_vol->setCategoryVolume(gfx::SoundCategory::vol_UI, sounds["ui"].get<float>());
		a_vol->setCategoryVolume(gfx::SoundCategory::vol_DIALOGUE, sounds["dialogue"].get<float>());
		a_vol->setCategoryVolume(gfx::SoundCategory::vol_FOLEY, sounds["foley"].get<float>());
		a_vol->setCategoryVolume(gfx::SoundCategory::vol_WEAPON, sounds["weapon"].get<float>());
		a_vol->setCategoryVolume(gfx::SoundCategory::vol_ENVIRONMENT, sounds["environment"].get<float>());

	} catch (json::type_error& e) { // catch json type errors
		appfn::Logger::logStatic("JSON::TYPE_LERROR: " + std::string(e.what()), "Core::cr_LoadData()");
		return false;
	}
	return true; // parse and past success
}

// mega save stuff here
bool Core::cr_SaveData() {
	auto a_gfx = cr_gfxSettings.get();
	auto a_vol = cr_VolumeCollector.get();

	std::filesystem::path filePath = appfn::PathTool::getPathConfigDirectory().append("save").append(appfn::path::sfile::config_window);
	std::ofstream ofs(filePath);
	if (!ofs.is_open()) {
		appfn::Logger::logStatic("CANNOT OPEN FILE", "l:96 -> GFX::loadFromFile()");
		return false;
	}

	try {
		jsonBuffer["cr_window"]["title"] = a_gfx->title;

		// after that write to file
		std::ofstream ofs(filePath);
		// check if file was opened
		if (!ofs.is_open()) {
			ofs << jsonBuffer.dump(4);
			ofs.close();
		} else {
			return false;
		}

	} catch (json::type_error& e) { // catch json type errors
		appfn::Logger::logStatic("GFX::JSON::TYPE_LERROR: " + std::string(e.what()), "l:113 -> GFX::loadFromFile()");
		return false; // some arror in loading data from json
	}
	return true; // load success
};
