#pragma once
#include "GameObject.h"

class ObjectA : public GameObject {
public:
    ObjectA() : GameObject(5, 1) {
        shape.setFillColor(sf::Color::Red);
        type = 1; // Type pour A
    }
};