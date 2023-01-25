//
// Created by Otso - on 11.12.2022.
//

#include "GameCommandsMenu.hpp"
static const int tileSize = 64.f;
GameCommandsMenu::GameCommandsMenu(const sf::Vector2f &textPosition,
                                   const sf::Vector2f &towerPosition,
                                   FontHolder &fonts,
                                   World &world) {
  menuString_.setFont(fonts.get(Fonts::GameTitleFont));
  menuString_.setString("Controls:\n"
                        "Left Click:\n"
                        "   Select location\n"
                        "Right Click:\n"
                        "   sell\n"
                        "Number 1, 2, 3:\n"
                        "   Buy tower type\n"
                        "Number 4:\n"
                        "   Upgrade tower\n"
                        "   (Price:500)");
  menuString_.setCharacterSize(24);
  menuString_.setFillColor(sf::Color::Black);
  menuString_.setPosition(textPosition);
  menuString_.setLineSpacing(0.8f);

  towerIndexText_.setFont(fonts.get(Fonts::GameTitleFont));
  towerIndexText_.setString("1            GunCat\n"
                            "             Price:300\n\n"
                            "2            IceCat\n"
                            "             Price:400\n\n"
                            "3            BombCat\n"
                            "             Price:500");
  towerIndexText_.setCharacterSize(24);
  towerIndexText_.setFillColor(sf::Color::Black);
  towerIndexText_.setPosition(towerPosition);
  towerIndexText_.move(-10.f, 2.f);
  towerIndexText_.setLineSpacing(0.8f);
  // load and set textures
  sf::Sprite tower1;
  tower1.setTexture(world.getTextures().get(Textures::GunCat));
  sf::Sprite tower2;
  tower2.setTexture(world.getTextures().get(Textures::FreezeCat));
  sf::Sprite tower3;
  tower3.setTexture(world.getTextures().get(Textures::BombCat));

  towerSprites_.push_back(tower1);
  towerSprites_.push_back(tower2);
  towerSprites_.push_back(tower3);
  int moveAmount = 0;

  for (auto &tower : towerSprites_) {
    tower.setPosition(towerPosition);
    tower.move(0, tileSize * float(moveAmount));
    moveAmount += 1;
  }

}
void GameCommandsMenu::draw(sf::RenderTarget &target, sf::RenderStates states) const {
  target.draw(menuString_);
  for (auto tower : towerSprites_) {
    target.draw(tower);
  }
  target.draw(towerIndexText_);
}