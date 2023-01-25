#include "Grid.hpp"
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/RenderTarget.hpp>

Grid::Grid() :
    width(16),
    height(16),
    blocks() {
};

void Grid::draw(sf::RenderTarget &target, sf::RenderStates states) const {
}
Sector *Grid::getSelectedSector() {
  return selectedSector;
}
