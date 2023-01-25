//
// Created by Otso - on 9.12.2022.
//

#ifndef MYGAME_SRC_UI_WAVESTART_HPP_
#define MYGAME_SRC_UI_WAVESTART_HPP_
#include <SFML/Graphics/Drawable.hpp>
#include "game/World.hpp"
/**
 * @class WaveStart
 * @brief A class for the button to start next wave.
 */
class WaveStart : public sf::Drawable {
 public:
  /**
   * @brief The constructor for the WaveStart button
   * @param position Button coordinates
   * @param fonts Reference to a FontHolder
   */
  explicit WaveStart(const sf::Vector2f &position, FontHolder &fonts);
  void update(World &world, int enemiesNotSpawned);
  void draw(sf::RenderTarget &target, sf::RenderStates states) const override;
  void handleInput(const sf::Event &event, World &world);
 private:
  sf::Text menuString_;
  sf::CircleShape triangle_ = sf::CircleShape(40, 3);
  sf::RectangleShape square_ = sf::RectangleShape(sf::Vector2f(100, 100));
  sf::Vector2<float> mousePosition_ = sf::Vector2f(0.f, 0.f);
};

#endif //MYGAME_SRC_UI_WAVESTART_HPP_
