//
// Created by Otso - on 16.11.2022.
//
#ifndef MYGAME_SRC_GAME_GAME_HPP_
#define MYGAME_SRC_GAME_GAME_HPP_
#include <SFML/Graphics.hpp>
#include "Scene.hpp"
#include "resource/Resource.hpp"
/**
 * @class Game
 * @brief Class where the game, setting are set and loading and rendering is called from
 */
class Game {
 public:
  Game(); //default constructor
  /**
   * @brief load all resources to Resource class instances
   */
  void load();
  /**
   * @brief call's current Scene class instance's draw function to display everything on screen
   */
  void render();
  /**
   * @brief takes player input from window and forwards is to current Scene class
   */
  void processEvents();
  /**
   * @brief Changes the current Scene class instance (for example when loading a level)
   */
  void handleSceneChange();
  /**
   * @brief Updates everything on screen that should move etc.
   * @param deltaTime time since last frame
   */
  void Update(sf::Time deltaTime);
  /**
   * @brief Run the game
   */
  void run();
  /**
   * Instance of class Resource, which stores textures
   */
  TextureHolder textures;
  /**
   * Instance of class Resource, which stores fonts
   */
  FontHolder fonts;
  /**
   * Instance of class Resource, which stores sounds
   */
  SoundBufferHolder sounds;
 private:
  sf::VideoMode videomode;
  sf::RenderWindow window;
  std::unique_ptr<Scene> scene;
  sf::Clock clock;
  sf::RenderStates renderStates;
};
#endif //MYGAME_SRC_GAME_GAME_HPP_
