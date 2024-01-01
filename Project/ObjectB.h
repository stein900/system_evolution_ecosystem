#pragma once
#include "GameObject.h"
class ObjectB : public GameObject {
public:
    ObjectB() : GameObject(7, 2) {
        shape.setFillColor(sf::Color::Blue);
        type = 2; // Type pour B
    }
};