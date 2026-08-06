#pragma once

#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>

struct ModelData {
	std::string nameGalaxy;

	float galaxyRadius = 3500.f;	// radius galaxy
	uint64_t seed = 0;			// seed for generation
	uint32_t starCount = 7'000;

	int spiralArms = 2;		// count arms in our galaxy
	uint32_t spiralArmCount = 1000;
	float spiralArmsWigth = 10.f;	// arm size
	float spiralArmCurvature = 18.f;

	float CoreRadius = 50.f;
	float CoreBrightness = 15.f;

	uint32_t DustDensity = 100;
	uint32_t GasDensity = 500;
};

class SpiralModel:public sf::Drawable, sf::Transformable {

private:
	sf::VertexArray mLines;
	sf::VertexArray mPointStar;
	sf::VertexArray mStarPlus;
	sf::Vector2f mCenter;
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

	SpiralModel(ModelData* data, sf::Vector2u winSize);
	~SpiralModel();

	void clearModel();
	void regenerateSpiral();


	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
};

