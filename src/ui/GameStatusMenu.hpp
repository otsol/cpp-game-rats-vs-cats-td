//
// Created by Otso - on 9.12.2022.
//

#ifndef MYGAME_SRC_UI_GAMESTATUSMENU_HPP_
#define MYGAME_SRC_UI_GAMESTATUSMENU_HPP_
#include <SFML/Graphics/Drawable.hpp>
#include "game/World.hpp"
/**
 * @class GameStatusMenu
 * @brief Shows the player information from the game world: hp, money, enemies left and wave number
 */
class GameStatusMenu : public sf::Drawable {
 public:
  explicit GameStatusMenu(const sf::Vector2f &position, FontHolder &fonts);
  /**
   * @brief Update The status menu numbers
   * @param world
   * @param enemiesNotSpawned enemies left in current wave that haven't spawned yet
   * @param waveNumber current wave number
   */
  void update(World &world, int enemiesNotSpawned, int waveNumber);
  /**
   * @brief draw the status menu to screen
   * @param target sf::RenderTarget to draw the statusmenu to
   * @param states sf::RenderStates object for drawing
   */
  void draw(sf::RenderTarget &target, sf::RenderStates states) const override;
 private:
  sf::Text menuString_;
};

#endif //MYGAME_SRC_UI_GAMESTATUSMENU_HPP_
