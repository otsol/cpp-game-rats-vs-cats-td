//
// Created by Antti - on 06.12.2022.
//

#include "Wave.hpp"

const sf::Time Wave::SPACING_HUGE = sf::milliseconds(1400);
const sf::Time Wave::SPACING_WIDE = sf::milliseconds(1000);
const sf::Time Wave::SPACING_MEDIUM = sf::milliseconds(400);
const sf::Time Wave::SPACING_NARROW = sf::milliseconds(200);

Wave::Wave(TextureHolder &textureholder,
           int textureID,
           int count,
           sf::Time spacing,
           std::map<int, std::pair<int, int>> &pathMarkers,
           int hitPoints,
           float speed) :
    enemyTemplate(Enemy::make(textureholder, textureID, pathMarkers, hitPoints, speed)),
    enemiesLeft(count),
    elapsed_(sf::Time::Zero),
    spacing_(spacing) {
}

EnemyPtr Wave::ifNextEnemy(sf::Time deltaTime) {
  elapsed_ += deltaTime;
  if (enemiesLeft && elapsed_ >= deltaTime) {
    elapsed_ -= spacing_;
    enemiesLeft--;
    return enemyTemplate->clone(enemyTemplate->getTextureHolder(),
                                enemyTemplate->getTextureID(),
                                enemyTemplate->getPathMarkers(),
                                enemyTemplate->getHitPoints(),
                                enemyTemplate->getSpeed());
  }
  return nullptr;
}