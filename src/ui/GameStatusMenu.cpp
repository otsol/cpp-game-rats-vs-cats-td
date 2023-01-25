//
// Created by Otso - on 9.12.2022.
//

#include "GameStatusMenu.hpp"
#include <sstream>      // std::stringstream
GameStatusMenu::GameStatusMenu(const sf::Vector2f &position, FontHolder &fonts) {
  menuString_.setFont(fonts.get(Fonts::GameTitleFont));
  menuString_.setString("GameStatusMenu");
  menuString_.setCharacterSize(24);
  menuString_.setFillColor(sf::Color::Black);
  menuString_.setPosition(position);
}
void GameStatusMenu::update(World &world, int enemiesNotSpawned, int waveNumber) {
  std::stringstream ss;
  ss << "Wave Number: " << waveNumber << "\n"
     << "Enemies Left: " << (world.getEnemies().size() + enemiesNotSpawned) << "\n"
     << "Hit Points: " << world.getHP() << "\n"
     << "Money: " << world.getMoney() << "\n";
  menuString_.setString(ss.str());

}
void GameStatusMenu::draw(sf::RenderTarget &target, sf::RenderStates states) const {
  target.draw(menuString_);
}
