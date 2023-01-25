//
// Created by Otso - on 6.12.2022.
//

#ifndef MYGAME_SRC_GAME_GAMETITLE_HPP_
#define MYGAME_SRC_GAME_GAMETITLE_HPP_
#include "Scene.hpp"
#include "SFML/Graphics/Text.hpp"
#include "SFML/Graphics/RenderTexture.hpp"
/**
 * @class GameTitle
 * @brief Welcome screen for the game
 */
class GameTitle : public Scene {
 public:
  /**
   * @brief Constructor for the GameTitle
   * @param textures Reference to a Resource class holding textures
   * @param fonts Reference to a Resource class holding fonts
   */
  explicit GameTitle(TextureHolder &textures, FontHolder &fonts);
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
   * @brief Return current scene's type
   * @return current scene's type, GameTitle
   */
  Scenes::ID sceneType() override { return Scenes::ID::GameTitle; }
 private:
  int width = 20;
  int height = 16;
  TextureHolder &textures_;
  FontHolder &fonts_;
  sf::Time textEffectTime_;
  sf::Text text_;
  sf::Text text2_;
  bool showText_;
  sf::Sprite grassSprite_;
  sf::Sprite pathSprite;
  sf::RenderTexture mapTex_;
  sf::Sprite mapSprite_;
  sceneRequest nextScene_;

};

#endif //MYGAME_SRC_GAME_GAMETITLE_HPP_
