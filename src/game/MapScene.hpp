//
// Created by kaspe on 21.11.2022.
//

#ifndef MYGAME_SRC_GAME_MAPSCENE_HPP_
#define MYGAME_SRC_GAME_MAPSCENE_HPP_
#include "Scene.hpp"
#include "World.hpp"
#include "WaveController.hpp"
#include "ui/TowerMenu.hpp"
#include "ui/GameStatusMenu.hpp"
#include "ui/WaveStart.hpp"
#include "ui/WavePause.hpp"
#include "ui/GameCommandsMenu.hpp"
/**
 * @class MapScene
 * @brief A class used when ingame. Inherits from Scene class. The main scene of the game.
 */
class MapScene : public Scene {
 public:
  /**
   * @brief Constructor for the class
   * @param textures Reference to a TextureHolder instance
   * @param fonts Reference to a FontHolder instance
   * @param soundBuffers Reference to a SoundBufferHolder instance
   * @param mapNum Map number
   */
  MapScene(TextureHolder &textures, FontHolder &fonts, SoundBufferHolder &soundBuffers, int mapNum);
  /**
   * @brief draw the scene to target
   * @param target sf::RenderTarget to draw the scene to
   * @param states sf::RenderStates object for drawing
   */
  void draw(sf::RenderTarget &target, sf::RenderStates states) const override;
  /**
   * @brief handle input for current scene
   * @param event sf::Event (keypress etc.)
   */
  void handleInput(const sf::Event &event) override;
  /**
   * @brief Update scene function
   * @param delta deltatime, time since last frame update
   */
  void update(sf::Time delta) override;
  /**
   * @brief Next scene from this one (GameOverScene)
   * @return the request
   */
  sceneRequest requestedScene() override;
  /**
   * @brief Return current scene's type
   * @return current scene's type, MapScene
   */
  Scenes::ID sceneType() override { return Scenes::ID::MapScene; }
  /**
   * @brief Current Map number
   */
  int mapNum_;
  /**
   * @brief A map that contains enemy pathMarkers for current level (coordinates enemies go through)
   */
  std::map<int, std::pair<int, int>> pathMarkers;
  /**
   * @brief The towermenu class that is rendered with maps
   */
  TowerMenu towerMenu_;
 private:
  World world_;
  TextureHolder &textures_;
  SoundBufferHolder &soundBuffers_;
  FontHolder &fonts_;
  WaveController waveController_;
  sf::Text fpsText;
  int width = 16;
  int height = 16;
  GameStatusMenu statusMenu_;
  GameCommandsMenu commandsMenu_;
  WaveStart waveStart_;
  WavePause wavePause_;
  request nextScene_;
};

#endif //MYGAME_SRC_GAME_MAPSCENE_HPP_
