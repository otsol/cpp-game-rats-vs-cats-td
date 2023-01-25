//
// Created by kaspe on 21.11.2022.
//

#include "MapScene.hpp"

#include <utility>
static const int tileSize = 64.f;
MapScene::MapScene(TextureHolder &textures, FontHolder &fonts, SoundBufferHolder &soundBuffers, int mapNum)
    : textures_(textures), soundBuffers_(soundBuffers), world_(textures, soundBuffers, mapNum, pathMarkers),
      mapNum_(mapNum), waveController_(textures, pathMarkers), fonts_(fonts), towerMenu_(world_),
      statusMenu_(sf::Vector2f(tileSize * float(width) / 0.98f, tileSize * float(height) / 60.f), fonts),
      commandsMenu_(sf::Vector2f(tileSize * float(width) / 0.98f, tileSize * float(height) / 2.2f),
                    sf::Vector2f(tileSize * float(width) / 0.98f, tileSize * float(height) / 1.35f),
                    fonts, world_),
      waveStart_(sf::Vector2f(tileSize * float(width) / 0.98f, tileSize * float(height) / 5.f), fonts),
      wavePause_(sf::Vector2f(tileSize * float(width) / 0.98f, tileSize * float(height) / 2.9f), fonts) {
  //world_ = World(textures_, soundBuffers, mapNum, pathMarkers);
  fpsText.setFont(fonts_.get(Fonts::GameTitleFont));
  fpsText.setString("updates / second");
  fpsText.setCharacterSize(30);
  fpsText.setFillColor(sf::Color::Black);
  fpsText.setPosition(tileSize * float(width) / 30.f, tileSize * float(height) / 60.f);
  // initialize scene request struct
  nextScene_.scene = Scenes::ID::MapScene;
  nextScene_.number = 1;
}

void MapScene::draw(sf::RenderTarget &target, sf::RenderStates states) const {
  world_.draw(target, states);
  //target.draw(fpsText);
  towerMenu_.draw(target, states);
  statusMenu_.draw(target, states);
  commandsMenu_.draw(target, states);
  waveStart_.draw(target, states);
  wavePause_.draw(target, states);
}
void MapScene::handleInput(const sf::Event &event) {
  //towerMenu_.handleInput(event, world_);
  towerMenu_.handleInput(event, world_);
  waveStart_.handleInput(event, world_);
  wavePause_.handleInput(event, world_);
}
void MapScene::update(sf::Time deltaTime) {
  world_.update(deltaTime);
  if (!world_.paused) waveController_.update(deltaTime, world_);
  double fps = 1.0 / deltaTime.asSeconds();
  fpsText.setString(std::to_string(fps));
  statusMenu_.update(world_, waveController_.getWaveEnemiesLeft(), waveController_.getWaveNumber());
  waveStart_.update(world_, waveController_.getWaveEnemiesLeft());
  // check if game is over
  if (world_.getHP() <= 0) {
    nextScene_.scene = Scenes::ID::GameEnd;
  }
}
sceneRequest MapScene::requestedScene() {
  return nextScene_;
}
