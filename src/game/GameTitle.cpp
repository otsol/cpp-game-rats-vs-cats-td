//
// Created by Otso - on 6.12.2022.
//
#include <iostream>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/RenderStates.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include "GameTitle.hpp"
static const int tileSize = 64.f;
GameTitle::GameTitle(TextureHolder &textures, FontHolder &fonts) : textures_(textures), fonts_(fonts) {
  showText_ = true;
  // load text resources
  text_.setFont(fonts_.get(Fonts::GameTitleFont));
  //textGameOver_.setFont(font);
  text_.setString("                  Cats vs Rats TD\n"
                  "by: Antti, Henrik, Kasperi and Otso");
  text_.setCharacterSize(43);
  text_.setFillColor(sf::Color::Black);
  text_.setPosition(tileSize * float(width) / 6.f, tileSize * float(height) / 3.f);
  text2_.setFont(fonts_.get(Fonts::GameTitleFont));
  //textGameOver_.setFont(font);
  text2_.setString("Press Enter");
  text2_.setCharacterSize(43);
  text2_.setFillColor(sf::Color::Red);
  text2_.setPosition(tileSize * float(width) / 2.8f, tileSize * float(height) / 2.f);
  // load texture resources
  grassSprite_.setTexture(textures_.get(Textures::GrassTile));

  // create holder for map sprite that consists of multiple
  // small tiles
  mapTex_.clear();
  mapTex_.create(1280, 1024);
  for (int i = 0; i < height; ++i) {
    for (int j = 0; j < width; ++j) {
      grassSprite_.setPosition(static_cast<float>(tileSize * j), static_cast<float>(tileSize * i));
      mapTex_.draw(grassSprite_);
    }
  }
  mapSprite_.setTexture(mapTex_.getTexture());
  mapSprite_.setOrigin({0, mapSprite_.getLocalBounds().height});
  mapSprite_.setScale({1, -1});
  mapSprite_.setColor(sf::Color(255, 255, 255, 64));

  //scene request
  nextScene_.scene = Scenes::ID::GameTitle;
  nextScene_.number = 1;
}

void GameTitle::draw(sf::RenderTarget &target, sf::RenderStates states) const {
  // draw background
  target.draw(mapSprite_);
  //if (showText_) {
  //  target.draw(text_);
  //}
  target.draw(text_);
  target.draw(text2_);

}
void GameTitle::handleInput(const sf::Event &event) {
  if (event.type == sf::Event::EventType::KeyPressed) {
    if (event.key.code == sf::Keyboard::Enter) {
      nextScene_.scene = Scenes::ID::LevelSelect;
    }
  }
  //std::cout << "input";
  //requestSceneChange(SceneChangeRequest { nextScene_ });
}
void GameTitle::update(sf::Time dt) {
  textEffectTime_ += dt;
  if (textEffectTime_ >= sf::seconds(0.1)) {
    showText_ = !showText_;
    text_.setFillColor(showText_ ? sf::Color::Black : sf::Color::Red);
    textEffectTime_ = sf::Time::Zero;
  }
}
sceneRequest GameTitle::requestedScene() {
  return nextScene_;
}
