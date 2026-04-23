#include "NoiceViewer.hpp"
#include "../../core/tools/LOGGER.hpp"

void NoiceViewer::initvariables() {
  this->noiceImage = sf::Image(
      {this->m_noice_data.RenderWindowX, this->m_noice_data.RenderWindowY},
      sf::Color::Black);
  this->noiceTexture = sf::Texture(this->noiceImage);
  this->noiceShape.setSize(sf::Vector2f(this->m_noice_data.RenderWindowX,
                                        this->m_noice_data.RenderWindowY));
}

NoiceViewer::NoiceViewer(mmath::noiceData &m_data) : m_noice_data(m_data) {
  // logger
  Logger::logStatic("NoiceViewer constructor", "NoiceViewer");

  this->m_prn_noice = new ProcessGenerationNoice(this->m_noice_data);
  this->m_perlin_noice = new PerlinNoise();
  this->m_simplex_noice = new SimplexNoise();
  this->current_Noice_Model = PERLIN_NOICE;
  this->current_Color_Mode = FULL_COLOR;

  // resize vector to map size
  this->noiceMap.resize(this->m_noice_data.mapSizeX);
  for (int i = 0; i < this->m_noice_data.mapSizeX; i++)
    this->noiceMap[i].resize(this->m_noice_data.mapSizeY);

  this->initvariables();
}

NoiceViewer::~NoiceViewer() {
  Logger::logStatic("NoiceViewer destructor", "NoiceViewer");

  delete this->m_prn_noice;
  delete this->m_perlin_noice;
  delete this->m_simplex_noice;
}

void NoiceViewer::updateNoiceModels() {
  this->m_prn_noice->setNoiceData(this->m_noice_data);
}

void NoiceViewer::generateNoice() {
  double h_buffer = 0.f;

  // clean noice map before generate
  this->noiceMap.clear();

  this->noiceMap.resize(this->m_noice_data.mapSizeX);
  for (int i = 0; i < this->m_noice_data.mapSizeX; i++)
    this->noiceMap[i].resize(this->m_noice_data.mapSizeY);

  for (int x = 0; x < this->m_noice_data.mapSizeX; x++)
    for (int y = 0; y < this->m_noice_data.mapSizeY; y++)
      switch (noiceType(current_Noice_Model)) {
      case PERLIN_NOICE:
        h_buffer = this->m_perlin_noice->Noise(x, y, 0, 255,
                                               this->m_noice_data.fastMode);
        this->noiceMap[x][y] = h_buffer;
        break;
      case PERLIN_NOICE_V2:
        h_buffer = this->m_prn_noice->getNoice(x, y);
        this->noiceMap[x][y] = mmath::normalize(h_buffer);
        break;
      case SIMPLEX_NOICE:
        h_buffer = this->m_simplex_noice->noise(
            x / this->m_noice_data.amplifire / 10.f,
            y / this->m_noice_data.amplifire / 10.f);
        this->noiceMap[x][y] = h_buffer;
        break;
      default:
        break;
      }

  // fill image using vector array
  double vec_buffer = 0.f;
  for (unsigned int x = 0; x < this->m_noice_data.mapSizeX; x++)
    for (unsigned int y = 0; y < this->m_noice_data.mapSizeY; y++) {
      vec_buffer = this->noiceMap[x][y];

      switch (colorMode(current_Color_Mode)) {
      case FULL_COLOR: {
        if (vec_buffer < 45) { // deep ocean
          double depth_intensity =
              100 + vec_buffer * 1.2; // Интенсивность синего
          this->noiceImage.setPixel(
              {x, y},
              sf::Color(
                  0, // Красный: полностью отсутствует
                  std::max(0.0, 5 + vec_buffer * 0.4), // Зелёный: приглушённый
                  std::min(255.0, depth_intensity),    // Синий: от 100 до 154
                  255));                               // Альфа
        } else if (vec_buffer < 66) {                  // ocean
          double shore_intensity =
              100 + vec_buffer *
                        2.0; // Синий: плавный переход от глубокого к светлому
          this->noiceImage.setPixel(
              {x, y},
              sf::Color(
                  0, // Красный: всегда отсутствует
                  std::min(255.0,
                           15 + vec_buffer *
                                    0.8), // Зелёный: усиливается от 15 до 67.8
                  std::min(255.0, shore_intensity), // Синий: от 100 до 232
                  255));                            // Альфа
        } else if (vec_buffer < 85) {               // sand
          this->noiceImage.setPixel(
              {x, y},
              sf::Color(
                  std::min(255.0,
                           200 + vec_buffer * 0.5), // Красный: от 200 до 242.5
                  std::min(255.0,
                           180 + vec_buffer * 0.3), // Зелёный: от 180 до 205.5
                  std::min(255.0,
                           100 + vec_buffer * 0.1), // Синий: от 100 до 108.5
                  255                               // Альфа: 255
                  ));
        } else if (vec_buffer < 120) { // grass
          this->noiceImage.setPixel(
              {x, y},
              sf::Color(
                  std::min(255.0,
                           vec_buffer * 0.08), // Красный: чуть приглушённый
                  std::min(255.0,
                           40 + vec_buffer *
                                    0.9), // Зелёный: уменьшена насыщенность
                  std::min(255.0, vec_buffer * 0.05), // Синий: слегка усилен
                  255));                              // Альфа
        } else if (vec_buffer < 165) {                // dirt
          this->noiceImage.setPixel(
              {x, y}, sf::Color(90 - vec_buffer * 0.1, 71 + vec_buffer * 0.15,
                                55 + vec_buffer * 0.1, 255));
        } else if (vec_buffer < 200) { // rock
          this->noiceImage.setPixel(
              {x, y}, sf::Color(40 + vec_buffer * 0.1, 71 - vec_buffer * 0.2,
                                55 - vec_buffer * 0.2, 255));
        } else { // snow
          double intensity =
              200 + (vec_buffer - 200) * 0.275; // Градиент от 200 до 255
          this->noiceImage.setPixel(
              {x, y}, sf::Color(std::min(255.0, intensity), // Красный
                                std::min(255.0, intensity), // Зелёный
                                std::min(255.0, intensity), // Синий
                                255));                      // Альфа
        }
        break;
      }
      case NOICE_COLOR:
        this->noiceImage.setPixel(
            {x, y}, sf::Color(vec_buffer, vec_buffer, vec_buffer, 255));
        break;
      case BIOME_COLOR:
        break;
      default:
        break;
      }
    }

  // access finale image
  this->noiceTexture.update(this->noiceImage);
  this->noiceShape.setTexture(&this->noiceTexture);
}

void NoiceViewer::swithNoiceModel() {
  // switch noice model to next
  // if current model is last, switch to first
  if (this->current_Noice_Model == SIMPLEX_NOICE)
    this->current_Noice_Model = PERLIN_NOICE;
  else
    this->current_Noice_Model++;
}
const std::string NoiceViewer::getNoiceModelName() {
  return this->noiceModels[this->current_Noice_Model];
}

const std::string NoiceViewer::getNoiceSmouthName() {
  std::array<std::string, 7> smoothModes = {"Linear",  "Cosine",  "Cubic",
                                            "Quintic", "Quartic", "Quadratic",
                                            "Hermite"};

  return smoothModes[this->m_noice_data.smoothMode];
}

void NoiceViewer::swithColorMode() {
  // switch color mode to next
  // if current mode is last, switch to first
  if (this->current_Color_Mode == BIOME_COLOR)
    this->current_Color_Mode = FULL_COLOR;
  else
    this->current_Color_Mode++;
}
const std::string NoiceViewer::getColorModeName() {
  return this->colorModes[this->current_Color_Mode];
}

void NoiceViewer::update(const float &dt) {}

void NoiceViewer::render(sf::RenderTarget &target) {
  target.draw(this->noiceShape);
}
