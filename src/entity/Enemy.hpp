//
// Created by Antti - on 06.12.2022.
//

#ifndef MYGAME_SRC_ENTITY_ENEMY_HPP_
#define MYGAME_SRC_ENTITY_ENEMY_HPP_

#include "Entity.hpp"
#include "SFML/System/Time.hpp"
#include <iostream>

class Enemy;
using EnemyPtr = std::shared_ptr<Enemy>;
using Enemies = std::vector<EnemyPtr>;
/** @class Enemy
 *  @brief A class for ingame enemies. Derived from Entity class.
 *
 *  Enemies have a set amount of hitpoints and speed, a set texture and a vector of points they follow.
 *
 */
class Enemy : public Entity {
public:
    Enemy(TextureHolder& textures, int textureID, std::map<int, std::pair<int,int>>& pathMarkers, int hitPoints, float speed);
    /**
     * @brief
     * @param deltaTime time since last update in Game loop
     * @param world World class the enemy belongs to
     */
    void update(sf::Time deltaTime, World &world);
    /**
     * @brief Makes a new enemy. Returns a pointer to it.
     * @param textures A pointer to a TextureHolder class instance.
     * @param textureID Texture ID to find correct texture inside textures
     * @param pathMarkers A list of coordinate points the enemy will follow.
     * @param hitPoints Amount of hitpoints for the enemy as an integer.
     * @param speed Enemy speed as a float value.
     * @return A shared pointer to the created enemy.
     */
    static EnemyPtr make(TextureHolder& textures, int textureID, std::map<int, std::pair<int,int>>& pathMarkers, int hitPoints, float speed) {
        return std::make_unique<Enemy>(textures, textureID, pathMarkers, hitPoints, speed);
    }
    /**
     *
     * @brief Copies an enemy.
     * @param textures A pointer to a TextureHolder class instance.
     * @param textureID Texture ID to find correct texture inside textures
     * @param pathMarkers A list of coordinate points the enemy will follow.
     * @param hitPoints Amount of hitpoints for the enemy as an integer.
     * @param speed Enemy speed as a float value.
     * @return A shared pointer to the copied enemy.
     */
    EnemyPtr clone(TextureHolder& textures, int textureID, std::map<int, std::pair<int,int>>& pathMarkers, int hitPoints, float speed) const;
    /**
     * @brief Makes this enemy instance take damage.
     * @param damageAmount Damage to take.
     */
    void takeDamage(int damageAmount) { hitPoints_ -= damageAmount; }
    /**
     * @brief Slows the enemy down (caused by FreezeCat tower).
     */
    void slowDown();
    /**
     * @brief returns a reference to the TextureHolder that contains the texture for this enemy.
     * @return
     */
    TextureHolder& getTextureHolder() const { return textures_; }
    /**
     * @brief Gets a reference to this Enemy's pathmarkers list.
     * @return Reference to the pathmarkers list.
     */
    std::map<int, std::pair<int, int>> &getPathMarkers() const { return pathMarkers_; }
    /**
     * @brief returns hitpoints for this enemy (int)
     * @return Hitpoints as int
     */
    int getHitPoints() const { return hitPoints_; }
    /**
     * @brief Get value for this enemy (how much money will killing it give).
     * @return Value as int.
     */
    int getValue() const { return value_; }
    /**
     * @brief Get speed for this enemy.
     * @return Speed as float.
     */
    float getSpeed() const { return speed_; }
    /**
     * Is this enemy at the finish line (house)?
     * @return true if enemy has reached the house, otherwise false.
     */
    bool isAtFinish() const { return atFinishTile; }
    /**
     * @brief Is this enemy alive (hitpoints>0)?
     * @return true if enemy is alive, otherwise false.
     */
    bool isAlive() const { return hitPoints_ > 0; }
    /**
     * @brief Should this enemy be removed from the enemies list?
     * @return true if enemy should be removed, otherwise false.
     */
    bool ifShouldRemove() const { return !isAlive() || atFinishTile; }
    /**
     * @brief Is this enemy not frozen (slowed down)?
     * @return false if enemy is frozen, otherwise true.
     */
    bool isNotFrozen() const { return !isFrozen; }

private:
    std::map<int, std::pair<int, int>>& pathMarkers_;
    TextureHolder& textures_;
    float speed_;
    float slowdownFactor_ = 1.0;
    int slowdownCounter_;
    sf::Time slowDownTime = sf::seconds(.1f);
    sf::Time slowedDownAt_ = sf::seconds(0.f);
    int nextMarker;
    int hitPoints_;
    int value_;
    bool atFinishTile;
    bool isFrozen;
};

#endif //MYGAME_SRC_ENTITY_ENEMY_HPP_
