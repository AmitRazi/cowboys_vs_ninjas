//
// Created by 97250 on 01/05/2023.
//

#include "Team.hpp"
#include <stdexcept>
#include <limits>
#include <iostream>
using namespace ariel;
Team::Team(Character *captain) : _team{nullptr}, _teammates(0), _captain(captain) {
    if (captain == nullptr) {
        throw std::invalid_argument("NULL argument\n");
    }

    _team[_teammates++] = captain;
}

void Team::add(Character *teammate) {
    if (teammate == nullptr) {
        throw std::invalid_argument("NULL argument\n");
    }

    if (_teammates == 10) {
        throw std::runtime_error("The team is already full\n");
    }

    _team[_teammates++] = teammate;
}

void Team::attack(Team *enemy_team) {
    if (enemy_team == nullptr) {
        throw std::invalid_argument("NULL argument\n");
    }

    if(stillAlive() == 0) return;

    if (!_captain->isAlive()) {
        appoint_leader();
    }

    if (_captain == nullptr) {
        throw std::runtime_error("All the team is already dead");
    }

    Character *closet = closest_enemy(enemy_team);

    if (closet == nullptr) {
        throw std::runtime_error("All the enemy team is dead");
    }

    int i;

    for (i = 0; i < MAX_TEAMMATES*2; i++) {

        if (i < 10 && _team[i] != nullptr && (typeid(*_team[(i)]) == typeid(Cowboy))) {
            _team[i]->attack(closet);
        } else if (i >= 10 && _team[(i % 10)] != nullptr && (dynamic_cast<Ninja*>(_team[(i % 10)]) != nullptr)) {
            _team[i % 10]->attack(closet);
        }

        if (!closet->isAlive()) {
            closet = closest_mate(enemy_team, _captain);
        }

        if (closet == nullptr) return;
    }

}

void Team::print() const {
    for (int i = 0; i < MAX_TEAMMATES * 2; i++) {
        const auto &teammate = *_team[i];
        if (i < 10 && _team[i] != nullptr && (typeid(*_team[i]) == typeid(Cowboy))) {
            std::cout<<_team[i]->print();
        } else if (i >= 10 && _team[i % 10] != nullptr && (dynamic_cast<Ninja*>(_team[(i % 10)]) != nullptr)) {
            std::cout<<_team[i % 10]->print();
        }
    }
}


void Team::appoint_leader() {
    _captain = closest_mate(this, _captain);
}

Character *Team::closest_mate(Team *to_search, const Character *dest_char) {
    double min_distance = std::numeric_limits<double>::max();
    Character *new_captain = nullptr;
    Character *cur_chr = nullptr;

    for (int i = 0; i < MAX_TEAMMATES; i++) {
        cur_chr = to_search->_team[i];
        if (cur_chr == nullptr) continue;

        double distance = dest_char->distance(cur_chr);
        if (distance < min_distance && cur_chr->isAlive()) {
            new_captain = to_search->_team[i];
            min_distance = distance;
        }
    }

    return new_captain;
}

Character *Team::closest_enemy(Team *enemy_team) const {
    Character *to_attack = closest_mate(enemy_team, _captain);
    return to_attack;
}

int Team::stillAlive() const{
    int count = 0;
    for(const Character* chr: _team){
        if(chr != nullptr && chr->isAlive()) count++;
    }
    return count;
}

Team::~Team(){
    for(auto &character: _team){
        if(character != nullptr){
            delete character;
        }
    }
}