//
// Created by 97250 on 12/05/2023.
//

#ifndef COWBOYS_VS_NINJAS_SMARTTEAM_HPP
#define COWBOYS_VS_NINJAS_SMARTTEAM_HPP

#include "Team.hpp"

namespace ariel {
    class SmartTeam : public Team {
    public:
        explicit SmartTeam(Character *captain) : Team(captain) {}

        void attack(Team *) override;

        void print() const override;

        Character* find_weakest(Team* team) const;
        Character* find_close_ninja(Team* team) const;



    };
}

#endif //COWBOYS_VS_NINJAS_SMARTTEAM_HPP
