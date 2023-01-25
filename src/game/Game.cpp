//
// Created by Otso - on 16.11.2022.
//

#include "Game.hpp"
#include <SFML/Graphics.hpp>
#include "MapGrid.hpp"
#include "World.hpp"
#include "MapScene.hpp"
#include "LevelSelect.hpp"
#include "GameTitle.hpp"
#include "GameEnd.hpp"
#include "resource/Resource.hpp"
#include <iostream>

Game::Game() : videomode(1280, 1024),
               window(videomode, "Cats vs Rats TD"),
               textures(),
               renderStates(sf::RenderStates::Default) {
  load();
  scene = std::make_unique<GameTitle>(textures, fonts);
  //scene = std::make_unique<GameEnd>(textures, fonts);
}

void Game::load() {
  //load textures and sounds at start of game, return false if failed
  //set renderStates
  renderStates.transform.scale(1, 1);
  textures.load(Textures::PathTile, "src/media/textures/pathtile.png");
  textures.load(Textures::GrassTile, "src/media/textures/grasstile.png");
  textures.load(Textures::HouseTile, "src/media/textures/house.png");
  textures.load(Textures::FatRat, "src/media/textures/fatrat.png");
  textures.load(Textures::BasicRat, "src/media/textures/basicrat.png");
  textures.load(Textures::FastRat, "src/media/textures/fastrat.png");
  textures.load(Textures::GunCat, "src/media/textures/guncat.png");
  textures.load(Textures::UpgradedGunCat, "src/media/textures/level2guncat.png");
  textures.load(Textures::FreezeCat, "src/media/textures/freezecat.png");
  textures.load(Textures::UpgradedFzeezeCat, "src/media/textures/level2freezecat.png");
  textures.load(Textures::BombCat, "src/media/textures/bombcat.png");
  textures.load(Textures::UpgradedBombCat, "src/media/textures/level2bombcat.png");
  textures.load(Textures::Bullet, "src/media/textures/bullet.png");
  textures.load(Textures::Snowflake, "src/media/textures/snowflake.png");
  textures.load(Textures::Bomb, "src/media/textures/bomb.png");
  textures.load(Textures::Explosion, "src/media/textures/explosion_128.png");
  textures.load(Textures::PlayButton, "src/media/textures/playbutton.png");
  //fonts.load(Fonts::GameTitleFont, "src/media/fonts/SnackerComic_PerosnalUseOnly.ttf");
  fonts.load(Fonts::GameTitleFont, "src/media/fonts/BalonkuRegular-la1w.otf");
  sounds.load(SoundBuffers::EnemyDeath, "src/media/sounds/44429_468340-lq.wav");
  sounds.load(SoundBuffers::Explosion, "src/media/sounds/explosion_sound.mp3");
  sounds.load(SoundBuffers::GunCat, "src/media/sounds/gun_sound.mp3");
  sounds.load(SoundBuffers::BombCatMeow, "src/media/sounds/sadmeow_speedup.mp3");
  sounds.load(SoundBuffers::FreezeCatMeow, "src/media/sounds/freezecat.mp3");
}

void Game::render() {
  //render everything to the screen
  //sf::CircleShape shape(50);
  //shape.setFillColor(sf::Color(150, 50, 250));
  //window.draw(shape);
  window.clear(sf::Color(250, 250, 250)); //????????????????
  window.draw(*scene, renderStates);
  window.display();
}

void Game::processEvents() {
  //handle input from player
  sf::Event event;
  while (window.pollEvent(event)) {
    scene->handleInput(event);
    if (event.type == sf::Event::Closed)
      window.close();
  }
}

void Game::Update(sf::Time deltaTime) {
  //update elements of the game, positions etc.
  scene->update(deltaTime);
}

void Game::run() {
  // Counts time between frames
  sf::Time TimePerFrame = sf::seconds(0.0167); // 1/60=0.0167
  sf::Time deltaTime = sf::Time::Zero;
  // Initialize time to zero
  while (window.isOpen()) {
    handleSceneChange();
    processEvents();
    deltaTime += clock.restart();
    while (deltaTime > TimePerFrame) {
      deltaTime -= TimePerFrame;
      processEvents();
      Update(deltaTime);
    }
    window.clear(sf::Color::White);
    render();
  }
}
void Game::handleSceneChange() {
  if (scene->requestedScene().scene != scene->sceneType()) {
    //std::cout << "Requested: " << scene->requestedScene().scene << " ,sceneType: " <<scene->sceneType << "\n";
    auto request = scene->requestedScene();
    switch (request.scene) {
      case Scenes::ID::GameTitle:scene = std::make_unique<GameTitle>(textures, fonts);
        break;
      case Scenes::ID::MapScene:scene = std::make_unique<MapScene>(textures, fonts, sounds, request.number);
        break;
      case Scenes::ID::LevelSelect:scene = std::make_unique<LevelSelect>(textures, fonts);
        break;
      case Scenes::ID::GameEnd:scene = std::make_unique<GameEnd>(textures, fonts);
        break;
      default:scene = std::make_unique<GameTitle>(textures, fonts);
        break;
    }
  }
}
