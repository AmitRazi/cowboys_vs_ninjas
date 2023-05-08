#include "Character.hpp"
using namespace ariel;
double Character::distance(Character *other) const {
    return _pos.distance(other->_pos);
}

void Character::hit(int damage) {
    if (damage >= _hit_points) {
        _hit_points = 0;
    } else {
        _hit_points -= damage;
    }
}

const std::string &Character::getName() const {
    return _name;
}

const Point &Character::getLocation() const {
    return _pos;
}

bool Character::isAlive() const {
    return _hit_points > 0;
}
