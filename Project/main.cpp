#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include <memory>
#include <chrono>
#include "GameObject.h"
#include "ObjectA.h"
#include "ObjectB.h"
#include "ObjectC.h"
#include "ObjectD.h"
#include "setup.h"


int main() {
    setup Src_Obj;
    srand(static_cast<unsigned int>(time(nullptr)));

    while (Src_Obj.window.isOpen()) {
        while (Src_Obj.window.pollEvent(Src_Obj.event)) {
            if (Src_Obj.event.type == sf::Event::Closed) {
                Src_Obj.window.close();
            }
        }
        Src_Obj.window.clear();
        Src_Obj.drawing_object();
        Src_Obj.handle_Collision();
        Src_Obj.delete_Object();
        Src_Obj.merge_Duplicated_object();
        if (Src_Obj.count > 60) std::cout << Src_Obj.see_Evolution_Statistic();
        Src_Obj.handle_Frame_rate_per_seconds_stability();
        Src_Obj.window.display();
    }

    return 0;
}