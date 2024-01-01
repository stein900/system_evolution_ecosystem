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
class setup{

private:
    int A_duplication = 0;
    int B_duplication = 0;
    int C_duplication = 0;
    int D_duplication = 0;
    int A_delete = 0;
    int B_delete = 0;
    int C_delete = 0;
    int D_delete = 0;
    const std::string RED = "\033[31m";
    const std::string BLUE = "\033[34m";
    const std::string GREEN = "\033[32m";
    const std::string MAGENTA = "\033[35m";
    const std::string RESET = "\033[0m";
    std::string statistics = "Waiting...";


public:
    sf::RenderWindow window;
    sf::Event event;
    sf::Clock clock;
    std::vector<std::unique_ptr<GameObject>> objects;
    std::vector<std::unique_ptr<GameObject>> newObjects;
    std::vector<size_t> toRemove;
    int count = 0;
public:
    setup();
    void drawing_object();
    void handle_Collision();
    bool collision(const std::unique_ptr<GameObject>& a, const std::unique_ptr<GameObject>& b);
    void delete_Object();
    void merge_Duplicated_object();
    std::string see_Evolution_Statistic();
    void handle_Frame_rate_per_seconds_stability();

};

