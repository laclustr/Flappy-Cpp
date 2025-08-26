#include "flappyBird/objects/Bird.hpp"

#include "flappyBird/utils/config.h"

#include <optional>

Bird::Bird(int playerNum, sf::Keyboard::Key jumpKey) : sprite(texture) {
    this->playerNum = playerNum;
    this->jumpKey = jumpKey;
    this->isAlive = true;
    this->score = 0;

    this->gravity = BIRD_GRAVITY;
    this->velocity = 0.f;

    if (!texture.loadFromFile(BIRD_ASSET_PATH)) {
        throw std::runtime_error("Failed to load bird texture");
    }
    sprite.setTexture(texture);
    sprite.setPosition({100.f, 300.f});
}

Bird::~Bird() {}

void Bird::update(const std::set<sf::Keyboard::Key>& keysDown, const float dt) {
    velocity += gravity;
    sprite.move({0, velocity * dt});

    if (keysDown.find(jumpKey) != keysDown.end()) {
        jump();
    }

    if (hits_bottom()) {
        sprite.setPosition({sprite.getPosition().x, DISP_HEIGHT});
    }
}

void Bird::render(sf::RenderWindow& window) {
    window.draw(sprite);
}

sf::FloatRect Bird::getBounds() const {
    return sprite.getGlobalBounds();
}

void Bird::jump() {
    velocity = -BIRD_JUMP_HEIGHT;
}

bool Bird::collides(sf::Sprite other) {
    auto intersection = sprite.getGlobalBounds().findIntersection(other.getGlobalBounds());
    return intersection.has_value();
}

bool Bird::hits_bottom() {
    return sprite.getPosition().y + sprite.getGlobalBounds().size.y > DISP_HEIGHT;
}

bool Bird::above_screen() {
    return sprite.getPosition().y < 0;
}

bool Bird::is_alive() const {
    return isAlive;
}

void Bird::kill() {
    isAlive = false;
}

long long Bird::getScore() const {
    return score;
}