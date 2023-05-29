#include "SmartTeam.hpp"
#include "Team.hpp"
#include <stdexcept>
#include <iostream>

using namespace ariel;

void SmartTeam::attack(Team *enemy_team) {
    if (enemy_team == nullptr) {
        throw std::invalid_argument("NULL argument\n");
    }

    Character *captain = getCaptain();

    if (!captain->isAlive()) {
        appoint_leader();
        captain = getCaptain();
        printf("appoting %d\n", stillAlive());
    }

    if (captain == nullptr) {
        throw std::runtime_error("All the team is already dead");
    }

    if (enemy_team->stillAlive() == 0) {
        throw std::runtime_error("All the enemy team is dead");
    }

    Character *closest_ninja = find_close_ninja(enemy_team);
    Character *weakest = find_weakest(enemy_team);
    Character *teammate = nullptr;
    Character *closest_to = nullptr;

    for (size_t i = 0; i < MAX_TEAMMATES * 2; i++) {
        teammate = getTeamMember(i % 10);
        if (teammate == nullptr || !teammate->isAlive()) {
            continue;
        }

        if (i < 10 && typeid(*teammate) == typeid(Cowboy)) {
            while (closest_ninja != nullptr && !closest_ninja->isAlive()) {
                find_close_ninja(enemy_team);
            }
            if (closest_ninja != nullptr) {
                teammate->attack(closest_ninja);
                continue;
            }
            weakest = weakest->isAlive() ? weakest : find_weakest(enemy_team);
            if(weakest == nullptr){
                break;
            }
            teammate->attack(weakest);
        } else if (i >= 10 && typeid(*teammate) != typeid(Cowboy)) {
            closest_to = closest_character(enemy_team, teammate);
            if (closest_to == nullptr) {
                break;
            }
            if (teammate->distance(closest_to) <= 1 && stillAliveCowboys() > 0) {
                Ninja* ninja = dynamic_cast<Ninja*>(teammate);
                Point newPosition = Point::moveAwayFrom(ninja->getLocation(),ninja->getSpeed());
                teammate->setLocation(newPosition);
            } else {
                teammate->attack(closest_to);
            }
        }
    }

}

Character *SmartTeam::find_weakest(Team *enemy) const {
    Character *weakest = nullptr;
    Character *cur = nullptr;
    for (size_t i = 0; i < MAX_TEAMMATES; i++) {
        cur = enemy->getTeamMember(i);
        if (cur == nullptr) {
            break;
        }

        if (weakest == nullptr || weakest->getHitPoints() > cur->getHitPoints()) {
            weakest = cur;
        }
    }
    return weakest;
}

//first cowboys attack any ninja that is close to a teammate
//ninjas attack the closet enemy to them with a higher priority for cowboys
Character *SmartTeam::find_close_ninja(Team *enemy) const {
    Character *closest = nullptr;
    Character *closest_to = nullptr;
    Character *cur = nullptr;

    for (size_t i = 0; i < MAX_TEAMMATES; i++) {
        cur = enemy->getTeamMember(i);
        if (cur != nullptr && typeid(*cur) != typeid(Cowboy)) {
            Character *temp = enemy->closest_character(this, cur);
            if (temp->distance(cur) <= 42) {
                if (closest == nullptr || (closest_to->getHitPoints() > temp->getHitPoints())) {
                    closest = cur;
                    closest_to = temp;
                }
            }
        }
    }

    return closest;
}


void SmartTeam::print() const {
    for (size_t i = 0; i < MAX_TEAMMATES; i++) {
        Character *teammate = getTeamMember(i);
        if (teammate != nullptr) {
            std::cout << teammate->print();
        }
    }
}

int SmartTeam::stillAliveCowboys(){
    int cowboysCount = 0;
    auto &team = getTeam();
    for(const Character* chr: team){
        if(chr == nullptr){
            break;
        }
        if(typeid(*chr) == typeid(Cowboy)){
            cowboysCount++;
        }
    }
    return cowboysCount;
}