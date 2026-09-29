#include "ECS.hpp"

int main() {
    sf::RenderWindow window(sf::VideoMode(800, 600), "Classic 2D Game - ECS Architecture");
    window.setFramerateLimit(60);

    Registry registry;
    MovementSystem movementSystem;
    RenderSystem renderSystem;

    Entity player = registry.createEntity();
    registry.addComponent<PositionComponent>(player, 400.f, 300.f);
    registry.addComponent<VelocityComponent>(player, 150.f, -100.f);
    registry.addComponent<SpriteComponent>(player, 20.f, sf::Color::Green);

    sf::Clock clock;

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }
        float dt = clock.restart().asSeconds();

        movementSystem.update(registry, dt);
        window.clear(sf::Color::Black);
        renderSystem.update(registry, window);
        window.display();
    }
    return 0;
}
