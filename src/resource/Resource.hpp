//
// Created by Otso - on 21.11.2022.
//

#ifndef MYGAME_SRC_RESOURCE_RESOURCE_HPP_
#define MYGAME_SRC_RESOURCE_RESOURCE_HPP_
#include "string"
#include <SFML/System/Time.hpp>
#include "map"
#include <stdexcept>
#include <memory>
#include <cassert>
#include "SFML/Graphics/Texture.hpp"
#include "SFML/Graphics/Font.hpp"
#include "SFML/Audio/SoundBuffer.hpp"

namespace Textures {
enum ID {
  PathTile,
  GrassTile,
  HouseTile,
  GunCat,
  UpgradedGunCat,
  FreezeCat,
  UpgradedFzeezeCat,
  BombCat,
  UpgradedBombCat,
  FatRat,
  FastRat,
  BasicRat,
  Bullet,
  Bomb,
  Snowflake,
  PlayButton,
  Explosion
};
}

namespace Maps {
enum ID { Map };
}

namespace Fonts {
enum ID { GameTitleFont };
}
namespace SoundBuffers {
enum ID { EnemyDeath, Explosion, GunCat, BombCatMeow, FreezeCatMeow };
}
/**
 *
 * @tparam Resource The resource, could be a texture, or font, etc.
 * @tparam Identifier Easily readable name for the texture
 */
template<typename Resource, typename Identifier>
class ResourceHolder {
 public:
  /**
   *
   * @param id Identifier for this texture
   * @param filename File to load to this identifier
   */
  void load(Identifier id, const std::string &filename);
  /**
   *
   * @param id Identifier for wanted resource
   * @return Reference to wanted resource
   */
  Resource &get(Identifier id);
  const Resource &get(Identifier id) const;
 private:
  std::map<Identifier,
           std::unique_ptr<Resource>> mResourceMap;
};
/**
 * @brief A template function for a Resource
 * @tparam Resource
 * @tparam Identifier Identifier for resources
 * @param id Identifier name, used when accessing a Resource
 * @param filename File to load from
 */
template<typename Resource, typename Identifier>
void ResourceHolder<Resource, Identifier>::load(Identifier id,
                                                const std::string &filename) {
  std::unique_ptr<Resource> resource(new Resource());
  if (!resource->loadFromFile(filename))
    throw std::runtime_error("ResourceHolder::load - Failed to load " + filename);
  auto inserted = mResourceMap.insert(
      std::make_pair(id, std::move(resource)));
  assert(inserted.second);
}
template<typename Resource, typename Identifier>
Resource &ResourceHolder<Resource, Identifier>::get(Identifier id) {
  auto found = mResourceMap.find(id);
  assert(found != mResourceMap.end());
  return *found->second;
}
template<typename Resource, typename Identifier>
const Resource &ResourceHolder<Resource, Identifier>::get(Identifier id) const {
  auto found = mResourceMap.find(id);
  assert(found != mResourceMap.end());
  return *found->second;
}

typedef ResourceHolder<sf::Texture, Textures::ID> TextureHolder;
typedef ResourceHolder<std::string, Maps::ID> MapHolder;
typedef ResourceHolder<sf::Font, Fonts::ID> FontHolder;
typedef ResourceHolder<sf::SoundBuffer, SoundBuffers::ID> SoundBufferHolder;

#endif //MYGAME_SRC_RESOURCE_RESOURCE_HPP_
