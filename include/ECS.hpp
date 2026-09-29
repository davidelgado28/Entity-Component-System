#pragma once

#include <iostream>
#include <vector>
#include <memory>
#include <unordered_map>
#include <typeindex>
#include <utility>
#include <SFML/Graphics.hpp>

using Entity = std::uint32_t;
const Entity INVALID_ENTITY = 0xFFFFFFFF;

struct Component {};

struct PositionComponent : public Component {
    float x, y;
};

struct VelocityComponent : public Component {
    float vx, vy;
};

struct SpriteComponent : public Component {
    sf::CircleShape shape;
    SpriteComponent(float radius, sf::Color color) {
        shape.setRadius(radius);
        shape.setFillColor(color);
        shape.setOrigin(radius, radius);
    }
};

class Registry {
private:
    Entity m_nextEntity = 1;
    std::vector<Entity> m_entities;
    std::unordered_map<Entity, std::unordered_map<std::type_index, std::unique_ptr<Component>>> m_componentPools;

public:
    Entity createEntity() {
        Entity newEntity = m_nextEntity++;
        m_entities.push_back(newEntity);
        return newEntity;
    }

    const std::vector<Entity>& getEntities() const {
        return m_entities;
    }

    template<typename T, typename... Args>
    void addComponent(Entity entity, Args&&... args) {
        static_assert(std::is_base_of_v<Component, T>, "T deve herdar de Component");
        m_componentPools[entity][typeid(T)] = std::make_unique<T>(std::forward<Args>(args)...);
    }

    template<typename T>
    T* getComponent(Entity entity) {
        auto entityIt = m_componentPools.find(entity);
        if (entityIt != m_componentPools.end()) {
            auto compIt = entityIt->second.find(typeid(T));
            if (compIt != entityIt->second.end()) {
                return static_cast<T*>(compIt->second.get());
            }
        }
        return nullptr;
    }
};

class MovementSystem {
public:
    void update(Registry& registry, float dt) {
        for (auto entity : registry.getEntities()) {
            auto pos = registry.getComponent<PositionComponent>(entity);
            auto vel = registry.getComponent<VelocityComponent>(entity);

            if (pos && vel) {
                pos->x += vel->vx * dt;
                pos->y += vel->vy * dt;
            }
        }
    }
};

class RenderSystem {
public:
    void update(Registry& registry, sf::RenderWindow& window) {
        for (auto entity : registry.getEntities()) {
            auto pos = registry.getComponent<PositionComponent>(entity);
            auto sprite = registry.getComponent<SpriteComponent>(entity);

            if (pos && sprite) {
                sprite->shape.setPosition(pos->x, pos->y);
                window.draw(sprite->shape);
            }
        }
    }
};
