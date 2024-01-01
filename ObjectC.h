#pragma once
#include "GameObject.h"
#include "Settings.h"

class ObjectC : public GameObject {
public:
    Settings settings_Obj;
    ObjectC() : GameObject(Settings::TYPE_C_OBJECT_RADIUS, 3) {
        shape.setFillColor(sf::Color::Green);
        type = 3; // Type pour C
    }
};