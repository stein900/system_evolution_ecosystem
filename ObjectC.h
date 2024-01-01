#pragma once
#include "GameObject.h"
class ObjectC : public GameObject {
public:
    ObjectC() : GameObject(6, 3) {
        shape.setFillColor(sf::Color::Green);
        type = 3; // Type pour C
    }
};