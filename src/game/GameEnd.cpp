//
// Created by Otso - on 8.12.2022.
//

#include <iostream>
#include "GameEnd.hpp"
static const int tileSize = 64.f;
GameEnd::GameEnd(TextureHolder &textures, FontHolder &fonts)
    : textures_(textures), fonts_(fonts) {
  // help text
  textGameOver_.setFont(fonts_.get(Fonts::GameTitleFont));
  textGameOver_.setString("Game Over!");
  textGameOver_.setCharacterSize(50);
  textGameOver_.setFillColor(sf::Color::Black);
  textGameOver_.setPosition(tileSize * float(width) / 3.f, tileSize * float(height) / 4.1f);
  textInstruction_.setFont(fonts_.get(Fonts::GameTitleFont));
  textInstruction_.setString("press Enter to go back to main menu");
  textInstruction_.setCharacterSize(24);
  textInstruction_.setFillColor(sf::Color::Black);
  textInstruction_.setPosition(tileSize * float(width) / 3.f, tileSize * float(height) / 3.4f);

  optionIndex = 0;
  //option for enter and going back to main menu
  sf::Text backToMenuOption;
  backToMenuOption.setFont(fonts_.get(Fonts::GameTitleFont));
  backToMenuOption.setString("Back To Menu");
  backToMenuOption.setPosition(tileSize * float(width) / 2.f, tileSize * float(height) / 3.f);
  backToMenuOption.setFillColor(sf::Color::Red); // optionIndex = 0;
  backToMenuOption.setCharacterSize(60);
  options.push_back(backToMenuOption);

  // nextScene struct for requestedScene
  nextScene_.scene = Scenes::ID::GameEnd;
  nextScene_.number = 1;
}
sceneRequest GameEnd::requestedScene() {
  return nextScene_;
}
void GameEnd::draw(sf::RenderTarget &target, sf::RenderStates states) const {
  for (const auto &text : options) {
    target.draw(text);
  }
  target.draw(textGameOver_);
  target.draw(textInstruction_);
}
void GameEnd::handleInput(const sf::Event &event) {
  switch (event.type) {
    case sf::Event::KeyPressed:handlePlayerInput(event.key.code, true);
      break;
    case sf::Event::KeyReleased:handlePlayerInput(event.key.code, false);
      break;
    default:break;
  }
}
void GameEnd::update(sf::Time dt) {}

void GameEnd::handlePlayerInput(sf::Keyboard::Key key, bool isPressed) {
  if (isPressed) {
    if (key == sf::Keyboard::Enter) {
      nextScene_.scene = Scenes::ID::LevelSelect;
      nextScene_.number = optionIndex + 1;
    }
  }
}