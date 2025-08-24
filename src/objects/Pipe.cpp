#include "flappyBird/objects/Pipe.hpp"

#include "flappyBird/utils/config.h"

Pipe::Pipe(float x, float y, bool isTop) : sprite(texture) {
    if (!texture.loadFromFile(PIPE_PATH)) {
        throw std::runtime_error("Failed to load pipe texture");
    }
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