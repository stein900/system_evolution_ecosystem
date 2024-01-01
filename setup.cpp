#include "setup.h"

setup::setup() : window(sf::VideoMode(1500, 888), "Object Simulation") {

        for (int i = 0; i < settings_Obj.number_Of_Shape_Per_Type; i++) {
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
    this->ID = rand() % 10000;
}

void setup::drawing_object(){

    for (size_t i = 0; i < objects.size(); ++i) {
        auto& obj = objects[i];
        obj->update(window, objects);
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
                if (objects[i]->type == static_cast<int>(setup::ObjectType::A) && objects[j]->type == static_cast<int>(setup::ObjectType::C)) { // A touche C
                    toRemove.push_back(j); 
                    this->C_delete++;
                    objects[i]->handleInteraction();
                    objects[j]->handleInteraction();
                }
                else if (objects[i]->type == static_cast<int>(setup::ObjectType::B) && objects[j]->type == static_cast<int>(setup::ObjectType::D)) { // B touche D
                    toRemove.push_back(j); 
                    this->D_delete++;
                    objects[i]->handleInteraction();
                    objects[j]->handleInteraction();
                    break; 
                }

                else if (objects[i]->type == static_cast<int>(setup::ObjectType::C) && objects[j]->type == static_cast<int>(setup::ObjectType::A)) { // C touche A

                    toRemove.push_back(j); 
                    this->A_delete++;
                    objects[i]->handleInteraction();
                    objects[j]->handleInteraction();
                    break; 
                }
                else if (objects[i]->type == static_cast<int>(setup::ObjectType::A) && objects[j]->type == static_cast<int>(setup::ObjectType::D)) { // A touche D
                    auto now = std::chrono::steady_clock::now();
                    auto& objA = objects[i]->type == static_cast<int>(setup::ObjectType::A) ? objects[i] : objects[j];

                    // Dupliquer seulement si suffisamment de temps s'est écoulé
                    if (std::chrono::duration_cast<std::chrono::milliseconds>(now - objA->lastDuplicationTime).count() > 500 && !objA->hasDuplicated && should_Create_Object(1)) { // 500 ms
                        this->A_duplication++;
                        auto newObj = std::make_unique<ObjectA>();
                        newObj->shape.setPosition(objA->shape.getPosition());
                        sf::Vector2f offset(rand() % 20 - 10, rand() % 20 - 10);
                        newObj->shape.move(offset);
                        newObj->velocity.x = -newObj->velocity.x + rand() % 3 - 1;
                        newObj->velocity.y = -newObj->velocity.y + rand() % 3 - 1;
                        newObj->handleInteraction();
                        newObjects.push_back(std::move(newObj)); 
                        objA->lastDuplicationTime = now; 
                        objA->handleInteraction();
                    }
                }
                else if (objects[i]->type == static_cast<int>(setup::ObjectType::B) && objects[j]->type == static_cast<int>(setup::ObjectType::A)) { // B touche A
                    auto now = std::chrono::steady_clock::now();
                    auto& objB = objects[i]->type == static_cast<int>(setup::ObjectType::B) ? objects[i] : objects[j];

                    // Dupliquer seulement si suffisamment de temps s'est écoulé
                    if (std::chrono::duration_cast<std::chrono::milliseconds>(now - objB->lastDuplicationTime).count() > 500 && !objB->hasDuplicated && should_Create_Object(2)) { // 500 ms
                        this->B_duplication++;
                        auto newObj = std::make_unique<ObjectB>();
                        newObj->shape.setPosition(objB->shape.getPosition());
                        sf::Vector2f offset(rand() % 20 - 10, rand() % 20 - 10);
                        newObj->shape.move(offset);
                        newObj->velocity.x = -newObj->velocity.x + rand() % 3 - 1;
                        newObj->velocity.y = -newObj->velocity.y + rand() % 3 - 1;
                        newObj->handleInteraction();
                        newObjects.push_back(std::move(newObj)); 
                        objB->lastDuplicationTime = now; 
                        objB->handleInteraction();
                    }
                }
                else if (objects[i]->type == static_cast<int>(setup::ObjectType::C) && objects[j]->type == static_cast<int>(setup::ObjectType::B)) { // C touche B
                    auto now = std::chrono::steady_clock::now();
                    auto& objC = objects[i]->type == static_cast<int>(setup::ObjectType::C) ? objects[i] : objects[j];

                    // Dupliquer seulement si suffisamment de temps s'est écoulé
                    if (std::chrono::duration_cast<std::chrono::milliseconds>(now - objC->lastDuplicationTime).count() > 500 && !objC->hasDuplicated && should_Create_Object(3)) { //500 ms
                        this->C_duplication++;
                        auto newObj = std::make_unique<ObjectC>();
                        newObj->shape.setPosition(objC->shape.getPosition());
                        sf::Vector2f offset(rand() % 20 - 10, rand() % 20 - 10); 
                        newObj->shape.move(offset);
                        newObj->velocity.x = -newObj->velocity.x + rand() % 3 - 1;
                        newObj->velocity.y = -newObj->velocity.y + rand() % 3 - 1;
                        newObj->handleInteraction();
                        newObjects.push_back(std::move(newObj));

                        objC->lastDuplicationTime = now;
                        objC->handleInteraction();
                    }
                }
                else if (objects[i]->type == static_cast<int>(setup::ObjectType::D) && objects[j]->type == static_cast<int>(setup::ObjectType::C)) { // D touche C
                    auto now = std::chrono::steady_clock::now();
                    auto& objD = objects[i]->type == static_cast<int>(setup::ObjectType::D) ? objects[i] : objects[j];
                    objects[i]->velocity.x = -objects[i]->velocity.x; 
                    objects[i]->velocity.y = -objects[i]->velocity.y; 
                    if (std::chrono::duration_cast<std::chrono::milliseconds>(now - objD->lastDuplicationTime).count() > 2000 && !objD->hasDuplicated && should_Create_Object(4)) { //500 ms
                        for (int n = 0; n < 1; ++n) {
                            auto newObj = std::make_unique<ObjectD>();
                            newObj->shape.setPosition(objD->shape.getPosition());
                            newObj->velocity.x = -newObj->velocity.x;
                            newObj->velocity.y = -newObj->velocity.y;
                            newObj->handleInteraction();
                            newObjects.push_back(std::move(newObj));
                            this->D_duplication++;
                        }
                        objD->lastDuplicationTime = now; 
                        objD->hasDuplicated = true; 
                        objD->handleInteraction();
                    }
                }

            }
        }
    }
    if (objects.size() == 0 && !isEnd) {
        saveStatistic(removeAnsiCodes(this->statistics));
        this->isEnd = true;
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
    if (count > number_of_iterations_before_displaying_statistics) {
        this->statistics = " ";
        this->statistics += "\n";
        this->statistics += "statistics ID: " + std::to_string(this->ID);
        this->statistics += "\n";
        this->statistics += this->RED + "A" + this->RESET + " as been duplicate " + std::to_string(this->A_duplication) + " time" + "\n";
        this->statistics += this->BLUE + "B" + this->RESET + " as been duplicate " + std::to_string(this->B_duplication) + " time" + "\n";
        this->statistics += this->GREEN + "C" + this->RESET + " as been duplicate " + std::to_string(this->C_duplication) + " time" + "\n";
        this->statistics += this->MAGENTA + "D" + this->RESET + " as been duplicate " + std::to_string(this->D_duplication) + " time" + "\n";
        this->statistics += ".\n";
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
    if (elapsedTime.asMilliseconds() < X_HZ_REFRESH_PERIOD) { //fPS 60 with T = 16.67ms (calculus = 1000 / 60 fps )
        sf::sleep(sf::milliseconds(X_HZ_REFRESH_PERIOD) - elapsedTime);
    }clock.restart();
}

void setup::saveStatistic(const std::string& stat) {
    std::ofstream file("statistics.txt", std::ios::app);

    if (file.is_open()) {
        file << stat << std::endl;
        file.close();
    }
    else {
        std::cerr << "Unable to open file" << std::endl;
    }
}

std::string setup::removeAnsiCodes(const std::string& input) {
    std::regex ansiRegex("\\x1B\\[[0-9;]*[A-Za-z]"); 
    return std::regex_replace(input, ansiRegex, "");
}

bool setup::should_Create_Object(int type) {
    auto now = std::chrono::steady_clock::now();
    if (objectCount[type] >= MAX_OBJECTS_PER_TYPE) {
        if (now - lastCreationTime[type] > PAUSE_DURATION) {
            objectCount[type] = 0; // Réinitialiser le compteur après la pause
            lastCreationTime[type] = now; // Réinitialiser le temporisateur
            return true;
        }
        return false;
    }
    objectCount[type]++;
    lastCreationTime[type] = now;
    return true;
}