#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include <memory>
#include <chrono>

class GameObject {
public:
    sf::CircleShape shape;
    sf::Vector2f velocity;
    int type; 
    std::chrono::time_point<std::chrono::steady_clock> lastDuplicationTime;
    bool hasDuplicated = false; 
    std::chrono::time_point<std::chrono::steady_clock> creationTime;

    GameObject(float radius, int initType = 0) 
        : shape(radius), type(initType) { 
       
        shape.setFillColor(sf::Color::Red); 

        float speedX = ((rand() % 200 - 100) / 100.0f) * 3.0f; // valeur entre -1 et 1
        float speedY = ((rand() % 200 - 100) / 100.0f) * 3.0f; 
        velocity = sf::Vector2f(speedX, speedY);
        lastDuplicationTime = std::chrono::steady_clock::now();
        creationTime = std::chrono::steady_clock::now(); 
    }

    virtual void update(const sf::RenderWindow& window) {
        shape.move(velocity);

        if (shape.getPosition().x < 0 || shape.getPosition().x > window.getSize().x) {
            velocity.x = -velocity.x;
        }
        if (shape.getPosition().y < 0 || shape.getPosition().y > window.getSize().y) {
            velocity.y = -velocity.y;
        }
    }

    bool isAlive() const {
        auto now = std::chrono::steady_clock::now();
        return std::chrono::duration_cast<std::chrono::seconds>(now - creationTime).count() < 20;
    }

    virtual void draw(sf::RenderWindow& window) {
        window.draw(shape);
    }

};