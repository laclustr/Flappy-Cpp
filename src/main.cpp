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

        while (const std::optional event = window.pollEvent()) {
            if (event->is<sf::Event::KeyPressed>()) {
                const auto& keyPressed = event->getIf<sf::Event::KeyPressed>();
                if (keyPressed) {
                    keysdown.insert(keyPressed->code);
                }
            }

            if (event->is<sf::Event::Closed>()) {
                window.close();
            }
        }

        sf::Time deltaTime = clock.restart();
        float dt = deltaTime.asSeconds();

        stateMachine.update(keysdown, dt);
        stateMachine.render();

        window.clear();
        window.display();

        window.setFramerateLimit(60);
    }
}