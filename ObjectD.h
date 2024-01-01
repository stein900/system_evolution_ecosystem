#pragma once
#include "GameObject.h"
class ObjectD : public GameObject {
public:
    ObjectD() : GameObject(9, 4) {
        shape.setFillColor(sf::Color::Magenta);
        type = 4; // Type pour C
        GameObject::velocity = sf::Vector2f(3.0f, 3.0f);
    }
};