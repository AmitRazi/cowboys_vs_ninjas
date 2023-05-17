#include "Character.hpp"
using namespace ariel;
double Character::distance(Character *other) const {
    return _pos.distance(other->_pos);
}

void Character::hit(int damage) {
    if(damage < 0){
        throw std::invalid_argument("Can not hit with a negative damage");
    }
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

void Character::setTeam() { in_team = true;}

Character &Character::operator=(Character &other){
    if (this != &other) {
        _name = other._name;
        _pos = other._pos;
        _hit_points = other._hit_points;
        in_team = other.in_team;
    }
    return *this;
}
