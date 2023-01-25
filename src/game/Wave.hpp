//
// Created by Antti - on 06.12.2022.
//
#ifndef MYGAME_SRC_GAME_WAVE_HPP_
#define MYGAME_SRC_GAME_WAVE_HPP_
#include "entity/Enemy.hpp"
#include <SFML/System/Time.hpp>
#include <iostream>

class Wave;
using WavePtr = std::unique_ptr<Wave>;
/**
 * @class Wave
 * @brief A class for a single wave of enemies. A wave can be started by a player with a button.
 */
class Wave {
 public:
  /**
   * @brief Large time difference for spawning enemies
   */
  static const sf::Time SPACING_HUGE;
  static const sf::Time SPACING_WIDE;
  static const sf::Time SPACING_MEDIUM;
  /**
   * @brief narrow time difference for spawning enemies
   */
  static const sf::Time SPACING_NARROW;
  /**
   * @brief Constructor for a Wave
   * @param textureholder Reference to TextureHolder object for textures
   * @param textureID What texture to use for this wave of enemies (same for all)
   * @param count How many enemies to spawn
   * @param spacing How close to each other should enemies be
   * @param pathMarkers Path for enemies
   * @param hitPoints Enemy hitpoints (same for all)
   * @param speed How fast enemies should be (same for all)
   */
  Wave(TextureHolder &textureholder,
       int textureID,
       int count,
       sf::Time spacing,
       std::map<int, std::pair<int, int>> &pathMarkers,
       int hitPoints,
       float speed);
  /**
   * @brief if next enemy should spawn this function returns it
   * @param deltaTime time since last frame
   * @return Pointer to next incoming enemy, if shouldn't spawn yet return nullptr
   */
  EnemyPtr ifNextEnemy(sf::Time deltaTime);
  /**
   * @brief is the current wave done
   * @return If there are no incoming enemies left, return true, else false
   */
  bool isEmpty() const { return enemiesLeft <= 0; }
  /**
   * @brief return amount of enemies left during this wave (shown in UI etc.)
   * @return integer, how many enemies left
   */
  int getEnemiesLeft() { return enemiesLeft; }

 private:
  int enemiesLeft;
  EnemyPtr enemyTemplate;
  sf::Time spacing_;
  sf::Time elapsed_;
};

#endif //MYGAME_SRC_GAME_WAVE_HPP_