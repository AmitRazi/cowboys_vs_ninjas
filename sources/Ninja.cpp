//
// Created by 97250 on 01/05/2023.
//

#include <iostream>
#include "Ninja.hpp"

using namespace ariel;

std::string Ninja::print() const {
    std::string printed_name, hit_points;
    if (!isAlive()) {
        printed_name = "(" + getName() + ")";
        hit_points = "";
    } else {
        printed_name = getName();
        hit_points = "Hit points: " + std::to_string(getHitPoints());
    }

    return "Name: N. " + printed_name + ", " + hit_points + ", Position: " + getLocation().print();
}

void Ninja::move(const Character *enemy) {
    if (isAlive()) {
        Point closest_point = Point::moveTowards(this->getLocation(), enemy->getLocation(), this->_speed);
        this->setLocation(closest_point);
    }

}

void Ninja::slash(Character *enemy) const {
    if (isAlive() == false) {
        throw std::runtime_error("Ninja is already dead");
    }

    if (enemy->isAlive() == false) {
        throw std::runtime_error("The enemy is already dead");
    }

    if (enemy == this) {
        throw std::runtime_error("A character can't attack itself");
    }


    if(distance(enemy) <= 1) {
        enemy->hit(DAMAGE);
    }

}

void Ninja::attack(Character *enemy) {
    double distance = this->distance(enemy);

    if (distance <= 1) {
        slash(enemy);
    } else {
        move(enemy);
    }
}

int Ninja::getSpeed() const{
    return _speed;
}