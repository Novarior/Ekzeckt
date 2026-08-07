#pragma once

#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>

struct ModelData {
	std::string nameGalaxy;

	float galaxyRadius = 4200.f;	// radius galaxy
	uint64_t seed = 0;			// seed for generation
	uint32_t starCount = 7'000;

	int spiralArms = 2;		// count arms in our galaxy
	uint32_t spiralArmCount = 250;
	float spiralArmsWigth = 10.f;	// arm size
	float spiralArmCurvature = 18.f;

	float CoreRadius = 50.f;
	float CoreBrightness = 15.f;

	uint32_t DustDensity = 100;
	uint32_t GasDensity = 500;
};

// basic spec star by temperature O, B, A, F, G, K, M.
// temp by spec (K - Kelvin)
//	 ____________________________
// 	/  O  |		over 30'000 K	 \
//	|_____|______________________|
//	|  B  |  10'000 |  30'000 K  |
//	|_____|_________|____________|
//	|  A  |  7'400  |  10'000 K  |
//	|_____|_________|____________|
//	|  F  |  6'000  |  7'400 K   |
//	|_____|_________|____________|
//	|  G  |  5'000  |  6'000 K   |
//	|_____|_________|____________|
//	|  K  |  3'800  |  5'000 K   |
//	|_____|_________|____________|
//	|  M  |  2'500  |  3'800     |
//  \_____|_________|____________/

struct starData {
	sf::Vector2i position = {0, 0};
	uint16_t temperature = 0;	// temperature in K - Kelvin
	uint32_t mass = 0;			// Mass relative to Sun
	uint8_t spectralClass = 0;	// Stellar classification (O, B, A, F, G, K, M)
	uint8_t starType = 0;		// 0=MainSequence, 1=Giant, 2=Dwarf, 3=Supergiant

	float radius = 0.f;			// radius (same as size)
	float gravRadius = 0.f;
	float gravCoefficient = 0.f;

	bool isBinary = false;              // Is part of binary star system
	bool hasCompanion = false;          // Has planetary system
};

class SpiralModel:public sf::Drawable, sf::Transformable {
private:
	sf::VertexArray mLines;
	sf::VertexArray mPointStar;
	sf::VertexArray mStarPlus;
	sf::VertexArray mDust;
	sf::VertexArray mGas;

	ModelData* mData;

	sf::Vector2f calculateSpiralPoint(float angle, float radius) const;
	sf::Color getArmColor(float normalizedIntensity) const;
	sf::Color getStarColor(float randomValue) const;

	void generateSpiralArms();
	void generateStars();
	void generateDust();
	void generateGas();
public:

	SpiralModel(ModelData* data);
	~SpiralModel();

	void update(const float& delta_time, sf::Vector2f mouseViewPos);

	void clearModel();
	void regenerateSpiral();


	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
};

