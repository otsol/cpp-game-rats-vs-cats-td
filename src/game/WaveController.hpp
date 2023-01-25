//
// Created by Antti - on 06.12.2022.
//

#ifndef MYGAME_SRC_GAME_WAVECONTROLLER_HPP_
#define MYGAME_SRC_GAME_WAVECONTROLLER_HPP_

#include "World.hpp"
#include "Wave.hpp"
/**
 * @class WaveController
 * @brief WaveController controls the current wave and makes a new one when the player is ready
 */
class WaveController {
 public:
  /**
   * @brief Constructor for WaveController
   * @param textureholder Reference to a TextureHolder instance, get enemy textures from here
   * @param pathMarkers map that contains enemy path
   */
  WaveController(TextureHolder &textureholder, std::map<int, std::pair<int, int>> &pathMarkers) :
      waveNumber(0), wave(), textureholder_(textureholder), pathMarkers_(pathMarkers) {};
  /**
   * @brief Checks wave status
   * If player has ordered a new wave, starts it, or if enemies still left in current wave, spawns the next one
   * @param deltaTime time since last update
   * @param world world to spawn enemies in
   */
  void update(sf::Time deltaTime, World &world);
  /**
   * @brief Make a new wave to the world
   * @param waveNumber goes to a switch case, determines how hard the wave will be
   * @return Pointer to the new Wave object
   */
  WavePtr makeNewWave(int waveNumber);
  /**
   * @brief Get current wave number
   * @return current wave number
   */
  int getWaveNumber() const { return waveNumber; }
  /**
   * @brief Get how many enemies there are left in the current wave
   * @return Amount of enemies as an integer
   */
  int getWaveEnemiesLeft() { return wave->getEnemiesLeft(); }

 private:
  TextureHolder &textureholder_;
  std::map<int, std::pair<int, int>> &pathMarkers_;
  int waveNumber;
  WavePtr wave;
};

#endif //MYGAME_SRC_GAME_WAVECONTROLLER_HPP_