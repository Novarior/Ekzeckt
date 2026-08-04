#ifndef CPP_STATE_NOICE_VIEW_HPP
#define CPP_STATE_NOICE_VIEW_HPP

#include "../../core/header.h"

#include "../../core/tools/appfn_logger.hpp"

#include "../../core/math/models noice/Noise_data.h"
#include "../../core/math/models noice/Noice_PGN.hpp"
#include "../../core/math/models noice/Noice_Perlin.hpp"
#include "../../core/math/models noice/Noice_Simplex.hpp"

enum noiceType {
	PERLIN_NOICE = 0,
	PERLIN_NOICE_V2 = 1,
	SIMPLEX_NOICE = 2
};

enum colorMode {
	FULL_COLOR = 0,
	NOICE_COLOR = 1,
	BIOME_COLOR = 2
};

class NoiceViewer {
private:
	std::array<std::string, 3> noiceModels = {"Perlin Noice", "Perlin Noice V2", "Simplex Noice"};
	std::array<std::string, 3> colorModes = {"Full Color", "Noice Color", "Biome Color 'add speciac viewport"};

	// Noice data colector
	NoiceData* m_noice_data;

	// models Noice generators
	ProcessGenerationNoice* m_prn_noice;
	PerlinNoise* m_perlin_noice;
	SimplexNoise* m_simplex_noice;

	// image and texture
	sf::Image noiceImage;
	sf::Texture noiceTexture;
	sf::RectangleShape noiceShape;

	uint16_t current_Noice_Model;
	uint16_t current_Color_Mode;

	void updateNoiceModels();

	void initvariables();

	// dynamin 2d array
	std::vector<double> noiceMap;

public:
	NoiceViewer(NoiceData* noicedata);
	~NoiceViewer();

	const NoiceData* getNoiceData();

	void swithNoiceModel();
	void swithColorMode();

	const std::string getNoiceModelName();
	const std::string getColorModeName();

	const uint16_t getNoiceModel() const;
	const uint16_t getColorMode() const;
	const double getHeightMap(sf::Vector2i mousepos);
	const std::string getNoiceSmouthName();

	void generateNoice();
	void setNoiceData(NoiceData* noicedata) { m_noice_data = noicedata; }

	void update(const float& dt);
	void render(sf::RenderTarget& target);
};
#endif // CPP_STATE_NOICE_VIEW_HPP