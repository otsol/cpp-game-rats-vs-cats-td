//
// Created by Otso - on 21.11.2022.
//

#ifndef MYGAME_SRC_ENTITY_ENTITY_HPP_
#define MYGAME_SRC_ENTITY_ENTITY_HPP_

#include <SFML/System/Time.hpp>
#include <SFML/Graphics.hpp>
#include "SFML/Graphics/Sprite.hpp"
#include <SFML/Graphics/RenderStates.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/Drawable.hpp>
#include "resource/Resource.hpp"
#include <vector>

class World;
/**
 * @class Entity
 * @brief Visible entity on the map.
 */
class Entity : public sf::Drawable {
public:
  /**
   * @brief
   * @param textureID Texture number to be used for the Entity
   * @param textures Reference to a TextureHolder class instance that holds the texture
   */
   Entity(int textureID, const TextureHolder& textures);
   /**
    * @brief draw this entity, structure according to SFML manual
    * @param target where to draw this Entity
    * @param states RenderStates class to use for this drawable
    */
   void draw(sf::RenderTarget &target, sf::RenderStates states) const;
   /**
    * @brief Virtual function to update this Entity, subclasses will implement
    * @param deltaTime Time since last frame
    * @param world Reference to a world class where to update
    */
   virtual void update(sf::Time deltaTime, World& world) = 0;
   /**
    * @brief Get sprite position
    * @return SFML 2D vector, the position
    */
   sf::Vector2f getPosition() const { return entitySprite.getPosition(); }
   /**
    * @brief Get textureID used for this Entity
    * @return integer, the textureID (index in TextureHolder list)
    */
   int getTextureID() const { return textureID_; }

protected:
  sf::Sprite entitySprite;

private:
  sf::Vector2f mVelocity;
  int textureID_;
};

#endif //MYGAME_SRC_ENTITY_ENTITY_HPP_
