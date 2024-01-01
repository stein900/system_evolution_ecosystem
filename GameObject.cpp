#include "GameObject.h"

GameObject::GameObject(float radius, int initType = 0)
    : shape(radius), type(initType), isInteracting(true), visionRange(0) {

    shape.setFillColor(sf::Color::Red);

    float speedX = ((rand() % 200 - 100) / 100.0f) * settings_Obj.SPEED_MULTIPLICATION; // valeur entre -1 et 1
    float speedY = ((rand() % 200 - 100) / 100.0f) * settings_Obj.SPEED_MULTIPLICATION;
    velocity = sf::Vector2f(speedX, speedY);
    lastDuplicationTime = std::chrono::steady_clock::now();
    creationTime = std::chrono::steady_clock::now();
    if (settings_Obj.INDIVIDUAL_VISION_BEHAVIOR) {
        if (this->type == 1)
            visionRange = settings_Obj.VISION_RANGE_OF_A_ObJECT_TYPE; /* Exemple: 100 unités de distance */ visionAngle = settings_Obj.VISION_ANGLE_OF_A_ObJECT_TYPE; // Exemple : 45 degrés de chaque côté de la direction de la vitesse
        if (this->type == 2)
            visionRange = settings_Obj.VISION_RANGE_OF_B_ObJECT_TYPE; visionAngle = settings_Obj.VISION_ANGLE_OF_B_ObJECT_TYPE;
        if (this->type == 3)
            visionRange = settings_Obj.VISION_RANGE_OF_C_ObJECT_TYPE; visionAngle = settings_Obj.VISION_ANGLE_OF_C_ObJECT_TYPE;
        if (this->type == 4)
            visionRange = settings_Obj.VISION_RANGE_OF_D_ObJECT_TYPE; visionAngle = settings_Obj.VISION_ANGLE_OF_D_ObJECT_TYPE;
    }
    else
        visionRange = settings_Obj.VISION_RANGE; //Exemple: 100 unités de distance
        visionAngle = settings_Obj.VISION_ANGLE; // Exemple : 45 degrés de chaque côté de la direction de la vitesse
    
    lastInteractionTime = std::chrono::steady_clock::now() - blindDuration;
}

void GameObject::update(const sf::RenderWindow& window, const std::vector<std::unique_ptr<GameObject>>& allObjects) {

    if (settings_Obj.SMART_SURVIVAL_INSTINCT_MODE) {
        auto now = std::chrono::steady_clock::now();
        bool interactionOccurred = false;

        if (now - lastInteractionTime > blindDuration) {
            isInteracting = false;
        }

        if (!isInteracting) {
            auto seenObjects = objectsInVision(allObjects);
            for (const auto& seen : seenObjects) {
                int seenType = seen.first;
                sf::Vector2f seenPosition = seen.second;
                sf::Vector2f direction = seenPosition - shape.getPosition();
                float length = std::sqrt(direction.x * direction.x + direction.y * direction.y);
                sf::Vector2f directionNormalized = direction / length;

                if (type == 1) {
                    if (seenType == 4) { // Si la boule A voit une boule D, elle s'oriente vers elle
                        velocity = directionNormalized * HUNT_SPEED;
                    }
                    else if (seenType == 3) { // Si la boule A voit une boule C, elle s'enfuit
                        velocity = -directionNormalized * ESCAPE_SPEED;
                    }
                }
                if (type == 2) {
                    if (seenType == 1) { // Si la boule B voit une boule A, elle s'oriente vers elle
                        velocity = directionNormalized * HUNT_SPEED;
                    }
                }
                if (type == 3) {
                    if (seenType == 2) { // Si la boule C voit une boule B, elle s'oriente vers elle
                        velocity = directionNormalized * HUNT_SPEED;
                    }
                    else if (seenType == 1) { // Si la boule C voit une boule A, elle s'enfuit
                        velocity = -directionNormalized * ESCAPE_SPEED;
                    }
                }
                if (type == 4) {
                    if (seenType == 3) { // Si la boule D voit une boule C, elle s'oriente vers elle
                        velocity = directionNormalized * HUNT_SPEED;
                    }
                    else if (seenType == 2) { // Si la boule D voit une boule B, elle s'enfuit
                        velocity = -directionNormalized * ESCAPE_SPEED;
                    }
                }
            }
        }


        if (interactionOccurred) {
            lastInteractionTime = now;
            isInteracting = true;
        }
    }


    shape.move(velocity);

    if (shape.getPosition().x < 0 || shape.getPosition().x > window.getSize().x) {
        velocity.x = -velocity.x;
    }
    if (shape.getPosition().y < 0 || shape.getPosition().y > window.getSize().y) {
        velocity.y = -velocity.y;
    }
}

bool GameObject::isAlive() const {
    auto now = std::chrono::steady_clock::now();
    if (settings_Obj.INDIVIDUAL_LIFETIME) {
        if (this->type == 1)
            return std::chrono::duration_cast<std::chrono::seconds>(now - creationTime).count() < settings_Obj.TIME_TO_LIVE_FOR_A;
        if (this->type == 2)
            return std::chrono::duration_cast<std::chrono::seconds>(now - creationTime).count() < settings_Obj.TIME_TO_LIVE_FOR_B;
        if (this->type == 3)
            return std::chrono::duration_cast<std::chrono::seconds>(now - creationTime).count() < settings_Obj.TIME_TO_LIVE_FOR_C;
        if (this->type == 4)
            return std::chrono::duration_cast<std::chrono::seconds>(now - creationTime).count() < settings_Obj.TIME_TO_LIVE_FOR_D;
    }
    else
        return std::chrono::duration_cast<std::chrono::seconds>(now - creationTime).count() < settings_Obj.TIME_TO_LIVE;
}

void GameObject::draw(sf::RenderWindow& window) {
    window.draw(shape);
}

// Modification de objectsInVision pour retourner également la position
std::vector<std::pair<int, sf::Vector2f>> GameObject::objectsInVision(const std::vector<std::unique_ptr<GameObject>>& objects) {
    std::vector<std::pair<int, sf::Vector2f>> seenObjects;
    for (const auto& obj : objects) {
        if (obj.get() != this && obj->isAlive()) { // Ne pas se détecter soi-même et vérifier que l'objet est en vie
            sf::Vector2f directionToObj = obj->shape.getPosition() - shape.getPosition();
            float distanceToObj = sqrt(directionToObj.x * directionToObj.x + directionToObj.y * directionToObj.y);
            if (distanceToObj <= visionRange) {
                float angleToObj = atan2(directionToObj.y, directionToObj.x);
                float angleOfVelocity = atan2(velocity.y, velocity.x);
                if (std::abs(angleToObj - angleOfVelocity) <= visionAngle) {
                    seenObjects.emplace_back(obj->type, obj->shape.getPosition());
                }
            }
        }
    }
    return seenObjects;
}

void GameObject::handleInteraction() {
    if (settings_Obj.IS_BIND_MODE) {
        auto now = std::chrono::steady_clock::now();
        lastInteractionTime = now;
        isInteracting = true;

        velocity.x = -velocity.x + rand() % 3 - 1;
        velocity.y = -velocity.y + rand() % 3 - 1;
    }
}