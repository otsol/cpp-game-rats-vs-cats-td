#pragma once
#include "Sector.hpp"
#include <vector>
#include <SFML/Graphics/Drawable.hpp>
#include "entity/Tower.hpp"
/**
 * @class Grid
 * @brief Grid is used to place the towers according to the visual tiles.
 */
class Grid : public sf::Drawable {
 public:
  Grid();
  virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const override;
  /**
   * @brief Get selected Sector. Used in TowerMenu class to change where to place a tower.
   * @return
   */
  Sector *getSelectedSector();
 private:
  int width;
  int height;
  Sector *selectedSector;
  std::vector<std::vector<int>> blocks;
};