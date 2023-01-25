//
// Created by Otso - on 6.12.2022.
//

#ifndef MYGAME_SRC_GAME_LEVELSELECT_HPP_
#define MYGAME_SRC_GAME_LEVELSELECT_HPP_

#include "Scene.hpp"
#include "SFML/Graphics/Text.hpp"
#include "SFML/Graphics/Sprite.hpp"
#include "SFML/Graphics/RenderTexture.hpp"
#include <fstream>
#include <iostream>
/**
 * @class LevelSelect
 * @brief A class for level selection menu, inherits Scene class
 */
class LevelSelect : public Scene {
 public:
  /**
   * @brief Constructor for the class.
   * @param textures Reference to a TextureHolder instance
   * @param fonts Reference to a FontHolder instance
   */
  explicit LevelSelect(TextureHolder &textures, FontHolder &fonts);
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
   * @brief Takes input from handleInput function
   * @param key keyboard key that was pressed
   * @param isPressed Is the key pressed currently?
   */
  void handlePlayerInput(sf::Keyboard::Key key, bool isPressed);
  /**
   * @brief Next scene from this one
   * @return the request
   */
  sceneRequest requestedScene() override;
  /**
   * @brief Update scene function
   * @param dt deltatime, time since last frame update
   */
  void update(sf::Time dt) override;
  /**
   * @brief Update, which option is selected (and so should be colored red)
   */
  void updateOptionText();
  /**
   * @brief Return current scene's type
   * @return current scene's type, GameEnd
   */
  Scenes::ID sceneType() override { return Scenes::ID::LevelSelect; }
  /**
   * @brief Options to choose from in this scene, so maps
   */
  std::vector<sf::Text> options;
  /**
   * @brief What option is currently selected
   */
  std::size_t optionIndex;
 private:
  int width = 20;
  int height = 16;
  TextureHolder &textures_;
  FontHolder &fonts_;
  sf::Time textEffectTime_;
  sf::Text text_;
  bool showText_;
  sf::Sprite grassSprite_;
  sf::Sprite pathSprite;
  sf::RenderTexture mapTex_;
  sf::Sprite mapSprite_;
  sceneRequest nextScene_;
};

#endif //MYGAME_SRC_GAME_LEVELSELECT_HPP_
