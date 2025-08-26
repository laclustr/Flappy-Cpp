#include <flappyBird/states/StateMachine.hpp>
#include <flappyBird/utils/config.h>

#include <SFML/Graphics.hpp>

#include <set>

int main() {
    sf::RenderWindow window(sf::VideoMode({DISP_WIDTH, DISP_HEIGHT}), "Flappy Bird");
    sf::Clock clock;

    StateMachine stateMachine(window);

    std::set<sf::Keyboard::Key> keysdown;

    while (window.isOpen()) {
        keysdown.clear();

        while (const std::optional<sf::Event> event = window.pollEvent()) {
            if (const auto* keyPressed = event->getIf<sf::Event::KeyPressed>()) {
                keysdown.insert(keyPressed->code);
            }

            if (event->is<sf::Event::Closed>()) {
                window.close();
            }
        }

        sf::Time deltaTime = clock.restart();
        float dt = deltaTime.asSeconds();

        stateMachine.update(keysdown, dt);
        
        window.clear();
        stateMachine.render();
        window.display();

        window.setFramerateLimit(60);
    }
}