#include <flappyBird/states/StateMachine.hpp>
#include <flappyBird/utils/config.h>

#include <SFML/Graphics.hpp>

#include <set>

int main() {
    sf::RenderWindow window(sf::VideoMode(DISP_WIDTH, DISP_HEIGHT), "Flappy Bird");
    sf::Clock clock;

    StateMachine stateMachine(window);

    std::set<sf::Keyboard::Key> keysdown;

    while (window.isOpen()) {
        keysdown.clear();

        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::KeyPressed) {
                keysdown.insert(event.key.code);
            }

            if (event.type == sf::Event::Closed) {
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