#include "NoiceViewer.hpp"

void NoiceViewer::initvariables() {
	noiceImage = sf::Image({m_noice_data->RenderWindowX, m_noice_data->RenderWindowY}, sf::Color::Black);
	noiceTexture = sf::Texture(noiceImage);
	noiceShape.setSize(sf::Vector2f(m_noice_data->RenderWindowX, m_noice_data->RenderWindowY));
}

NoiceViewer::NoiceViewer(NoiceData* m_data): m_noice_data(m_data) {
	// logger
	appfn::Logger::logStatic("NoiceViewer constructor", "NoiceViewer");

	m_prn_noice = new ProcessGenerationNoice(m_noice_data);
	m_perlin_noice = new PerlinNoise(m_noice_data);
	m_simplex_noice = new SimplexNoise();
	current_Noice_Model = PERLIN_NOICE;
	current_Color_Mode = FULL_COLOR;

	// resize vector to map size
	uint32_t size = m_noice_data->mapSizeX * m_noice_data->mapSizeY;
	noiceMap.resize(size);

	initvariables();
}

NoiceViewer::~NoiceViewer() {
	appfn::Logger::logStatic("NoiceViewer destructor", "NoiceViewer");

	delete m_prn_noice;
	delete m_perlin_noice;
	delete m_simplex_noice;
}

void NoiceViewer::updateNoiceModels() {
	m_prn_noice->setNoiceData(m_noice_data);
}

void NoiceViewer::generateNoice() {
	const uint32_t width = m_noice_data->mapSizeX;
	const uint32_t height = m_noice_data->mapSizeY;
	const uint32_t size = height * width;

	// clean noice map before generate
	noiceMap.clear();
	noiceMap.resize(size);
	// determine thread count
	uint32_t hw = std::thread::hardware_concurrency();
	if (hw == 0) hw = 4; // fallback
	uint32_t threadCount = std::min<unsigned int>(hw, static_cast<unsigned int>(width));
	std::vector<std::thread> workers;
	workers.reserve(threadCount);

	// chunk size along X axis
	int chunk = (width + threadCount - 1) / threadCount;

	for (uint32_t t = 0; t < threadCount; ++t) {
		uint32_t xStart = static_cast<int>(t * chunk);
		uint32_t xEnd = std::min(width, xStart + chunk);

		workers.emplace_back([this, xStart, xEnd, height, width]() {
			// Each thread writes only to noiceMap for x in [xStart,xEnd)
			for (uint32_t x = xStart; x < xEnd; ++x) {
				for (uint32_t y = 0; y < height; ++y) {
					uint32_t index = y * width + x;
					switch (noiceType(current_Noice_Model)) {
					case PERLIN_NOICE:
						noiceMap[index] = m_perlin_noice->Noise(x, y, 0, 255);
						break;
					case PERLIN_NOICE_V2:
						noiceMap[index] = m_prn_noice->getNoice(x, y);
						break;
					case SIMPLEX_NOICE:
						noiceMap[index] = m_simplex_noice->noise(x / m_noice_data->frequency / 10.f, y / m_noice_data->frequency / 10.f);
						break;
					default:
						noiceMap[index] = 0.0;
						break;
					}
				}
			}
		});
	}

	// join threads
	for (auto& th : workers) {
		if (th.joinable()) th.join();
	}

	// fill image using vector array
	double vec_buffer = 0.f;
	for (unsigned int x = 0; x < m_noice_data->mapSizeX; x++)
		for (unsigned int y = 0; y < m_noice_data->mapSizeY; y++) {
			uint32_t index = y * width + x;
			vec_buffer = noiceMap[index];

			switch (colorMode(current_Color_Mode)) {
			case FULL_COLOR:
			{
				if (vec_buffer < 45) { // deep ocean
					double depth_intensity = 100 + vec_buffer * 1.2;
					noiceImage.setPixel({x, y}, sf::Color(0, std::max(0.0, 5 + vec_buffer * 0.4), std::min(255.0, depth_intensity), 255));
				} else if (vec_buffer < 65) { // ocean
					double shore_intensity = 100 + vec_buffer * 2.0;
					noiceImage.setPixel({x, y}, sf::Color(0, std::min(255.0, 15 + vec_buffer * 0.8), std::min(255.0, shore_intensity), 255));
				} else if (vec_buffer < 80) { // sand
					noiceImage.setPixel({x, y}, sf::Color(std::min(255.0, 200 + vec_buffer * 0.5), std::min(255.0, 180 + vec_buffer * 0.3), std::min(255.0, 100 + vec_buffer * 0.1), 255));
				} else if (vec_buffer < 140) { // grass
					noiceImage.setPixel({x, y}, sf::Color(std::min(255.0, vec_buffer * 0.08), std::min(255.0, 40 + vec_buffer * 0.9), std::min(255.0, vec_buffer * 0.05), 255));
				} else if (vec_buffer < 165) { // dirt
					noiceImage.setPixel({x, y}, sf::Color(90 - vec_buffer * 0.1, 71 + vec_buffer * 0.15, 55 + vec_buffer * 0.1, 255));
				} else if (vec_buffer < 200) { // rock
					noiceImage.setPixel({x, y}, sf::Color(10 + vec_buffer * 0.2, 10 + vec_buffer * 0.2, 10 + vec_buffer * 0., 255));
				} else { // snow
					double intensity = 200 + (vec_buffer - 200) * 0.275;
					noiceImage.setPixel({x, y}, sf::Color(std::min(255.0, intensity), std::min(255.0, intensity), std::min(255.0, intensity), 255));
				}
				break;
			}
			case BIOME_COLOR:
			{
				if (vec_buffer < 50) { // deep ocean
					double depth_intensity = 20 + vec_buffer * 1.5;
					noiceImage.setPixel({x, y}, sf::Color(0, std::max(0.0, 10 + vec_buffer * 0.5), std::min(255.0, 50 + vec_buffer * 1.2), 255));
				} else if (vec_buffer < 70) { // shallow ocean
					double shore_intensity = 50 + vec_buffer * 2.0;
					noiceImage.setPixel({x, y}, sf::Color(0, std::min(255.0, 15 + vec_buffer * 0.8), std::min(255.0, shore_intensity), 255));
				} else if (vec_buffer < 85) { // sand/beach
					noiceImage.setPixel({x, y}, sf::Color(std::min(255.0, 210 + vec_buffer * 0.3), std::min(255.0, 190 + vec_buffer * 0.2), std::min(255.0, 120 + vec_buffer * 0.15), 255));
				} else if (vec_buffer < 140) { // grass/plains
					double green_intensity = 40 + (vec_buffer - 85) * 0.8;
					noiceImage.setPixel({x, y}, sf::Color(std::min(255.0, 34 + vec_buffer * 0.3), std::min(255.0, green_intensity + 80), std::min(255.0, vec_buffer * 0.2), 255));
				} else if (vec_buffer < 160) { // forest/dark grass
					noiceImage.setPixel({x, y}, sf::Color(std::min(255.0, 20 + vec_buffer * 0.4), std::min(255.0, 80 + vec_buffer * 0.5), std::min(255.0, vec_buffer * 0.15), 255));
				} else if (vec_buffer < 185) { // hills/rock
					double rock_intensity = 80 + (vec_buffer - 160) * 1.2;
					noiceImage.setPixel({x, y}, sf::Color(std::min(255.0, rock_intensity), std::min(255.0, rock_intensity - 20), std::min(255.0, rock_intensity - 40), 255));
				} else if (vec_buffer < 210) { // mountain/high rock - сірі тони
					double mountain_intensity = 140 + (vec_buffer - 190) * 1.2;
					noiceImage.setPixel({x, y}, sf::Color(std::min(255.0, mountain_intensity), std::min(255.0, mountain_intensity - 10), std::min(255.0, mountain_intensity - 15), 255));
				} else { // snow/peak
					double snow_intensity = 230 + (vec_buffer - 220) * 0.3;
					noiceImage.setPixel({x, y}, sf::Color(std::min(255.0, snow_intensity), std::min(255.0, snow_intensity), std::min(255.0, snow_intensity), 255));
				}
				break;
			}
			case NOICE_COLOR:
				noiceImage.setPixel({x, y}, sf::Color(vec_buffer, vec_buffer, vec_buffer, 255));
				break;
			default:
				break;
			}
		}

	// access finale image
	noiceTexture.update(noiceImage);
	noiceShape.setTexture(&noiceTexture);
}

const NoiceData* NoiceViewer::getNoiceData() { return m_noice_data; }
const uint16_t NoiceViewer::getNoiceModel() const { return current_Noice_Model; }
const uint16_t NoiceViewer::getColorMode() const { return current_Color_Mode; }
const double NoiceViewer::getHeightMap(sf::Vector2i mousepos) {
	if (mousepos.x > 0 && mousepos.x < m_noice_data->mapSizeX && mousepos.y > 0 && mousepos.y < m_noice_data->mapSizeY)
		return noiceMap[mousepos.x+ mousepos.y* m_noice_data->mapSizeX];
	return 0.0;
}

void NoiceViewer::swithNoiceModel() {
	// switch noice model to next
	// if current model is last, switch to first
	if (current_Noice_Model == SIMPLEX_NOICE)
		current_Noice_Model = PERLIN_NOICE;
	else
		current_Noice_Model++;
}
const std::string NoiceViewer::getNoiceModelName() {
	if (current_Noice_Model > noiceModels.size())
		return "NaN";
	return noiceModels[current_Noice_Model];
}
const std::string NoiceViewer::getColorModeName() {
	if (current_Color_Mode > colorModes.size())
		return "NaN";
	return colorModes[current_Color_Mode];
}

const std::string NoiceViewer::getNoiceSmouthName() {
	std::array<std::string, 7> smoothModes = {"Linear", "Cosine", "Cubic", "Quintic", "Quartic", "Quadratic", "Hermite"};

	return smoothModes[m_noice_data->smoothMode];
}

void NoiceViewer::swithColorMode() {
	// switch color mode to next
	// if current mode is last, switch to first
	if (current_Color_Mode == BIOME_COLOR)
		current_Color_Mode = FULL_COLOR;
	else
		current_Color_Mode++;
}

void NoiceViewer::update(const float& dt) {}

void NoiceViewer::render(sf::RenderTarget& target) {
	target.draw(noiceShape);
}
