#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include <memory>
#include <chrono>
#include "Settings.h"

class GameObject {
public:
    Settings settings_Obj;
    sf::CircleShape shape;
    sf::Vector2f velocity;
    int type; 
    std::chrono::time_point<std::chrono::steady_clock> lastDuplicationTime;
    bool hasDuplicated = false; 
    std::chrono::time_point<std::chrono::steady_clock> creationTime;
    //vision
    float visionRange; // La portée du champ de vision
    float visionAngle; // L'angle du champ de vision
    const float M_PI = 3.14159265358979323846f;
    const float HUNT_SPEED = settings_Obj.HUNT_SPEED_VALUE;
    const float ESCAPE_SPEED = settings_Obj.ESCAPE_SPEED_VALUE;
    std::chrono::time_point<std::chrono::steady_clock> lastInteractionTime;
    const std::chrono::milliseconds blindDuration = std::chrono::milliseconds(1000); // Durée d'aveuglement après interaction
    bool isInteracting; // Nouvelle variable pour suivre l'état d'interaction


    GameObject(float radius, int initType);

    void update(const sf::RenderWindow& window, const std::vector<std::unique_ptr<GameObject>>& allObjects);

    bool isAlive() const;

    virtual void draw(sf::RenderWindow& window);

    // Modification de objectsInVision pour retourner également la position
    std::vector<std::pair<int, sf::Vector2f>> objectsInVision(const std::vector<std::unique_ptr<GameObject>>& objects);

    void handleInteraction();

};