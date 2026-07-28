#include "NoiceViewer.hpp"
#include "../../core/tools/LOGGER.hpp"

void NoiceViewer::initvariables() {
	noiceImage = sf::Image({m_noice_data->RenderWindowX,  m_noice_data->RenderWindowY}, sf::Color::Black);
	noiceTexture = sf::Texture(noiceImage);
	noiceShape.setSize(sf::Vector2f(m_noice_data->RenderWindowX, m_noice_data->RenderWindowY));
}

NoiceViewer::NoiceViewer(NoiceData* m_data): m_noice_data(m_data) {
	// logger
	Logger::logStatic("NoiceViewer constructor", "NoiceViewer");

	m_prn_noice = new ProcessGenerationNoice(m_noice_data);
	m_perlin_noice = new PerlinNoise(m_noice_data);
	m_simplex_noice = new SimplexNoise();
	current_Noice_Model = PERLIN_NOICE;
	current_Color_Mode = FULL_COLOR;

	// resize vector to map size
	noiceMap.resize(m_noice_data->mapSizeX);
	for (int i = 0; i < m_noice_data->mapSizeX; i++)
		noiceMap[i].resize(m_noice_data->mapSizeY);

	initvariables();
}

NoiceViewer::~NoiceViewer() {
	Logger::logStatic("NoiceViewer destructor", "NoiceViewer");

	delete  m_prn_noice;
	delete  m_perlin_noice;
	delete  m_simplex_noice;
}

void NoiceViewer::updateNoiceModels() {
	m_prn_noice->setNoiceData(m_noice_data);
}

void NoiceViewer::generateNoice() {
	// clean noice map before generate
	noiceMap.clear();
	noiceMap.resize(m_noice_data->mapSizeX);
	for (int i = 0; i < m_noice_data->mapSizeX; i++)
		noiceMap[i].resize(m_noice_data->mapSizeY);

	const int width = m_noice_data->mapSizeX;
	const int height = m_noice_data->mapSizeY;

	// determine thread count
	unsigned int hw = std::thread::hardware_concurrency();
	if (hw == 0) hw = 4; // fallback
	unsigned int threadCount = std::min<unsigned int>(hw,  static_cast<unsigned int>(width));
	std::vector<std::thread> workers;
	workers.reserve(threadCount);

	// chunk size along X axis
	int chunk = (width + threadCount - 1) / threadCount;

	for (unsigned int t = 0; t < threadCount; ++t) {
		int xStart = static_cast<int>(t * chunk);
		int xEnd = std::min(width, xStart + chunk);

		workers.emplace_back([this, xStart, xEnd, height]() {
			// Each thread writes only to noiceMap[x][y] for x in [xStart,xEnd)
			for (int x = xStart; x < xEnd; ++x) {
				for (int y = 0; y < height; ++y) {
					switch (noiceType(current_Noice_Model)) {
					case PERLIN_NOICE:
						noiceMap[x][y] = m_perlin_noice->Noise(x, y, 0, 255);
						break;
					case PERLIN_NOICE_V2:
						noiceMap[x][y] = m_prn_noice->getNoice(x, y);
						break;
					case SIMPLEX_NOICE:
						noiceMap[x][y] = m_simplex_noice->noise(x / m_noice_data->amplifire / 10.f, y / m_noice_data->amplifire / 10.f);
						break;
					default:
						noiceMap[x][y] = 0.0;
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
			vec_buffer = noiceMap[x][y];

			switch (colorMode(current_Color_Mode)) {
			case FULL_COLOR:
			{
				if (vec_buffer < 45) { // deep ocean
					double depth_intensity = 100 + vec_buffer * 1.2;
					noiceImage.setPixel({x, y}, sf::Color(0,
										std::max(0.0, 5 + vec_buffer * 0.4),
										std::min(255.0, depth_intensity), 255));
				} else if (vec_buffer < 66) { // ocean
					double shore_intensity = 100 + vec_buffer * 2.0;
					noiceImage.setPixel({x, y}, sf::Color(0,
										std::min(255.0, 15 + vec_buffer * 0.8),
										std::min(255.0, shore_intensity), 255));
				} else if (vec_buffer < 85) { // sand
					noiceImage.setPixel({x, y}, sf::Color(std::min(255.0, 200 + vec_buffer * 0.5),
										std::min(255.0, 180 + vec_buffer * 0.3),
										std::min(255.0, 100 + vec_buffer * 0.1), 255));
				} else if (vec_buffer < 120) { // grass
					noiceImage.setPixel({x, y}, sf::Color(std::min(255.0, vec_buffer * 0.08),
										std::min(255.0, 40 + vec_buffer * 0.9),
										std::min(255.0, vec_buffer * 0.05), 255));
				} else if (vec_buffer < 165) { // dirt
					noiceImage.setPixel({x, y}, sf::Color(90 - vec_buffer * 0.1,
										71 + vec_buffer * 0.15,
										55 + vec_buffer * 0.1, 255));
				} else if (vec_buffer < 200) { // rock
					noiceImage.setPixel({x, y}, sf::Color(40 + vec_buffer * 0.1,
										71 - vec_buffer * 0.2,
										55 - vec_buffer * 0.2, 255));
				} else { // snow
					double intensity = 200 + (vec_buffer - 200) * 0.275;
					noiceImage.setPixel({x, y}, sf::Color(std::min(255.0, intensity),
										std::min(255.0, intensity),
										std::min(255.0, intensity),
										255));
				}
				break;
			}
			case NOICE_COLOR:
				noiceImage.setPixel({x, y}, sf::Color(vec_buffer, vec_buffer, vec_buffer, 255));
				break;
			case BIOME_COLOR:
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
const uint16_t NoiceViewer::getColorMode() const { return  current_Color_Mode; }
const double NoiceViewer::getHeightMap(sf::Vector2i mousepos) {
	if (mousepos.x > 0 && mousepos.x < m_noice_data->mapSizeX && mousepos.y > 0 && mousepos.y < m_noice_data->mapSizeY)
		return noiceMap[mousepos.x][mousepos.y];
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
	return  noiceModels[current_Noice_Model];
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
const std::string NoiceViewer::getColorModeName() {
	return  colorModes[current_Color_Mode];
}

void NoiceViewer::update(const float& dt) {}

void NoiceViewer::render(sf::RenderTarget& target) {
	target.draw(noiceShape);
}
