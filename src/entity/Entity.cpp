//
// Created by Otso - on 21.11.2022.
//

#include "Entity.hpp"
#include <SFML/Graphics/RenderTarget.hpp>

Entity::Entity(int textureID, const TextureHolder& textures) : entitySprite() {
  textureID_ = textureID;
  entitySprite.setTexture(textures.get(Textures::ID(textureID_)));
}

void Entity::draw(sf::RenderTarget &target, sf::RenderStates states) const{
  target.draw(entitySprite, states);
}
