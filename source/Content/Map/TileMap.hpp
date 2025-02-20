#ifndef CPP_MAP_TILEMAP_HPP
#define CPP_MAP_TILEMAP_HPP
#include "block.hpp"

#include "../../entitys/entity.hpp"
#include "../../math/LSystem.hpp"
#include "../../math/ProcessGenerationNoice.hpp"

class Entity;

struct rectangleWithOffset {
  int fromX;
  int fromY;
  int toX;
  int toY;
  int offsetX;
  int offsetY;
};

class TileMap {
private:
  rectangleWithOffset m_renderArea; // rectangle with offset used for set render
                                    // area in tilemap and update only this area
  rectangleWithOffset m_colisionArea;
  sf::RectangleShape bariere_box; // world bounds collision
  sf::FloatRect checkreck;

  sf::Vector2i worldSizeGrid;
  sf::Vector2i worldSizeInt;
  sf::Vector2f worldSizeFloat;

  std::vector<std::vector<std::vector<BrickBlock *>>> tilemap;

  mmath::noiceData _map_dataNoice;
  ProcessGenerationNoice mGen_noice;

  std::unique_ptr<LSystem> _treeGenerator;

  std::vector<std::vector<float>> _map_heightMap; // 2d array for height map
  std::vector<std::vector<float>> _map_biomeMap;  // 2d array for biome map
  std::vector<std::vector<float>>
      _map_temperatureMap; // 2d array for temperature map

  std::vector<sf::Vector2f> m_listGrassBlocks;
  std::vector<sf::Texture> listTrees;
  std::vector<sf::RectangleShape> trees;
  sf::Image minimapImage;

  float keyTime;
  float keyTimeMax;
  void updateKeyTime(const float &delta_time);
  const bool getKeyTime();

  /// @brief clear vector with BrickBlocks
  void Clear();
  /// @brief load textures used on the map
  void loadTextuteMap();
  /// @brief generate map using noice and some math
  void generateMap();
  sf::Texture getTreeTexture();

  // create tree on map using x and y position
  void pushTree(int x, int y);
  // load texture for trees
  void initTrees();

  void initMapVariables();

public:
  TileMap(mmath::noiceData datanoice, ProcessGenerationNoice *noice);
  virtual ~TileMap();

  inline const sf::Image &getMinimapImage() { return this->minimapImage; }
  inline const sf::Vector2i &getMapSizeOnTiles() { return this->worldSizeGrid; }
  inline const sf::Vector2i &getMapSizeOnInt() { return this->worldSizeInt; }
  inline const sf::Vector2f &getMapSizeOnFloat() {
    return this->worldSizeFloat;
  }
  inline const rectangleWithOffset &getRenderArea() {
    return this->m_renderArea;
  }

  sf::Vector2f getCollisionDepth(const sf::FloatRect &rectA,
                                 const sf::FloatRect &rectB);

  void updateWorldBoundsCollision(Entity *entity);
  void updateTileCollision(Entity *entity, const float &delta_time);
  void updateAnimationTiles(const float &delta_time);
  void updateRenderArea(const sf::Vector2i &playerPosition_grid);
  void update(Entity *entity, const float &delta_time);

  // get array with grassblock
  std::vector<sf::Vector2f> &getSpawnPosArray() {
    return this->m_listGrassBlocks;
  }

  sf::FloatRect getGlobalBounds(const unsigned int x,
                                const unsigned int Y) const;
  bool getCollision(const unsigned int x, const unsigned int y) const;

  void render(sf::RenderTarget *target);
};
#endif