#pragma once
#include <SFML/Graphics/Drawable.hpp>
#include "Sector.hpp"
#include <SFML/Graphics/RectangleShape.hpp>
#include "entity/Tower.hpp"
/**
 * @class TowerMenu
 * @brief TowerMenu class allows the player to buy and upgrade towers.
 * Controls: Left click to select a Sector.
 * Right click to sell a tower at selected Sector.
 * 1 to buy tower 1 (GunCat)
 * 2 to buy tower 2 (FreezeCat)
 * 3 to buy tower 3 (BombCat)
 * 4 to upgrade tower in selected Sector
 */
class TowerMenu : public sf::Drawable {
 public:
  TowerMenu(World &world);
  virtual ~TowerMenu() {}
  /**
   * @brief handle player input
   * @param event Player did something
   * @param world Current World
   * Controls: Left click to select a Sector.
   * Right click to sell a tower at selected Sector.
   * 1 to buy tower 1 (GunCat)
   * 2 to buy tower 2 (FreezeCat)
   * 3 to buy tower 3 (BombCat)
   * 4 to upgrade tower in selected Sector
   */
  void handleInput(const sf::Event &event, World &world);
  void update(World &world, const sf::Vector2f &mousePosition);
  /**
   * @brief Draw a square to show which Sector is selected
   * @param target sf::RenderTarget to draw the scene to
   * @param states sf::RenderStates object for drawing
   */
  void draw(sf::RenderTarget &target, sf::RenderStates states) const override;
 private:
  Sector selectedSector;
  sf::RectangleShape hoverIndicator;
  bool showSectorIndicator;
  sf::RectangleShape sectorIndicator;
  sf::CircleShape rangeIndicator;
};
