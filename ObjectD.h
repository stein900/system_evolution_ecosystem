#pragma once
#include "GameObject.h"
#include "Settings.h"

class ObjectD : public GameObject {
public:
    Settings settings_Obj;
    ObjectD() : GameObject(settings_Obj.TYPE_D_OBJECT_RADIUS, 4) {
        shape.setFillColor(sf::Color::Magenta);
        type = 4; // Type pour C
        GameObject::velocity = sf::Vector2f(3.0f, 3.0f);
    }
};