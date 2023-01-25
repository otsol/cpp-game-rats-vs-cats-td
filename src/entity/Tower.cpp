#include "Tower.hpp"
#include <SFML/Graphics/RenderTarget.hpp>
#include "game/World.hpp"
#include "SFML/System/Time.hpp"
#include "SFML/Audio/Sound.hpp"

sf::Time frameDelay = sf::seconds(0.0167);

Tower::Tower(TextureHolder& textures,
             SoundBufferHolder& sounds,
             int textureID,
             Sector sector,
             int damage,
             float range,
             sf::Time shootDelay,
             int price,
             TowerType towerType) :
  Entity(textureID, textures),
  textures_(textures),
  sounds_(sounds),
  sector(sector),
  damage(damage),
  range(range),
  shootDelay(shootDelay),
  timeSinceFiring(sf::Time::Zero),
  price(price),
  type(towerType), 
  upgradeable(true),
  bombRange(150.f),
  velocity_(10.f)
{
  entitySprite.setPosition(sector.x, sector.y);
  soundBullet_.setBuffer(sounds.get(SoundBuffers::GunCat));
  soundBullet_.setVolume(50.f);
  soundBomb_.setBuffer(sounds.get(SoundBuffers::BombCatMeow));
  soundSnow_.setBuffer(sounds.get(SoundBuffers::FreezeCatMeow));
  if (towerType == TowerType::FreezeCat) {
    upgradeable = false;
  }
}

void Tower::update(sf::Time deltaTime, World &world) {
  timeSinceFiring += frameDelay;
  //std::cout << "timeSinceFiring: " << timeSinceFiring.asSeconds() << "   deltaTime: " << deltaTime.asSeconds() << "   shootDelay: " << shootDelay.asSeconds() << std::endl;
  
  if (timeSinceFiring < shootDelay) {
    return;
  }

  if (timeSinceFiring >= shootDelay) {
    std::pair<float, std::shared_ptr<Enemy>> closestEnemy = getClosestEnemy(world);
    if (closestEnemy.second != nullptr && inRange(closestEnemy.second->getPosition(), range)) {
      if (type == TowerType::GunCat) {
        // Shoot Bullet
        world.addProjectile(Projectile::make(textures_, Textures::Bullet, ProjectileType::Bullet, sector, closestEnemy, getClosestEnemies(world), getNeighbourEnemies(closestEnemy, world), 1.f, damage, velocity_));
        soundBullet_.play();
        timeSinceFiring = sf::Time::Zero;
      }
      else if (type == TowerType::FreezeCat) {
        // Shoot Freeze
        world.addProjectile(Projectile::make(textures_, Textures::Snowflake, ProjectileType::FreezeGun, sector, closestEnemy, getClosestEnemies(world), getNeighbourEnemies(closestEnemy, world), range, damage, velocity_));
        soundSnow_.play();
        timeSinceFiring = sf::Time::Zero;
      }
      else if (type == TowerType::BombCat) {
        // Shoot Bomb
        world.addProjectile(Projectile::make(textures_, Textures::Bomb, ProjectileType::Bomb, sector, closestEnemy, getClosestEnemies(world), getNeighbourEnemies(closestEnemy, world), bombRange, damage, velocity_));
        soundBomb_.play();
        timeSinceFiring = sf::Time::Zero;
      }
    }
    timeSinceFiring = sf::Time::Zero;
  }
}

std::pair<float, std::shared_ptr<Enemy>> Tower::getClosestEnemy(World& world) {
  std::shared_ptr<Enemy> closestEnemy = nullptr;
  float closestDistance = 0.0;

  float towerX = entitySprite.getPosition().x;
  float towerY = entitySprite.getPosition().y;

  for (auto&& enemy : world.getEnemies()) {

    float enemyX = enemy->getPosition().x;
    float enemyY = enemy->getPosition().y;

    float distanceX = abs(enemyX - towerX);
    float distanceY = abs(enemyY - towerY);

    float distance = sqrt(distanceX * distanceX + distanceY * distanceY);

    if (closestDistance == 0.0 || distance < closestDistance) {
      closestEnemy = enemy;
      closestDistance = distance;
    }
  }
  //std::cout << closestDistance << std::endl;
  return std::make_pair(closestDistance, closestEnemy);
}

std::map<int, std::pair<float, std::shared_ptr<Enemy>>> Tower::getClosestEnemies(World& world) {
  std::map<float, std::shared_ptr<Enemy>> enemyDistances;

  float towerX = entitySprite.getPosition().x;
  float towerY = entitySprite.getPosition().y;
  for (const auto& enemy : world.getEnemies()) {
    float enemyX = enemy->getPosition().x;
    float enemyY = enemy->getPosition().y;  
    float distanceX = abs(enemyX - towerX);
    float distanceY = abs(enemyY - towerY);
    float distance = sqrt(distanceX * distanceX + distanceY * distanceY);
    enemyDistances.insert(std::make_pair(distance, std::shared_ptr<Enemy>(enemy)));
  }
  std::map<int, std::pair<float, std::shared_ptr<Enemy>>> closestEnemies;
  int counter = 0;
  for (std::map<float, std::shared_ptr<Enemy>>::iterator enemy = enemyDistances.begin(); enemy != enemyDistances.end(); enemy++) {
    // Sort into result
    closestEnemies[counter] = std::make_pair(enemy->first, std::shared_ptr<Enemy>(enemy->second));
    counter++;
  }
  
  return closestEnemies;
}

std::map<int, std::pair<float, std::shared_ptr<Enemy>>> Tower::getNeighbourEnemies(std::pair<float, std::shared_ptr<Enemy>> closestEnemy, World& world) {
  std::map<float, std::shared_ptr<Enemy>> enemyDistances;

  float closestEnemyX = closestEnemy.second->getPosition().x;
  float closestEnemyY = closestEnemy.second->getPosition().y;
  for (auto& enemy : world.getEnemies()) {
    float enemyX = enemy->getPosition().x;
    float enemyY = enemy->getPosition().y;  
    float distanceX = abs(enemyX - closestEnemyX);
    float distanceY = abs(enemyY - closestEnemyY);
    float distance = sqrt(distanceX * distanceX + distanceY * distanceY);
    if (enemy != closestEnemy.second) {
      enemyDistances.insert(std::make_pair(distance, std::shared_ptr<Enemy>(enemy)));
    }
  }
  std::map<int, std::pair<float, std::shared_ptr<Enemy>>> neighbourEnemies;
  int counter = 0;
  for (std::map<float, std::shared_ptr<Enemy>>::iterator enemy = enemyDistances.begin(); enemy != enemyDistances.end(); enemy++) {
    // Sort into result
    neighbourEnemies[counter] = std::make_pair(enemy->first, std::shared_ptr<Enemy>(enemy->second));
    counter++;
  }
  
  return neighbourEnemies;
}

bool Tower::inRange(const sf::Vector2f enemyPos, float range) {
  float enemyX = enemyPos.x;
  float enemyY = enemyPos.y;
  float towerX = entitySprite.getPosition().x;
  float towerY = entitySprite.getPosition().y;
  float distanceX = abs(enemyX - towerX);
  float distanceY = abs(enemyY - towerY);
  float distance = sqrt(distanceX * distanceX + distanceY * distanceY);
  if (distance <= range) {
    return true;
  }
  else
    return false;
}

bool Tower::upgrade() {
  if (type == TowerType::GunCat) {
    damage = damage * 2;
    velocity_ = velocity_ * 1.5;
    shootDelay = sf::seconds(1);
    entitySprite.setTexture(textures_.get(Textures::UpgradedGunCat));
    upgradeable = false;
    return true;
  }
  else if (type == TowerType::FreezeCat) {
    range = 350.f;
    velocity_ = velocity_ * 1.5;
    shootDelay = sf::seconds(1);
    entitySprite.setTexture(textures_.get(Textures::UpgradedFzeezeCat));
    upgradeable = false;
    return true;
  }
  else if (type == TowerType::BombCat) {
    bombRange = 200.f;
    shootDelay = sf::seconds(2);
    entitySprite.setTexture(textures_.get(Textures::UpgradedBombCat));
    upgradeable = false;
    return true;
  }
  else
    return false;
}