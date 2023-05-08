//
// Created by 97250 on 01/05/2023.
//

#include "Ninja.hpp"

using namespace ariel;
std::string Ninja::print() const {
    std::string printed_name, hit_points;
    if (!isAlive()) {
        printed_name = "(" + getName() + ")";
        hit_points = "";
    } else {
        printed_name = _name;
        hit_points = "Hit points: "+std::to_string(_hit_points);
    }

    return "Name: N. " + printed_name + ", " + hit_points + ", Position: "+_pos.print();
}

void Ninja::move(const Character *enemy) {
    if (isAlive()) {
        Point closest_point = Point::moveTowards(this->_pos, enemy->_pos, this->_speed);
        this->_pos = closest_point;
    }

}

void Ninja::slash(Character *enemy) const {
    if (this->_pos.distance(enemy->_pos) < 1) {
        enemy->hit(_speed);
    }
}

void Ninja::attack(Character *enemy) {
    if (isAlive() == false) return;

    double distance = this->distance(enemy);

    if (distance < 1) {
        slash(enemy);
    } else {
        move(enemy);
    }
}
