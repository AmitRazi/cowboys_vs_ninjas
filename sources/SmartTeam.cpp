#include "SmartTeam.hpp"
#include "Team.hpp"
#include <stdexcept>
using namespace ariel;

void SmartTeam::attack(Team *enemy_team) {
    if (enemy_team == nullptr) {
        throw std::invalid_argument("NULL argument\n");
    }

    if (!_captain->isAlive()) {
        appoint_leader();
    }

    if (_captain == nullptr) {
        throw std::runtime_error("All the team is already dead");
    }

    if (enemy_team->stillAlive() == 0) {
        throw std::runtime_error("All the enemy team is dead");
    }

    Character *closet = find_close_ninja(enemy_team);

    if (closet == nullptr) {
        throw std::runtime_error("All the enemy team is dead");
    }

    size_t i;

    for (i = 0; i < MAX_TEAMMATES; i++) {
        if (!closet->isAlive()) {
            closet = closest_character(enemy_team, _captain);
        }

        if (closet == nullptr) return;

        if (_team[i] != nullptr && _team[i]->isAlive()) {
            _team[i]->attack(closet);
        }
    }

}

Character* SmartTeam::find_weakest(Team *enemy) const{
    return nullptr;
}

//first cowboys attack any ninja that is close to a teammate
//ninjas attack the closet enemy to them with a higher priority for cowboys
Character* SmartTeam::find_close_ninja(Team *enemy) const{
    Character *closest = nullptr;
    Character *closest_to = nullptr;
    Character *cur = nullptr;

    for(size_t i = 0 ; i < MAX_TEAMMATES ; i++){
        cur = enemy->getTeamMember(i);
        if(cur != nullptr && typeid(*cur) != typeid(Cowboy)){
            Character* temp = enemy->closest_character(this,cur);
            if(temp->distance(cur) <= 42){
                if(closest == nullptr || (closest_to->_hit_points > temp->_hit_points)){
                    closest = cur;
                    closest_to = temp;
                }
            }
        }
    }

    return closest;
}


void SmartTeam::print() const{
    for (size_t i = 0; i < MAX_TEAMMATES; i++) {
        if(_team[i] != nullptr){
            _team[i]->print();
        }
    }
}
