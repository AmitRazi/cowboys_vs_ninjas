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
        printed_name = getName();
        hit_points = "Hit points: " + std::to_string(getHitPoints());
    }

    return "Name: C. " + printed_name + ", " + hit_points + ", Position: " + getLocation().print();
}

void Cowboy::shoot(Character *enemy) {
    if (hasboolets() == false) {
        return;
    }

    if (isAlive() == false) {
        throw std::runtime_error("Cowboy is dead");
    }

    if (enemy->isAlive() == false) {
        throw std::runtime_error("The enemy is already dead");
    }

    if(enemy == this){
        throw std::runtime_error("A character can not attack itself");
    }

    enemy->hit(DAMAGE);
    _bullets--;

}

bool Cowboy::hasboolets() const {
    return _bullets > 0;
}

void Cowboy::reload() {
    if (isAlive() == false) {
        throw std::runtime_error("Cowboy is dead");
    }
    _bullets = FULL_CLIP;
}

void Cowboy::attack(Character *enemy) {
    if (hasboolets()) {
        shoot(enemy);
    } else {
        reload();
    }
}