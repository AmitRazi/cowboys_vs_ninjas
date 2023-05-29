#include "Character.hpp"
using namespace ariel;
double Character::distance(Character *other) const {
    return _pos.distance(other->_pos);
}

void Character::hit(int damage) {
    if(damage < 0){
        throw std::invalid_argument("Can not hit with a negative damage");
    }
    if (damage >= _hitPoints) {
        _hitPoints = 0;
    } else {
        _hitPoints -= damage;
    }
}

const std::string &Character::getName() const {
    return _name;
}

const Point &Character::getLocation() const {
    return _pos;
}

void Character::setLocation(const Point point) {
    _pos = point;
}

bool Character::isAlive() const {
    return _hitPoints > 0;
}

void Character::setTeam() { _inTeam = true;}

int Character::getHitPoints() const{
    return _hitPoints;
}

bool Character::isInTeam() const {
    return _inTeam;
}


