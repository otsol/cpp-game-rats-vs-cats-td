//
// Created by Otso - on 9.12.2022.
//

#ifndef MYGAME_SRC_UI_WAVEPAUSE_HPP_
#define MYGAME_SRC_UI_WAVEPAUSE_HPP_
#include <SFML/Graphics/Drawable.hpp>
#include "game/World.hpp"
/**
 * @class WavePause
 * @brief A class for pause button to pause a wave of enemies.
 */
class WavePause : public sf::Drawable {
 public:
  /**
   * @brief The constructor for the WavePause button
   * @param position Button coordinates
   * @param fonts Reference to a FontHolder
   */
  explicit WavePause(const sf::Vector2f &position, FontHolder &fonts);
  void update(World &world, int enemiesNotSpawned);
  void draw(sf::RenderTarget &target, sf::RenderStates states) const override;
  void handleInput(const sf::Event &event, World &world);
 private:
  sf::Text menuString_;
  sf::CircleShape triangle_ = sf::CircleShape(40, 3);
  sf::RectangleShape square_ = sf::RectangleShape(sf::Vector2f(100, 100));
  sf::Vector2<float> mousePosition_ = sf::Vector2f(0.f, 0.f);
};

#endif //MYGAME_SRC_UI_WAVEPAUSE_HPP_
