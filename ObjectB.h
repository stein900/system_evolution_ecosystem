#pragma once
#include "GameObject.h"
#include "Settings.h"

class ObjectB : public GameObject {
public:
    Settings settings_Obj;
    ObjectB() : GameObject(settings_Obj.TYPE_B_OBJECT_RADIUS, 2) {
        shape.setFillColor(sf::Color::Blue);
        type = 2; // Type pour B
    }
};