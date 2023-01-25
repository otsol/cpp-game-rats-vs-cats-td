//
// Created by Antti - on 09.12.2022.
//
#ifndef MYGAME_SRC_ENTITY_PROJECTILES_HPP_
#define MYGAME_SRC_ENTITY_PROJECTILES_HPP_

#include <SFML/System/Time.hpp>
#include "ui/Sector.hpp"
#include "Entity.hpp"
#include "Enemy.hpp"
#include "SFML/System/Time.hpp"
#include <vector>
#include <memory>
/**
 * @class ProjectileType
 * @brief Contains identification for different projectiles
 */
enum class ProjectileType {
  Bullet,
  FreezeGun,
  Bomb
};
class World;
class Projectile;
using ProjectilePtr = std::unique_ptr<Projectile>;
using Projectiles = std::vector<ProjectilePtr>;
/**
 * @class Projectile
 * @brief Extends Entity class, Bombs, Bullets etc.
 */
class Projectile : public Entity {
public:
  /**
   *
   * @param textures Reference to a TextureHolder class instance
   * @param textureID an integer, index of wanted texture in the TextureHolder
   * @param type Is the projectile a bullet or a bomb, etc.
   * @param start Start location as a Sector type
   * @param closestEnemy The closest enemy to The projectile, target
   * @param closestEnemies A map of closest enemies, needed for splash damage
   * @param neighbourEnemies
   * @param range Splash damage range
   * @param damage How much damage does the projectile do
   * @param velocity How fast the projectile moves
   */
    Projectile(TextureHolder &textures, int textureID, ProjectileType type, Sector start, const std::pair<float, std::shared_ptr<Enemy>>& closestEnemy, const std::map<int, std::pair<float, std::shared_ptr<Enemy>>>& closestEnemies, std::map<int, std::pair<float, std::shared_ptr<Enemy>>> neighbourEnemies, float range, int damage, float velocity);
    /**
     * @brief make new projectile
     * @param textures Reference to a TextureHolder class instance
     * @param textureID an integer, index of wanted texture in the TextureHolder
     * @param type Is the projectile a bullet or a bomb, etc.
     * @param start Start location as a Sector type
     * @param closestEnemy The closest enemy to The projectile, target
     * @param closestEnemies A map of closest enemies, needed for splash damage
     * @param neighbourEnemies
     * @param range Splash damage range
     * @param damage How much damage does the projectile do
     * @param velocity How fast the projectile moves
     * @return unique_ptr to the Projectile
     */
    static ProjectilePtr make(TextureHolder& textures, int textureID, ProjectileType type, Sector start, const std::pair<float, std::shared_ptr<Enemy>>& closestEnemy, const std::map<int, std::pair<float, std::shared_ptr<Enemy>>>& closestEnemies, const std::map<int, std::pair<float, std::shared_ptr<Enemy>>>& neighbourEnemies, float range, int damage, float velocity);
    /**
     * @brief update projectile in World
     * @param deltaTime time since last frame
     * @param world reference to World class where the Projectile is
     */
    void update(sf::Time deltaTime, World &world);
    /**
     * @brief Should the projectile be removed, has it hit something?
     * @return Whether the projectile should be removed, true is should
     */
	bool ifShouldRemove() const { return atFinish; }
    /**
     * @brief type of this projectile
     */
    ProjectileType type_;

private:
    Sector start_;
    Sector finish_;
    std::pair<float, std::shared_ptr<Enemy>> closestEnemy_;
    std::map<int, std::pair<float, std::shared_ptr<Enemy>>> closestEnemies_;
    std::map<int, std::pair<float, std::shared_ptr<Enemy>>> neighbourEnemies_;
    TextureHolder &textures_;
    float range_;
    int damage_;
    float velocity_;
	float distanceCovered;
    float distance;
    bool atFinish;
};

#endif //MYGAME_SRC_ENTITY_PROJECTILES_HPP_