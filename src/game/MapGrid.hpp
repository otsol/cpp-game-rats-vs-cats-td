//
// Created by kaspe on 21.11.2022.
//

#ifndef MYGAME_SRC_GAME_MAPGRID_HPP_
#define MYGAME_SRC_GAME_MAPGRID_HPP_
#include <vector>
#include "SFML/Graphics/RenderTarget.hpp"
#include "SFML/Graphics/Drawable.hpp"
#include "resource/Resource.hpp"
#include "SFML/Graphics/RenderTexture.hpp"
#include "SFML/Graphics/Sprite.hpp"
/**
 * @class MapGrid
 * @brief The game map consists of blocks, this class handles reading maps from file and rendering the grid
 */
class MapGrid : public sf::Drawable {
 public:
  /**
   * @brief Constructor for the class
   * @param textureholder Reference to Resource class instance that holds textures for the map
   * @param mapNum Which map to load from file (file=map(mapNum).txt)
   * @param pathMarkers Map that will hold the enemy pathMarkers for this map
   */
  MapGrid(TextureHolder &textureholder, int mapNum, std::map<int, std::pair<int, int>> &pathMarkers);
  /**
   * @brief Find out if a block is road or not
   * @param x x-coordinate of the block (in blocks)
   * @param y y-coordinate of the block (in blocks)
   * @return 0=grass,1=road
   */
  int getBlockAt(int x, int y) const { return map[y][x]; }
  /**
   * @brief set a row of map blocks. Used by the constructor when reading a map
   * @param row row number to change
   */
  void setBlockRow(std::vector<int> &row) { map.emplace_back(row); }
  /**
   * @brief draw the scene to target
   * @param target sf::RenderTarget to draw the scene to
   * @param states sf::RenderStates object for drawing
   */
  virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const override;
  /**
   * @brief Get map width
   * @return map width
   */
  int getWidth() const { return width; }
  /**
   * @brief Get map height
   * @return map height
   */
  int getHeight() const { return height; }
 private:
  int width = 16;
  int height = 16;
  std::string diff;
  std::string name;
  std::vector<std::vector<int>> map; //matrix for blocks, 0=grass, 1=road
  std::map<int, std::pair<int, int>> &pathMarkers_; //location of path corners, enemies follow these
  TextureHolder &textures_;
  sf::RenderTexture mapTex_;
  sf::Sprite mapSprite_;
  int mapNum_;
};

#endif //MYGAME_SRC_GAME_MAPGRID_HPP_
