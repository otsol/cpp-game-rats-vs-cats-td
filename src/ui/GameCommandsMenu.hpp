//
// Created by Otso - on 11.12.2022.
//

#ifndef MYGAME_SRC_UI_GAMECOMMANDSMENU_HPP_
#define MYGAME_SRC_UI_GAMECOMMANDSMENU_HPP_
#include <SFML/Graphics/Drawable.hpp>
#include "resource/Resource.hpp"
#include "SFML/Graphics/Text.hpp"
#include "SFML/Graphics/Texture.hpp"
#include <SFML/Graphics/RenderStates.hpp>
#include "game/World.hpp"
/**
 * @class GameCommandsMenu
 * @brief Shows the player how to play the game (at the right side of the screen in a MapScene)
 */
class GameCommandsMenu : public sf::Drawable {
 public:
  /**
   * @brief Constructor
   * @param textPosition Coordinates for the guide text
   * @param towerPosition Coordinates for the Tower sprites position
   * @param fonts Reference to a FontHolder to get fonts for text
   * @param world Reference to the current Game World
   */
  GameCommandsMenu(const sf::Vector2f &textPosition,
                   const sf::Vector2f &towerPosition,
                   FontHolder &fonts,
                   World &world);
  void draw(sf::RenderTarget &target, sf::RenderStates states) const override;
 private:
  sf::Text menuString_;
  sf::Text towerIndexText_;
  std::vector<sf::Sprite> towerSprites_;
};

#endif //MYGAME_SRC_UI_GAMECOMMANDSMENU_HPP_
