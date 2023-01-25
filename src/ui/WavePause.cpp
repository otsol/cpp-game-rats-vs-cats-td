//
// Created by Otso - on 9.12.2022.
//

#include "WavePause.hpp"
WavePause::WavePause(const sf::Vector2f &position, FontHolder &fonts) :
    mousePosition_(sf::Vector2f(0.f, 0.f)) {
  //mousePosition_ = sf::V
  menuString_.setFont(fonts.get(Fonts::GameTitleFont));
  menuString_.setString("Pause Game");
  menuString_.setCharacterSize(24);
  menuString_.setFillColor(sf::Color::Black);
  menuString_.setPosition(position);
  menuString_.move(0.f, -40.f);

  triangle_.setPosition(position);
  triangle_.setOutlineThickness(5);
  triangle_.setFillColor(sf::Color::Green);
  triangle_.setOutlineColor(sf::Color::Black);
  triangle_.setRotation(90.f);
  triangle_.move(80.f, 12.f);
  square_.setPosition(position);
  square_.setOutlineThickness(3);
  square_.setOutlineColor(sf::Color::Black);
}
void WavePause::update(World &world, int enemiesNotSpawned) {
  //std::cout << "Is ready: " << world.isReadyForNextWave << "\n";
  triangle_.setFillColor(sf::Color::Green);
}
void WavePause::draw(sf::RenderTarget &target, sf::RenderStates states) const {
  target.draw(menuString_);
  target.draw(square_);
  target.draw(triangle_);
}
void WavePause::handleInput(const sf::Event &event, World &world) {
  // left click
  if (event.type == sf::Event::MouseButtonPressed
      && event.mouseButton.button == sf::Mouse::Button::Left) {
    // inside square bounds
    if (square_.getGlobalBounds().contains(
        sf::Vector2f(event.mouseButton.x, event.mouseButton.y))) {
      world.paused = !world.paused;
      triangle_.setFillColor(world.paused ? sf::Color(200, 200, 200) : sf::Color::Green);
      menuString_.setString(world.paused ? "Paused" : "Pause Game");
    }
  }
}

