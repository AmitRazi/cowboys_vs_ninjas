//
// Created by 97250 on 01/05/2023.
//


#include "Cowboy.hpp"

using namespace ariel;
std::string Cowboy::print() const {
    std::string printed_name, hit_points;
    if (!isAlive()) {
        printed_name = "(" + getName() + ")";
        hit_points = "";
    } else {
        printed_name = _name;
        hit_points = "Hit points: "+std::to_string(_hit_points);
    }

    return "Name: C. " + printed_name + ", " + hit_points + ", Position: "+_pos.print();
}

void Cowboy::shoot(Character *enemy)  {
    if (enemy->isAlive() && this->hasboolets()) {
        enemy->hit(DAMAGE);
        _bullets--;
    }
}

bool Cowboy::hasboolets() const {
    return _bullets > 0;
}

void Cowboy::reload() {
    _bullets = FULL_CLIP;
}

void Cowboy::attack(Character *enemy) {
    if(isAlive()){
        if(hasboolets()) {
            shoot(enemy);
        } else{
            reload();
        }
    }
}