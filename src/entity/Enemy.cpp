//
// Created by Antti - on 06.12.2022.
//

#include <cmath>
#include <memory>
#include "Enemy.hpp"
#include "SFML/System/Time.hpp"

Enemy::Enemy(TextureHolder &textures, int textureID, std::map<int, std::pair<int, int>> &pathMarkers, int hitPoints, float speed) :
    Entity(textureID, textures),
    textures_(textures),
    pathMarkers_(pathMarkers),
    atFinishTile(false),
    hitPoints_(hitPoints),
    value_(hitPoints),
    speed_(speed),
    slowdownCounter_(0),
    isFrozen(false)
  {
  int tileX = pathMarkers_.at(1).first;
  int tileY = pathMarkers_.at(1).second;

  float coordX = tileX * 64.f;
  float coordY = tileY * 64.f;

  entitySprite.setPosition(coordX, coordY);
  nextMarker = 2;
  //std::cout << "x: " << entitySprite.getPosition().x << " y: " << entitySprite.getPosition().y << std::endl;
}
void Enemy::slowDown() {
  slowdownCounter_ = 0;
  slowdownFactor_ = 0.5f;
  isFrozen = true;
}
void Enemy::update(sf::Time deltaTime, World &world) {

  int finishTileX = pathMarkers_.at(pathMarkers_.size()).first;
  int finishTileY = pathMarkers_.at(pathMarkers_.size()).second;
  float finishCoordX = finishTileX * 64.f;
  float finishCoordY = finishTileY * 64.f;

  if (!(abs(finishCoordX - entitySprite.getPosition().x) <= 4.f && abs(finishCoordY - entitySprite.getPosition().y) <= 4.f)) {

    //Check if has reached next marker
    int nextTileX = pathMarkers_.at(nextMarker).first;
    int nextTileY = pathMarkers_.at(nextMarker).second;
    float nextCoordX = nextTileX * 64.f;
    float nextCoordY = nextTileY * 64.f;

    if (pathMarkers_.size() != nextMarker) {
      if (abs(nextCoordX - entitySprite.getPosition().x) <= 4.f && abs(nextCoordY - entitySprite.getPosition().y) <= 4.f) {
        entitySprite.setPosition(nextCoordX, nextCoordY);
        nextMarker++;
      }
    }

    //Recalculate next marker coordinates in case of nextmarker++
    nextTileX = pathMarkers_.at(nextMarker).first;
    nextTileY = pathMarkers_.at(nextMarker).second;
    nextCoordX = nextTileX * 64.f;
    nextCoordY = nextTileY * 64.f;
    //float movement = round(speed_ * slowdownFactor_);
    float movement = speed_ * slowdownFactor_;

    //Move either along x- or y-axis
    if (entitySprite.getPosition().x == nextCoordX) {
      if (entitySprite.getPosition().y < nextCoordY) {
        entitySprite.move(0.0f, movement);
      } else {
        entitySprite.move(0.0f, -movement);
      }
    } else if (entitySprite.getPosition().y == nextCoordY) {
      if (entitySprite.getPosition().x < nextCoordX) {
        entitySprite.move(movement, 0.0f);
      } else {
        entitySprite.move(-movement, 0.0f);
      }
    }

    // std::cout << "X: " << entitySprite.getPosition().x << ",Y: " << entitySprite.getPosition().y << "\n";
    /*
    std::cout << "getPos x: " << entitySprite.getPosition().x << " y: " << entitySprite.getPosition().y << std::ends;
    std::cout << "   nextCr x: " << nextCoordX << " y: " << nextCoordY << std::ends;
    std::cout << "   nextMarker: " << nextMarker << std::ends;
    std::cout << "   finCr x: " << finishCoordX << " y: " << finishCoordY << std::endl;
    */
   
    slowdownCounter_++;
    // handle slowdown
    if (slowdownFactor_ < 1.0f && slowdownCounter_ >= 100) {
      slowdownFactor_ = 1.0;
      isFrozen = false;
    }
  } else {
    atFinishTile = true;
  }
}

EnemyPtr Enemy::clone(TextureHolder &textures,
                      int textureID,
                      std::map<int, std::pair<int, int>> &pathMarkers,
                      int hitPoints, float speed) const {
  return std::make_shared<Enemy> (textures, textureID, pathMarkers, hitPoints, speed);
}
