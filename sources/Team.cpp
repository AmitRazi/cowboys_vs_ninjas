//
// Created by 97250 on 01/05/2023.
//

#include "Team.hpp"
#include <stdexcept>
#include <limits>
#include <iostream>
using namespace ariel;
Team::Team(Character *captain) :_team{nullptr}, _teammates(0), _captain(captain) {
    if (captain == nullptr) {
        throw std::invalid_argument("NULL argument\n");
    }

    if(captain->in_team){
        throw std::runtime_error("Character is already in a different team\n");
    }
    std::fill(_team.begin(), _team.end(), nullptr);
    _team[_teammates++] = captain;
    captain->setTeam();
}

void Team::add(Character *teammate) {
    if (teammate == nullptr) {
        throw std::invalid_argument("NULL argument\n");
    }

    if (_teammates == 10) {
        throw std::runtime_error("The team is already full\n");
    }

    if(teammate->in_team){
        throw std::runtime_error("Character is already in a team\n");
    }

    _team[_teammates++] = teammate;
    teammate->setTeam();
}

void Team::attack(Team *enemy_team) {
    if (enemy_team == nullptr) {
        throw std::invalid_argument("NULL argument\n");
    }

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

    size_t i;

    for (i = 0; i < MAX_TEAMMATES*2; i++) {
        if (!closet->isAlive()) {
            closet = closest_enemy(enemy_team);
        }

        if (closet == nullptr) return;

        const auto &teammate = *_team[i % 10];
        if(_team[i % 10] == nullptr || teammate.isAlive() == false){
            continue;
        }

        if (i < 10 && (typeid(teammate) == typeid(Cowboy))) {
            _team[i]->attack(closet);
        } else if (i >= 10 && typeid(teammate) != typeid(Cowboy)) {
            _team[i % 10]->attack(closet);
        }
    }
}

void Team::print() const {
    for (size_t i = 0; i < MAX_TEAMMATES * 2; i++) {
        if(_team[i % 10] == nullptr){
            break;
        }

        const auto &teammate = *_team[i % i];
        if (i < 10  && (typeid(teammate) == typeid(Cowboy))) {
            std::cout<<_team[i]->print();
        } else if (i >= 10 && typeid(teammate) != typeid(Cowboy)) {
            std::cout<<_team[i % 10]->print();
        }
    }
}


void Team::appoint_leader() {
    _captain = closest_character(this, _captain);
}

Character *Team::closest_character(const Team *to_search, const Character *dest_char) {
    double min_distance = std::numeric_limits<double>::max();
    Character *closest_chr = nullptr;
    Character *cur_chr = nullptr;

    for (size_t i = 0; i < MAX_TEAMMATES; i++) {
        cur_chr = to_search->_team[i];
        if (cur_chr == nullptr) break;

        double distance = dest_char->distance(cur_chr);
        if (distance < min_distance && cur_chr->isAlive()) {
            closest_chr = to_search->_team[i];
            min_distance = distance;
        }
    }

    return closest_chr;
}

Character *Team::closest_enemy(Team *enemy_team) const {
    Character *to_attack = closest_character(enemy_team, _captain);
    return to_attack;
}

int Team::stillAlive() const{
    int count = 0;
    for(const Character* chr: _team){
        if(chr != nullptr && chr->isAlive()){
            count+=1;
        }
    }
    return count;
}

Team::~Team(){
    for(auto &character: _team){
            delete character;
    }
}

Character* Team::getTeamMember(size_t i) const { return _team[i]; }

Character* Team::getCaptain() const{
    return _captain;
}

int Team::getTeamSize() const{
    return _teammates;
}
