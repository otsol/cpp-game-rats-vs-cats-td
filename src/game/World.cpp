//
// Created by kaspe on 21.11.2022.
//

#include "World.hpp"
#include "SFML/Graphics/RectangleShape.hpp"
#include "SFML/Graphics/CircleShape.hpp"

static const int startMoney = 2000;
static const int startHP = 100;
static const int tileSize = 64.f;
World::World(TextureHolder &textureholder,
             SoundBufferHolder &soundBufferHolder,
             int mapNum,
             std::map<int, std::pair<int, int>> &pathMarkers) :
    grid_(textureholder, mapNum, pathMarkers),
    money_(startMoney),
    hp_(startHP),
    textures(textureholder),
    sounds(soundBufferHolder),
    mapNum_(mapNum),
    towerGrid_() {
  deathSound_.setBuffer(soundBufferHolder.get(SoundBuffers::EnemyDeath));
  explosionSound_.setBuffer(soundBufferHolder.get(SoundBuffers::Explosion));
  endHouse.setTexture(textures.get(Textures::HouseTile));
  // x coords
  float x = float(pathMarkers.rbegin()->second.first) * tileSize;
  // y coords
  float y = float(pathMarkers.rbegin()->second.second) * tileSize;
  endHouse.setPosition(x, y);
  endHouse.setScale(2.f, 2.f);
  endHouse.move(-55.f, -64.f);
}

void World::update(sf::Time deltaTime) {
  if (!paused) {
    //Update all enemies
    update(enemies, deltaTime);
    //Update all towers
    update(towers, deltaTime);
    //Update all projectiles
    update(projectiles, deltaTime);
  }
  //Check which enemies are dead or at finish -> changes money amount
  for (auto &&enemy : enemies) {
    if (!enemy->isAlive()) {
      deathSound_.play();
      this->money_ += enemy->getValue() * 5;
    }
    if (enemy->isAtFinish()) {
      this->hp_ -= enemy->getValue();
    }
  }

  //Clean dead enemies from enemies vector
  clean(enemies);

  //Clean dead projectiles from projectiles vector
  for (auto &&projectile : projectiles) {
    if (projectile->type_ == ProjectileType::Bomb) {
      if (projectile->ifShouldRemove()) {
        explosionSound_.play();
      }
    }
  }
  clean(projectiles);

  // std::cout << "Enemies: " << enemies.size() << "   Towers: " << towers.size() << "   Projectiles: " << projectiles.size() << std::endl;
}

void World::draw(sf::RenderTarget &target, sf::RenderStates states) const {
  target.draw(grid_); //draw map
  draw(towers, target, states); //draw towers
  draw(enemies, target, states); // draw enemies
  target.draw(endHouse);
  draw(projectiles, target, states); // draw projectiles
}

void World::addProjectile(ProjectilePtr &&projectile) {
  projectiles.push_back(std::move(projectile));
}

bool World::addTower(TowerPtr &&tower, int price) {
  if (money_ >= price) {
    money_ -= price;
    //std::cout << "Money left: " << money_ << std::endl;
    //std::cout << "HP left: " << hp_ << std::endl;
    towers.push_back(std::move(tower));
    return true;
  } else
    return false;
}

void World::removeTower(Tower *tower, int price) {
  towers.erase(
      std::find_if(
          towers.begin(),
          towers.end(),
          [tower](const TowerPtr &other) { return other.get() == tower; }
      )
  );
  money_ += price;
  //std::cout << "Money left: " << money_ << std::endl;
  //std::cout << "HP left: " << hp_ << std::endl;
}

Tower *World::getTowerAt(const Sector &target) const {
  auto found = std::find_if(
      towers.cbegin(),
      towers.cend(),
      [&target](const TowerPtr &tower) { return tower->getSector() == target; }
  );
  return found == towers.cend() ? nullptr : &**found;
}
bool World::upgradeTower(Tower *tower, int price) {
  if (money_ >= price) {
    if (tower->upgrade()) money_ -= price;
    return true;
  } else return false;
}
