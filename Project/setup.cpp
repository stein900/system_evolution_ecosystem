#include "setup.h"

setup::setup() : window(sf::VideoMode(1500, 888), "Object Simulation") {

        for (int i = 0; i < 20; i++) {
        auto objA = std::make_unique<ObjectA>();
        objA->shape.setPosition(sf::Vector2f(rand() % window.getSize().x, rand() % window.getSize().y));
        objects.push_back(std::move(objA));

        auto objB = std::make_unique<ObjectB>();
        objB->shape.setPosition(sf::Vector2f(rand() % window.getSize().x, rand() % window.getSize().y));
        objects.push_back(std::move(objB));

        auto objC = std::make_unique<ObjectC>();
        objC->shape.setPosition(sf::Vector2f(rand() % window.getSize().x, rand() % window.getSize().y));
        objects.push_back(std::move(objC));

        auto objD = std::make_unique<ObjectD>();
        objD->shape.setPosition(sf::Vector2f(rand() % window.getSize().x, rand() % window.getSize().y));
        objects.push_back(std::move(objD));
    }
    std::cout<<see_Evolution_Statistic();
}

void setup::drawing_object(){

    for (size_t i = 0; i < objects.size(); ++i) {
        auto& obj = objects[i];
        obj->update(window);
        obj->draw(window);

        if (!obj->isAlive()) {
            toRemove.push_back(i); 
        }
    }
}

// A = 1, B = 2, C = 3, D = 4
void setup::handle_Collision(){
    for (size_t i = 0; i < objects.size(); i++) {
        for (size_t j = 0; j < objects.size(); j++) {
            if (i != j && collision(objects[i], objects[j])) {
                if (objects[i]->type == 1 && objects[j]->type == 3) { // A touche C
                    toRemove.push_back(j); 
                    this->C_delete++;
                }
                else if (objects[i]->type == 2 && objects[j]->type == 4) { // B touche D
                    toRemove.push_back(j); 
                    this->D_delete++;
                    break; 
                }
                //else if (objects[i]->type == 3 && objects[j]->type == 3) { // C touche C
                //    int Duplicate_B_with_B = rand() % 2;
                //    if (Duplicate_B_with_B == 1) {
                //        toRemove.push_back(j); 
                //        C_delete++;
                //    }
                //}
                else if (objects[i]->type == 3 && objects[j]->type == 1) { // C touche A
                    //int destroyA = rand() % 2;
                    //if (destroyA == 1) {
                    //    toRemove.push_back(j); 
                    //    A_delete++;
                    //}

                    toRemove.push_back(j); 
                    this->A_delete++;
                    break; 
                }
                else if (objects[i]->type == 1 && objects[j]->type == 4) { // A touche D
                    auto now = std::chrono::steady_clock::now();
                    auto& objA = objects[i]->type == 1 ? objects[i] : objects[j];

                    // Dupliquer seulement si suffisamment de temps s'est écoulé
                    if (std::chrono::duration_cast<std::chrono::milliseconds>(now - objA->lastDuplicationTime).count() > 500 && !objA->hasDuplicated) { // 500 ms
                        this->A_duplication++;
                        auto newObj = std::make_unique<ObjectA>();
                        newObj->shape.setPosition(objA->shape.getPosition());
                        newObjects.push_back(std::move(newObj)); 
                        objA->lastDuplicationTime = now; 
                    }
                }
                else if (objects[i]->type == 2 && objects[j]->type == 1) { // B touche A
                    auto now = std::chrono::steady_clock::now();
                    auto& objB = objects[i]->type == 2 ? objects[i] : objects[j];

                    // Dupliquer seulement si suffisamment de temps s'est écoulé
                    if (std::chrono::duration_cast<std::chrono::milliseconds>(now - objB->lastDuplicationTime).count() > 500 && !objB->hasDuplicated) { // 500 ms
                        //int duplicateB = rand() % 1;
                        //if (duplicateB == 1) {
                        //    B_duplication++;
                        //    auto newObj = std::make_unique<ObjectB>();
                        //    newObj->shape.setPosition(objB->shape.getPosition());
                        //    newObjects.push_back(std::move(newObj)); 
                        //    objB->lastDuplicationTime = now; 
                        //}

                        this->B_duplication++;
                        auto newObj = std::make_unique<ObjectB>();
                        newObj->shape.setPosition(objB->shape.getPosition());
                        newObjects.push_back(std::move(newObj)); 
                        objB->lastDuplicationTime = now; 
                    }
                }
                else if (objects[i]->type == 3 && objects[j]->type == 2) { // C touche B
                    auto now = std::chrono::steady_clock::now();
                    auto& objC = objects[i]->type == 3 ? objects[i] : objects[j];

                    // Dupliquer seulement si suffisamment de temps s'est écoulé
                    if (std::chrono::duration_cast<std::chrono::milliseconds>(now - objC->lastDuplicationTime).count() > 500 && !objC->hasDuplicated) { //500 ms
                        //int duplicateC = rand() % 1;
                        //if (duplicateC == 1) {
                        //     this->C_duplication++;
                        //    auto newObj = std::make_unique<ObjectC>();
                        //    newObj->shape.setPosition(objC->shape.getPosition());
                        //    newObjects.push_back(std::move(newObj));
                        //    objC->lastDuplicationTime = now;
                        //}

                        this->C_duplication++;
                        auto newObj = std::make_unique<ObjectC>();
                        newObj->shape.setPosition(objC->shape.getPosition());
                        newObjects.push_back(std::move(newObj));
                        objC->lastDuplicationTime = now;
                    }
                }
                else if (objects[i]->type == 4 && objects[j]->type == 3) { // D touche C
                    auto now = std::chrono::steady_clock::now();
                    auto& objD = objects[i]->type == 4 ? objects[i] : objects[j];

                    if (std::chrono::duration_cast<std::chrono::milliseconds>(now - objD->lastDuplicationTime).count() > 500 && !objD->hasDuplicated) { //500 ms
                        for (int n = 0; n < 1; ++n) {
                            auto newObj = std::make_unique<ObjectD>();
                            newObj->shape.setPosition(objD->shape.getPosition());
                            newObjects.push_back(std::move(newObj));
                            this->D_duplication++;
                        }
                        objD->lastDuplicationTime = now; 
                        objD->hasDuplicated = true; 

                    }
                }

            }
        }
    }
    this->count++;

}

bool setup::collision(const std::unique_ptr<GameObject>& a, const std::unique_ptr<GameObject>& b) {
    float distanceX = a->shape.getPosition().x - b->shape.getPosition().x;
    float distanceY = a->shape.getPosition().y - b->shape.getPosition().y;
    float distance = std::sqrt(distanceX * distanceX + distanceY * distanceY);
    return distance < (a->shape.getRadius() + b->shape.getRadius());
}

void setup::delete_Object() {
    // Ensure that 'toRemove' is sorted and contains unique indices
    std::sort(toRemove.begin(), toRemove.end());
    toRemove.erase(std::unique(toRemove.begin(), toRemove.end()), toRemove.end());

    // Now it's safe to delete objects in reverse order
    for (auto rit = toRemove.rbegin(); rit != toRemove.rend(); ++rit) {
        objects.erase(objects.begin() + (*rit));
    }
    toRemove.clear();
}



void setup::merge_Duplicated_object(){
    objects.insert(objects.end(), std::make_move_iterator(newObjects.begin()), std::make_move_iterator(newObjects.end()));
    newObjects.clear();
}

std::string setup::see_Evolution_Statistic(){
    system("cls");
    if (count > 60) {
        this->statistics = " ";
        this->statistics += "\n";
        this->statistics += this->RED + "A" + this->RESET + " as been duplicate " + std::to_string(this->A_duplication) + " time" + "\n";
        this->statistics += this->BLUE + "B" + this->RESET + " as been duplicate " + std::to_string(this->B_duplication) + " time" + "\n";
        this->statistics += this->GREEN + "C" + this->RESET + " as been duplicate " + std::to_string(this->C_duplication) + " time" + "\n";
        this->statistics += this->MAGENTA + "D" + this->RESET + " as been duplicate " + std::to_string(this->D_duplication) + " time" + "\n";
        this->statistics += "\n";
        this->statistics += this->RED + "A" + this->RESET + " as been delete " + std::to_string(this->A_delete) + " time" + "\n";
        this->statistics += this->BLUE + "B" + this->RESET + " as been delete " + std::to_string(this->B_delete) + " time" + "\n";
        this->statistics += this->GREEN + "C" + this->RESET + " as been delete " + std::to_string(this->C_delete) + " time" + "\n";
        this->statistics += this->MAGENTA + "D" + this->RESET + " as been delete " + std::to_string(this->D_delete) + " time" + "\n";
        this->count = 0;
        return this->statistics;
    }
    return this->statistics;
}

void setup::handle_Frame_rate_per_seconds_stability(){
    sf::Time elapsedTime = clock.getElapsedTime();
    if (elapsedTime.asMilliseconds() < 16.67) { //fPS 60 with T = 16.67ms (calculus = 1000 / 60 fps )
        sf::sleep(sf::milliseconds(16.67) - elapsedTime);
    }clock.restart();
}
