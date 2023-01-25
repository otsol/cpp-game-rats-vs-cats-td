//
// Created by Otso - on 6.12.2022.
//
#include <iostream>
#include "LevelSelect.hpp"
static const int tileSize = 64.f;
LevelSelect::LevelSelect(TextureHolder &textures, FontHolder &fonts)
    : textures_(textures), fonts_(fonts) {
  std::vector<std::string> maps;
  for (int i = 0; i < 5; i++) {
    std::string mapfile = "src/media/maps/map";
    mapfile.append(std::to_string(i + 1));
    mapfile.append(".txt");
    std::ifstream infile(mapfile);
    std::string line; //line to store a line of the text file
    std::getline(infile, line); //first line, map name
    maps.push_back(line);
    std::getline(infile, line); //second line, difficulty
    maps[i] = maps[i] + " (" + line + ")";
    infile.close();
  }
  showText_ = true;
  optionIndex = 0;
  // load text resources
  text_.setFont(fonts_.get(Fonts::GameTitleFont));
  //textGameOver_.setFont(font);
  text_.setString("Use Up and Down keys to navigate,\n"
                  "choose Map and press Enter");
  text_.setCharacterSize(30);
  text_.setFillColor(sf::Color::Black);
  text_.setPosition(tileSize * float(width) / 3.8f, tileSize * float(height) / 5.f);
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
  mapSprite_.setColor(sf::Color(255, 255, 255, 128)); // opacity 50%

  // initialize menu options
  sf::Text mapOption1;
  mapOption1.setFont(fonts_.get(Fonts::GameTitleFont));
  mapOption1.setString(maps[0]);
  mapOption1.setPosition(tileSize * float(width) / 3.5f, tileSize * float(height) / 3.5f);
  mapOption1.setFillColor(sf::Color::Red); // optionIndex = 0;
  mapOption1.setCharacterSize(60);
  sf::Text mapOption2;
  mapOption2.setFont(fonts_.get(Fonts::GameTitleFont));
  mapOption2.setString(maps[1]);
  mapOption2.setPosition(tileSize * float(width) / 3.5f, tileSize * float(height) / 3.5f + 100);
  mapOption2.setFillColor(sf::Color::Black);
  mapOption2.setCharacterSize(60);
  sf::Text mapOption3;
  mapOption3.setFont(fonts_.get(Fonts::GameTitleFont));
  mapOption3.setString(maps[2]);
  mapOption3.setPosition(tileSize * float(width) / 3.5f, tileSize * float(height) / 3.5f + 200);
  mapOption3.setFillColor(sf::Color::Black);
  mapOption3.setCharacterSize(60);
  sf::Text mapOption4;
  mapOption4.setFont(fonts_.get(Fonts::GameTitleFont));
  mapOption4.setString(maps[3]);
  mapOption4.setPosition(tileSize * float(width) / 3.5f, tileSize * float(height) / 3.5f + 300);
  mapOption4.setFillColor(sf::Color::Black);
  mapOption4.setCharacterSize(60);
  sf::Text mapOption5;
  mapOption5.setFont(fonts_.get(Fonts::GameTitleFont));
  mapOption5.setString(maps[4]);
  mapOption5.setPosition(tileSize * float(width) / 3.5f, tileSize * float(height) / 3.5f + 400);
  mapOption5.setFillColor(sf::Color::Black);
  mapOption5.setCharacterSize(60);

  options.push_back(mapOption1);
  options.push_back(mapOption2);
  options.push_back(mapOption3);
  options.push_back(mapOption4);
  options.push_back(mapOption5);


  //sf::Text
  // next scene:
//  sceneType.scene = Scenes::ID::LevelSelect;
//  sceneType.number = 0;
  nextScene_.scene = Scenes::ID::LevelSelect;
  nextScene_.number = 1;
}
sceneRequest LevelSelect::requestedScene() {
  return nextScene_;
}
void LevelSelect::draw(sf::RenderTarget &target, sf::RenderStates states) const {
  target.draw(mapSprite_);
  for (const auto &text : options) {
    target.draw(text);
  }
  target.draw(text_);
}
void LevelSelect::handleInput(const sf::Event &event) {
  switch (event.type) {
    case sf::Event::KeyPressed:handlePlayerInput(event.key.code, true);
      break;
    case sf::Event::KeyReleased:handlePlayerInput(event.key.code, false);
      break;
    default:break;
      //case sf::Event::MouseButtonPressed:handlePlayerInput(event.mouseButton, true);
  }
}
void LevelSelect::update(sf::Time dt) {
//  textEffectTime_ += dt;
//  if (textEffectTime_ >= sf::seconds(0.5f))
//  {
//    showText_ = !showText_;
//    textEffectTime_ = sf::Time::Zero;
//  }
}
void LevelSelect::updateOptionText() {
  if (options.empty())
    return;
  // Black all texts
  for (size_t i = 0; i < options.size(); i++) {
    options[i].setFillColor(sf::Color::Black);
  }
  // Red the selected text
  options[optionIndex].setFillColor(sf::Color::Red);
}
void LevelSelect::handlePlayerInput(sf::Keyboard::Key key, bool isPressed) {
  //std::cout << "input: " << key << ", isPressed: " << isPressed << "\n";
  if (isPressed) {
    //std::cout << "START: index is: " << optionIndex << ", key is " << key << "\n";
    if (key == sf::Keyboard::Up) {
      if (optionIndex > 0)
        optionIndex--;
      else
        optionIndex = options.size() - 1;
      updateOptionText();
    } else if (key == sf::Keyboard::Down) {
      if (optionIndex < options.size() - 1)
        optionIndex++;
      else
        optionIndex = 0;
      updateOptionText();
    } else if (key == sf::Keyboard::Enter) {
      nextScene_.scene = Scenes::ID::MapScene;
      nextScene_.number = optionIndex + 1;
      //updateOptionText();
    }
    //std::cout << "END: index is: " << optionIndex << "key is" << key << "\n";
  }

//  switch (event.type) {
//    case sf::Event::MouseButtonPressed:
//      //handlePlayerInput(event.mouseButton, false);
//      break;
//    case sf::Event::MouseButtonReleased:
//      //handlePlayerInput(event.mouseButton, false);
//      break;
  //case sf::Event::MouseMoved:handlePlayerInput(event.)
//    case sf::Event::Closed:
//      window.close();
//      break;
//  }
}
