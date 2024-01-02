#pragma once
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
#include <fstream>
#include <string>
#include <regex>
#include <unordered_map>
#include "Settings.h"
class GameObject;
class setup{

private:
    int A_duplication = 0, B_duplication = 0, C_duplication = 0, D_duplication = 0;
    int A_delete = 0, B_delete = 0, C_delete = 0, D_delete = 0;
    const std::string RED = "\033[31m", BLUE = "\033[34m", GREEN = "\033[32m";
    const std::string MAGENTA = "\033[35m", RESET = "\033[0m";
    int ID;

    std::unordered_map<int, int> objectCount; // Compteur d'objets par type
    std::unordered_map<int, std::chrono::time_point<std::chrono::steady_clock>> lastCreationTime; // Dernière création par type
    const int MAX_OBJECTS_PER_TYPE = settings_Obj.MAX_OBJECTS_PER_TYPE_VAR;
    const std::chrono::seconds PAUSE_DURATION = std::chrono::seconds(settings_Obj.PAUSE_DURATION_AFTER_CREATION);


public:
    Settings settings_Obj;
    //GameObject gameObj_Object;
    //GameObject* gameObj_Object = new GameObject();
    /*std::unique_ptr<GameObject> gameObj_Object = std::make_unique<GameObject>();*/
    sf::RenderWindow window;
    sf::Event event;
    sf::Clock clock;
    std::vector<std::unique_ptr<GameObject>> objects;
    std::vector<std::unique_ptr<GameObject>> newObjects;
    std::vector<size_t> toRemove;
    int count = 0;
    int number_of_iterations_before_displaying_statistics = settings_Obj.NUMBER_OF_ITERATIONS_BEFORE_DISPLAYING_STATISTICS;
    std::string statistics = "Waiting...";
    bool isEnd = false;
    float X_HZ_REFRESH_PERIOD = 1000 / settings_Obj.NUMBER_OF_FRAME_RATE_PER_SECONDS;
    enum class ObjectType { none, A, B, C, D};
    std::string algorithm_help = " ";

public:
    setup();
    void drawing_object();
    void handle_Collision();
    bool collision(const std::unique_ptr<GameObject>& a, const std::unique_ptr<GameObject>& b);
    void delete_Object();
    void merge_Duplicated_object();
    std::string see_Evolution_Statistic();
    void handle_Frame_rate_per_seconds_stability();
    void saveStatistic(const std::string& stat);
    std::string removeAnsiCodes(const std::string& input);
    bool should_Create_Object(int type);

};

