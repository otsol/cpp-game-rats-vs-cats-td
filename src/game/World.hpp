//
// Created by kaspe on 21.11.2022.
//

#ifndef MYGAME_SRC_GAME_WORLD_HPP_
#define MYGAME_SRC_GAME_WORLD_HPP_
#include <SFML/Graphics/RenderStates.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/System/Time.hpp>
#include <SFML/Graphics/Drawable.hpp>
#include <algorithm>
#include "ui/Sector.hpp"
#include "MapGrid.hpp"
#include "resource/Resource.hpp"
#include "entity/Enemy.hpp"
#include "entity/Tower.hpp"
#include "entity/Projectile.hpp"
#include "SFML/System/Time.hpp"
#include "ui/Grid.hpp"
#include "SFML/Audio/Sound.hpp"
/**
 * @class World
 * @brief The world class houses all of the things in a game level.
 * Towers, enemies, map, map grid, etc. All those elements are used here to run and update the game.
 */
class World : public sf::Drawable {
 public:
  /**
   * @brief Constructor for world
   * @param textureholder Reference to a TextureHolder instance, mostly passed along to other classes
   * @param soundBufferHolder Reference to a SoundBufferHolder instance, mostly passed along to other classes
   * @param mapNum which map is used here (int)
   * @param pathMarkers map that contains enemy path
   */
  World(TextureHolder &textureholder,
        SoundBufferHolder &soundBufferHolder,
        int mapNum,
        std::map<int, std::pair<int, int>> &pathMarkers); //default constructor
  /**
   * @brief Update all enemies, towers and projectiles
   * @param delta time since last frame
   * Updates positions of everything. If game is paused, stops enemies, towers and projectiles.
   * Checks for dead enemies and those that have reached the cats' house.
   */
  void update(sf::Time delta);
  /**
   * @brief call other classes' draw functions. Map, towers, enemies, house, and projectiles.
   * @param target sf::RenderTarget to draw the scene to
   * @param states sf::RenderStates object for drawing
   */
  void draw(sf::RenderTarget &target, sf::RenderStates states) const;
  /**
   * @brief Add a projectile to the world (a tower shot one).
   * @param projectile ProjectilePtr, pointer to the projectile to add
   * @return
   */
  void addProjectile(ProjectilePtr &&projectile);
  /**
   * @brief Add a tower to the world (when player buys one)
   * @param tower A TowerPtr, pointer to the tower.
   * @param price The amount of money to deduct from player's balance
   */
  bool addTower(TowerPtr &&tower, int price);
  /**
   * @brief Upgrade a tower
   * @param tower Tower to upgrade, calls its function for upgrading
   * @param price How much the upgrade costs
   * @return Whether the upgrade succeeded (true if there was an upgrade available and the player had enough money)
   */
  bool upgradeTower(Tower *tower, int price);
  /**
   * @brief Find a tower and remove it
   * @param tower A pointer to a tower that should be removed
   * @param price how much money is returned to the player
   */
  void removeTower(Tower *tower, int price);
  /**
   * @brief Get the enemies currently on the map.
   * @return A vector of enemies.
   */
  Enemies &getEnemies() { return enemies; }
  /**
   * @brief Get the amount of money the player has
   * @return integer, amount of money
   */
  int getMoney() const { return money_; }
  /**
   * @brief Get the player hp
   * @return integer, hp
   */
  int getHP() const { return hp_; }
  /**
   * @brief Get the current map's MapGrid.
   * @return the map's MapGrid class instance
   */
  const MapGrid &getMapGrid() const { return grid_; }
  /**
   * @brief Find a tower at given coordinates
   * @param target Target coordinates (using Sector class)
   * @return Pointer to the tower
   */
  Tower *getTowerAt(const Sector &target) const;
  /**
   * @brief Get world TextureHolder
   * @return reference to a TextureHolder
   */
  TextureHolder &getTextures() { return textures; }
  /**
   * @brief Get world SoundBufferHolder
   * @return reference to a SoundBufferHolder
   */
  SoundBufferHolder &getSounds() { return sounds; }
  /**
   * @brief Is the player ready for next wave (pressed the button)?
   */
  bool isReadyForNextWave = false;
  /**
   * @brief Is the game paused? If so, dont move anything.
   */
  bool paused = false;
 private:
  TextureHolder &textures;
  sf::Sprite endHouse;
  SoundBufferHolder &sounds;
  sf::Sound deathSound_;
  sf::Sound explosionSound_;
  MapGrid grid_;
  int money_;
  int hp_;
  int mapNum_;
  Enemies enemies; //std::vector<std::unique_ptr<Enemy>>
  Towers towers; //std::vector<std::unique_ptr<Tower>>;
  Projectiles projectiles; //std::vector<std::unique_ptr<Projectile>>;
  ProjectilePtr projectile;
  Grid towerGrid_;
  template<typename T>
  void update(const std::vector<std::unique_ptr<T>> &vec, sf::Time delta);

  template<typename T>
  void update(const std::vector<std::shared_ptr<T>> &vec, sf::Time delta);

  template<typename T>
  void draw(const std::vector<std::unique_ptr<T>> &vec, sf::RenderTarget &target, const sf::RenderStates &states) const;

  template<typename T>
  void draw(const std::vector<std::shared_ptr<T>> &vec, sf::RenderTarget &target, const sf::RenderStates &states) const;

  template<typename T>
  void clean(std::vector<std::unique_ptr<T>> &vec);

  template<typename T>
  void clean(std::vector<std::shared_ptr<T>> &vec);

};

template<typename T>
inline void World::update(const std::vector<std::unique_ptr<T>> &vec, sf::Time deltaTime) {
  for (auto &&entity : vec) {
    if (entity != nullptr) {
      entity->update(deltaTime, *this);
    }
  }
}

template<typename T>
inline void World::update(const std::vector<std::shared_ptr<T>> &vec, sf::Time deltaTime) {
  for (auto &&entity : vec) {
    if (entity != nullptr) {
      entity->update(deltaTime, *this);
    }
  }
}

template<typename T>
inline void World::draw(const std::vector<std::unique_ptr<T>> &vec,
                        sf::RenderTarget &target,
                        const sf::RenderStates &states) const {
  for (auto &&entity : vec) {
    target.draw(*entity, states);
  }
}
template<typename T>
inline void World::draw(const std::vector<std::shared_ptr<T>> &vec,
                        sf::RenderTarget &target,
                        const sf::RenderStates &states) const {
  for (auto &&entity : vec) {
    target.draw(*entity, states);
  }
}

template<typename T>
inline void World::clean(std::vector<std::unique_ptr<T>> &vec) {
  if (!vec.empty()) {
    vec.erase(std::remove_if(vec.begin(),
                             vec.end(),
                             [](const std::unique_ptr<T> &entity) {
                               if (entity != nullptr) {
                                 return entity->ifShouldRemove();
                               } else return false;
                             }), vec.end());
  }
}

template<typename T>
inline void World::clean(std::vector<std::shared_ptr<T>> &vec) {
  for (auto elem = vec.begin(); elem != vec.end();) {
    if ((*elem)->ifShouldRemove()) {
      elem = vec.erase(elem);
    } else {
      ++elem;
    }
  }
}
//inline void World::clean(std::vector<std::shared_ptr<T>> &vec) {
//  if (!vec.empty()) {
//    vec.erase(std::remove_if(vec.begin(),
//                             vec.end(),
//                             [](const std::shared_ptr<T> &entity) {
//                               if (entity != nullptr) {
//                                 return entity->ifShouldRemove();
//                               } else return false;
//                             }), vec.end());
//  }
//}

#endif //MYGAME_SRC_GAME_WORLD_HPP_
