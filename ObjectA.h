#pragma once
#include "GameObject.h"
#include "Settings.h"

class ObjectA : public GameObject {
public:
    Settings settings_Obj;
    ObjectA() : GameObject(Settings::TYPE_A_OBJECT_RADIUS, 1) {
        shape.setFillColor(sf::Color::Red);
        type = 1; // Type pour A
    }
};