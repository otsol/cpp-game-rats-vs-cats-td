#include "Projectile.hpp"

#include <utility>

Projectile::Projectile(TextureHolder &textures, int textureID, ProjectileType type, Sector start, const std::pair<float, std::shared_ptr<Enemy>>& closestEnemy, const std::map<int, std::pair<float, std::shared_ptr<Enemy>>>& closestEnemies, std::map<int, std::pair<float, std::shared_ptr<Enemy>>> neighbourEnemies, float range, int damage, float velocity) :
    Entity(textureID, textures),
    textures_(textures),
    type_(type),
    start_(start),
    closestEnemy_(closestEnemy),
    neighbourEnemies_(std::move(neighbourEnemies)),
    range_(range),
    damage_(damage),
    velocity_(velocity),
    distanceCovered(0.f),
    distance(closestEnemy.first),
    atFinish(false)
{

  for (auto const& [key, value] : closestEnemies) {
    std::shared_ptr pTemp (value.second);
    std::pair <int, std::pair<float, std::shared_ptr<Enemy>>> p = {key, {value.first, pTemp}};
    closestEnemies_.insert(p);
  }
  for (auto const& [key, value] : neighbourEnemies_) {
    std::shared_ptr pTemp (value.second);
    std::pair <int, std::pair<float, std::shared_ptr<Enemy>>> p = {key, {value.first, pTemp}};
    neighbourEnemies_.insert(p);
  }

  if (type == ProjectileType::Bomb) {

    entitySprite.setPosition((float)start_.x , (float)start_.y);
  }
  else {
    entitySprite.setPosition((float)start_.x + 32.f , (float)start_.y + 32.f);
  }
}

void Projectile::update(sf::Time deltaTime, World &world) {
  //closestEnemies_= getClosestEnemies(world);
  if(closestEnemy_.second==nullptr) {return;}
  float enemyX = closestEnemy_.second->getPosition().x;
  float enemyY = closestEnemy_.second->getPosition().y;
  //std::shared_ptr<Enemy> freezeEnemy=nullptr;
  std::shared_ptr<Enemy> freezeEnemy (closestEnemy_.second);
  if (type_ == ProjectileType::FreezeGun) {
    for (int i = 0; i < closestEnemies_.size(); i++) {
      if (closestEnemies_[i].second!=nullptr && closestEnemies_[i].first <= range_) {
        if (closestEnemies_[i].second->isNotFrozen()) {
          enemyX = closestEnemies_[i].second->getPosition().x;
          enemyY = closestEnemies_[i].second->getPosition().y;
          freezeEnemy = closestEnemies_[i].second;
          break;
        }
      }
    }
  }

  auto towerX = float(start_.x);
  auto towerY = float(start_.y);
  float distanceX = abs(enemyX - towerX);
  float distanceY = abs(enemyY - towerY);

  float factorX = distanceX / distance;
  float factorY = distanceY / distance;

  float velocityX = velocity_ * factorX;
  float velocityY = velocity_ * factorY;

  if (enemyX < towerX) {
    velocityX = -velocityX;
  }
  if (enemyY < towerY) {
    velocityY = -velocityY;
  }

  //std::cout << "DistanceCovered: " << distanceCovered << "   Distance: " << distance <<std::endl;
  //std::cout << entitySprite.getPosition().x << "," << entitySprite.getPosition().y << std::endl;
  //std::cout << velocityX << "," << velocityY << std::endl;

  if (type_ == ProjectileType::Bullet) {
    if (distanceCovered <= distance) {
      entitySprite.move(velocityX, velocityY);
      distanceCovered += velocity_;
    }
    else {
      if (closestEnemy_.second != nullptr) {
        closestEnemy_.second->takeDamage(damage_);
      }
      atFinish = true;
    }
  }
  else if (type_ == ProjectileType::FreezeGun) {
    if (distanceCovered <= distance) {
      entitySprite.move(velocityX, velocityY);
      distanceCovered += velocity_;
    }
    else {
      if (freezeEnemy != nullptr) {
        freezeEnemy->slowDown();
        freezeEnemy->takeDamage(damage_);
      }
      atFinish = true;
    }
  }
  else if (type_ == ProjectileType::Bomb) {
    //Explosion texture
    if (distance-distanceCovered <= 30.f) {
      entitySprite.setTexture(textures_.get(Textures::Explosion));
    }
    //Check if at finish
    if (distanceCovered <= distance) {
      entitySprite.move(velocityX, velocityY);
      distanceCovered += velocity_;
    }
    else {
      //Closest enemy takes damage
      if (closestEnemy_.second != nullptr) {
        closestEnemy_.second->takeDamage(damage_);
      }

      //Other enemies inside range take damage as well
      for (auto enemy : neighbourEnemies_) {
        //std::cout << enemy.second.first << std::endl;
        if (enemy.second.first <= range_) {
          if (enemy.second.second != nullptr) {
            enemy.second.second->takeDamage(damage_);
          }
        }
      }
      atFinish = true;
    }
  }
  //std::cout << "DistanceCovered: " << distanceCovered << "   Distance: " << distance <<std::endl;
}
ProjectilePtr Projectile::make(TextureHolder &textures,
                               int textureID,
                               ProjectileType type,
                               Sector start,
                               const std::pair<float, std::shared_ptr<Enemy>>& closestEnemy,
                               const std::map<int, std::pair<float, std::shared_ptr<Enemy>>>& closestEnemies,
                               const std::map<int, std::pair<float, std::shared_ptr<Enemy>>>& neighbourEnemies,
                               float range,
                               int damage,
                               float velocity) {
  std::map<int, std::pair<float, std::shared_ptr<Enemy>>> closestEnemiesTemp;
  for (auto const& [key, value] : neighbourEnemies) {
    std::shared_ptr pTemp (value.second);
    std::pair <int, std::pair<float, std::shared_ptr<Enemy>>> p = {key, {value.first, pTemp}};
    closestEnemiesTemp.insert(p);
  }
  std::map<int, std::pair<float, std::shared_ptr<Enemy>>> neighbourEnemiesTemp;
  for (auto const& [key, value] : neighbourEnemies) {
    std::shared_ptr pTemp (value.second);
    std::pair <int, std::pair<float, std::shared_ptr<Enemy>>> p = {key, {value.first, pTemp}};
    neighbourEnemiesTemp.insert(p);
  }
  return std::make_unique<Projectile>(textures, textureID, type, start, closestEnemy, closestEnemiesTemp, neighbourEnemiesTemp, range, damage, velocity);
}
