#include "TowerMenu.hpp"
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Window/Event.hpp>
#include "game/World.hpp"

static const sf::Color hoverColor = sf::Color(100, 100, 220, 200);
static const sf::Color rangeIndicatorColor = sf::Color(220, 220, 220, 60);

TowerMenu::TowerMenu(World &world) :
    showSectorIndicator(false),
    sectorIndicator(),
    rangeIndicator() {
  sectorIndicator.setSize(Sector::DiagVector);
  sectorIndicator.setFillColor(sf::Color::Transparent);
  sectorIndicator.setOutlineColor(hoverColor);
  sectorIndicator.setOutlineThickness(3.f);
  rangeIndicator.setRadius(0);
  rangeIndicator.setFillColor(rangeIndicatorColor);
  rangeIndicator.setOutlineColor(hoverColor);
  rangeIndicator.setOutlineThickness(3.f);
}

void TowerMenu::handleInput(const sf::Event &event, World &world) {
  if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Button::Left) {
    showSectorIndicator = true;
    Sector sector = Sector::fromCoords(event.mouseButton.x, event.mouseButton.y);
    if ((sector.x / Sector::Size) <= world.getMapGrid().getHeight() - 1
        && (sector.y / Sector::Size) <= world.getMapGrid().getWidth() - 1
        && world.getMapGrid().getBlockAt(sector.x / Sector::Size, sector.y / Sector::Size) == 0) {
      auto t = world.getTowerAt(sector);
      float selectedTowerRange;
      if (t != nullptr) selectedTowerRange = t->getRange(); else selectedTowerRange = 0;
      sectorIndicator.setPosition(sector.upperLeftPoint());
      rangeIndicator.setPosition(sector.upperLeftPoint().x - selectedTowerRange + ((float) Sector::Size / 2),
                                 sector.upperLeftPoint().y - selectedTowerRange + ((float) Sector::Size / 2));
      rangeIndicator.setRadius(selectedTowerRange);
      selectedSector = sector;
    }
  } else if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Button::Right) {
    Sector sector = Sector::fromCoords(event.mouseButton.x, event.mouseButton.y);
    if (world.getTowerAt(sector) != nullptr)
      world.removeTower(const_cast<Tower *>(world.getTowerAt(sector)),
                        (int) (0.8 * world.getTowerAt(sector)->getPrice()));
  } else if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Num1) {
    if (world.getTowerAt(selectedSector) == nullptr) {
      TowerPtr
          t = std::make_unique<Tower>(world.getTextures(), world.getSounds(), Textures::GunCat,
                                      selectedSector, 2, 250.f, sf::seconds(2), 300, TowerType::GunCat);
      world.addTower(std::move(t), t->getPrice());
    }
  } else if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Num2
      && world.getMapGrid().getBlockAt(selectedSector.x / 64, selectedSector.y / 64) == 0) {
    if (world.getTowerAt(selectedSector) == nullptr) {
      TowerPtr
          t = std::make_unique<Tower>(world.getTextures(), world.getSounds(), Textures::FreezeCat,
                                      selectedSector, 1, 250.f, sf::seconds(2), 400, TowerType::FreezeCat);
      world.addTower(std::move(t), t->getPrice());
    }
  } else if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::P) {
    world.paused = !world.paused;
  } else if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Num3
      && world.getMapGrid().getBlockAt(selectedSector.x / 64, selectedSector.y / 64) == 0) {
    if (world.getTowerAt(selectedSector) == nullptr) {
      TowerPtr
          t = std::make_unique<Tower>(world.getTextures(), world.getSounds(), Textures::BombCat,
                                      selectedSector, 1, 250.f, sf::seconds(3), 500, TowerType::BombCat);
      world.addTower(std::move(t), t->getPrice());
    }
  } else if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Num4
      && world.getMapGrid().getBlockAt(selectedSector.x / 64, selectedSector.y / 64) == 0) {
    if (world.getTowerAt(selectedSector) != nullptr) {
      world.upgradeTower(world.getTowerAt(selectedSector), 500);
    }
  }
}

void TowerMenu::update(World &world, const sf::Vector2f &mousePosition) {

}

void TowerMenu::draw(sf::RenderTarget &target, sf::RenderStates states) const {
  target.draw(sectorIndicator, states);
  target.draw(rangeIndicator, states);
}