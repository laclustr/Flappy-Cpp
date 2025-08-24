#include "flappyBird/objects/PipePair.hpp"

#include "flappyBird/utils/config.h"

#include <optional>

Pipe::Pipe(float x, float y, bool isTop) {
    if (!texture.loadFromFile(PIPE_PATH)) {}
    if (isTop) {
        sprite.setTexture(texture);
    } else {
        sprite.setTexture(texture);
        sprite.setScale({1.f, -1.f});
    }
    sprite.setPosition({x, y});
}

Pipe::~Pipe() {}

void Pipe::update(const float dt) {
    sprite.move({-PIPE_SPEED * dt, 0});
}

void Pipe::render(sf::RenderWindow& window) {
    window.draw(sprite);
}

sf::FloatRect Pipe::getBounds() const {
    return sprite.getGlobalBounds();
}

PipePair::PipePair() 
    : topPipe(DISP_WIDTH, 0, true), 
      bottomPipe(DISP_WIDTH, DISP_HEIGHT - bottomPipe.getBounds().size.y, false),
      passed(false) 
{}

PipePair::~PipePair() {
    topPipe.~Pipe();
    bottomPipe.~Pipe();
}

void PipePair::update(const float dt) {
    topPipe.update(dt);
    bottomPipe.update(dt);
}

bool PipePair::isOffScreen() const {
    return topPipe.getBounds().position.x + topPipe.getBounds().size.x < 0;
}

bool PipePair::hasPassed(const sf::FloatRect bounds) {
    if (!passed && topPipe.getBounds().position.x + topPipe.getBounds().size.x < bounds.position.x) {
        passed = true;
        return true;
    }
    return false;
}

bool PipePair::collidesWith(const sf::FloatRect& bounds) const {
    std::optional<sf::FloatRect> topIntersection = topPipe.getBounds().findIntersection(bounds);
    std::optional<sf::FloatRect> bottomIntersection = bottomPipe.getBounds().findIntersection(bounds);
    return topIntersection.has_value() || bottomIntersection.has_value();
}

sf::FloatRect PipePair::getTopBounds() const {
    return topPipe.getBounds();
}

sf::FloatRect PipePair::getBottomBounds() const {
    return bottomPipe.getBounds();
}
