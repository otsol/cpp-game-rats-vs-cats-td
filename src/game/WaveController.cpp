//
// Created by Antti - on 06.12.2022.
//

#include "WaveController.hpp"
#include <iostream>

sf::Time delayTime = sf::seconds(0.0167);

void WaveController::update(sf::Time deltaTime, World &world) {
  //Add an Enemy to World::enemies
  if (!wave || (wave->isEmpty() && world.getEnemies().empty())) {
    if (world.isReadyForNextWave) {
      world.isReadyForNextWave = false;
      wave = makeNewWave(++waveNumber);
    } else {
      wave = std::make_unique<Wave>(textureholder_, Textures::BasicRat, 0, Wave::SPACING_HUGE, pathMarkers_, 2, 1.0f);
    }

  }
  auto next = wave->ifNextEnemy(delayTime);

  //if not nullptr
  if (next && !world.paused) {
    world.getEnemies().push_back(std::move(next));
  }
}

WavePtr WaveController::makeNewWave(int waveNumber) {
  //Wave format: textureholder, textureID, amount of enemies, spacing of enemies, path markers to follow, hitpoints of enemies

  switch (waveNumber) {
    case 1:
      return std::make_unique<Wave>(textureholder_,
                                    Textures::BasicRat,
                                    10,
                                    Wave::SPACING_HUGE,
                                    pathMarkers_,
                                    4,
                                    2.f);
    case 2:
      return std::make_unique<Wave>(textureholder_,
                                    Textures::BasicRat,
                                    20,
                                    Wave::SPACING_HUGE,
                                    pathMarkers_,
                                    4,
                                    2.f);
    case 3:
      return std::make_unique<Wave>(textureholder_,
                                    Textures::BasicRat,
                                    40,
                                    Wave::SPACING_WIDE,
                                    pathMarkers_,
                                    4,
                                    2.f);
    case 4:
      return std::make_unique<Wave>(textureholder_,
                                    Textures::BasicRat,
                                    40,
                                    Wave::SPACING_MEDIUM,
                                    pathMarkers_,
                                    4,
                                    2.f);
    case 5:
      return std::make_unique<Wave>(textureholder_,
                                    Textures::FastRat,
                                    30,
                                    Wave::SPACING_WIDE,
                                    pathMarkers_,
                                    2,
                                    4.f);
    case 6:
      return std::make_unique<Wave>(textureholder_,
                                    Textures::FastRat,
                                    50,
                                    Wave::SPACING_MEDIUM,
                                    pathMarkers_,
                                    2,
                                    4.f);
    case 7:
      return std::make_unique<Wave>(textureholder_,
                                    Textures::FastRat,
                                    100,
                                    Wave::SPACING_MEDIUM,
                                    pathMarkers_,
                                    2,
                                    4.f);
    case 8:
      return std::make_unique<Wave>(textureholder_,
                                    Textures::FastRat,
                                    150,
                                    Wave::SPACING_NARROW,
                                    pathMarkers_,
                                    2,
                                    4.f);
    case 9:
      return std::make_unique<Wave>(textureholder_,
                                    Textures::BasicRat,
                                    100,
                                    Wave::SPACING_MEDIUM,
                                    pathMarkers_,
                                    4,
                                    2.f);
    case 10:
      return std::make_unique<Wave>(textureholder_,
                                    Textures::FatRat,
                                    10,
                                    Wave::SPACING_HUGE,
                                    pathMarkers_,
                                    30,
                                    1.f);
    case 11:
      return std::make_unique<Wave>(textureholder_,
                                    Textures::FatRat,
                                    20,
                                    Wave::SPACING_WIDE,
                                    pathMarkers_,
                                    40,
                                    1.f);
    case 12:
      return std::make_unique<Wave>(textureholder_,
                                    Textures::FatRat,
                                    40,
                                    Wave::SPACING_WIDE,
                                    pathMarkers_,
                                    50,
                                    1.f);
    case 20:
      return std::make_unique<Wave>(textureholder_,
                                    Textures::FatRat,
                                    5,
                                    Wave::SPACING_HUGE,
                                    pathMarkers_,
                                    10000,
                                    4.f);
    default:
      if (waveNumber % 2)
        return std::make_unique<Wave>(textureholder_,
                                      Textures::FatRat,
                                      50,
                                      Wave::SPACING_WIDE,
                                      pathMarkers_,
                                      waveNumber * 10,
                                      1.f);
      else
        return std::make_unique<Wave>(textureholder_,
                                      Textures::FastRat,
                                      waveNumber * 20,
                                      Wave::SPACING_NARROW,
                                      pathMarkers_,
                                      waveNumber,
                                      4.f);
  }

}