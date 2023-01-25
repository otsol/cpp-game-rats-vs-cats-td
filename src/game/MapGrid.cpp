//
// Created by kaspe on 21.11.2022.
//

#include "MapGrid.hpp"
#include "SFML/Graphics/Sprite.hpp"
#include "SFML/Graphics/Texture.hpp"
#include "SFML/Graphics/CircleShape.hpp"
#include <fstream>
#include <iostream>
static const int tileSize = 64.f;
void MapGrid::draw(sf::RenderTarget &target, sf::RenderStates states) const {
  target.draw(mapSprite_);
}
MapGrid::MapGrid(TextureHolder &textureholder, int mapNum, std::map<int, std::pair<int, int>> &pathMarkers) : textures_(
    textureholder), mapNum_(mapNum), pathMarkers_(pathMarkers) {
  std::string mapfile = "src/media/maps/map";
  mapfile.append(std::to_string(mapNum));
  mapfile.append(".txt");
  std::ifstream infile(mapfile);
  std::string line; //line to store a line of the text file
  std::getline(infile, line); //first line, map name
  this->name = line;
  std::getline(infile, line); //second line, difficulty
  this->diff = line;
  std::getline(infile, line); //third line, map width
  this->width = std::stoi(line);
  std::getline(infile, line); //fourth line, map height
  this->height = std::stoi(line);
  //read the map
  for (int i = 0; i < height; ++i) {
    std::getline(infile, line);
    std::vector<int> row;
    int offset = 0;
    for (int j = 0; j < line.length() + 1; ++j) {
      if (line[j] == '+') {
        row.emplace_back(0);
      } else if (line[j] == '(') {
        row.emplace_back(1);
        std::string it;
        j++;
        while (line[j] != ')') {
          it += line[j];
          j++;
          offset++;
        }
        offset++;
        int key = std::stoi(it);
        pathMarkers_.insert(std::make_pair(key, std::make_pair(j - offset, i)));
      } else if (line[j] == '-') {
        row.emplace_back(1);
      }
    }
    setBlockRow(row);
  }
  infile.close();
  /*
  for (int i = 0; i < pathMarkers.size(); i++) {
    std::cout << i + 1 << ": " << pathMarkers.at(i + 1).first << "," << pathMarkers.at(i + 1).second << std::endl;
  }
  */

  mapTex_.clear();
  mapTex_.create(1280, 1024);
  sf::Sprite grassSprite;
  grassSprite.setTexture(textures_.get(Textures::GrassTile));
  sf::Sprite pathSprite;
  pathSprite.setTexture(textures_.get(Textures::PathTile));
  for (int i = 0; i < height; ++i) {
    for (int j = 0; j < width; ++j) {
      if (getBlockAt(j, i) == 0) {
        grassSprite.setPosition(static_cast<float>(tileSize * j), static_cast<float>(tileSize * i));
        mapTex_.draw(grassSprite);
      } else if (getBlockAt(j, i) == 1) {
        pathSprite.setPosition(static_cast<float>(tileSize * j), static_cast<float>(tileSize * i));
        mapTex_.draw(pathSprite);
      }
    }
  }
  mapSprite_.setTexture(mapTex_.getTexture());
  mapSprite_.setOrigin({0, mapSprite_.getLocalBounds().height});
  mapSprite_.setScale({1, -1});
}
