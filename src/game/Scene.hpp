//
// Created by kaspe on 21.11.2022.
//

#ifndef MYGAME_SRC_GAME_SCENE_HPP_
#define MYGAME_SRC_GAME_SCENE_HPP_

#include <SFML/System/Time.hpp>
#include <SFML/Window/Event.hpp>
#include <SFML/Graphics/Drawable.hpp>
#include "resource/Resource.hpp"

namespace Scenes {
/**
 * @class Contains different types of Scenes
 */
enum class ID {
  GameTitle, /// Title menu of the game, has name and list of creators
  LevelSelect, /// Main menu for selecting map
  MapScene, /// Game and its GUI
  GameEnd /// For Game Over Scene
};
}

struct request {
  Scenes::ID scene;
  size_t number;
};
typedef request sceneRequest;
/** @class Scene
 *  @brief This is a class for different UI "pages" of the game such as main menu or the game itself
 *
 *  These scenes do not have many relationships in the code. Scene object is called directly
 *  from the main Game loop. All scenes handle input, draw GUI and allow to change to next scene.
 *
 */
class Scene : public sf::Drawable {
 public:
  virtual void handleInput(const sf::Event &event) = 0;
/** <
 * @brief updates everything is a scene including UI elements and entities
 * @param deltaTime time since last update in Game loop
 */
  virtual void update(sf::Time deltaTime) = 0;
  /**
   * @brief Should the current scene be changed.
   * @return Returns the next scene ID (GUI page type) or the current scene ID if no need to change
   */
  virtual sceneRequest requestedScene() = 0;
  /**
   * @brief Returns the ID the scene, does not change
   * @return Does not change after scene creation
   */
  virtual Scenes::ID sceneType() = 0; // has to be initialized
  TextureHolder textures;
 private:
};

using ScenePtr = std::unique_ptr<Scene>;
#endif //MYGAME_SRC_GAME_SCENE_HPP_