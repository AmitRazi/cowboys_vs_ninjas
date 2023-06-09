//
// Created by 97250 on 02/05/2023.
//

#include "Team2.hpp"
#include <stdexcept>
using namespace ariel;

void Team2::attack(Team *enemy_team) {
    if (enemy_team == nullptr) {
        throw std::invalid_argument("NULL argument\n");
    }

    Character* captain = getCaptain();

    if (!captain->isAlive()) {
        appoint_leader();
        captain = getCaptain();
    }

    if (captain == nullptr) {
        throw std::runtime_error("All the team is already dead");
    }

    Character *closet = closest_enemy(enemy_team);

    if (closet == nullptr) {
        throw std::runtime_error("All the enemy team is dead");
    }

    size_t i;

    for (i = 0; i < MAX_TEAMMATES; i++) {
        if (!closet->isAlive()) {
            closet = closest_enemy(enemy_team);
        }

        if (closet == nullptr) break;

        Character* teammate = getTeamMember(i);

        if (teammate != nullptr && teammate->isAlive()) {
            teammate->attack(closet);
        }
    }

}

void Team2::print() const{
    for (size_t i = 0; i < MAX_TEAMMATES; i++) {
        Character* teammate = getTeamMember(i);

        if(teammate != nullptr){
            teammate->print();
        }
    }
}
