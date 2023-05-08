//
// Created by 97250 on 02/05/2023.
//

#ifndef SP_4_TEAM2_HPP
#define SP_4_TEAM2_HPP


#include "Team.hpp"
namespace ariel {
    class Team2 : public Team {
    public:
        explicit Team2(Character *captain) : Team(captain) {}

        void attack(Team *) override;

        void print() const override;

    };
}

#endif //SP_4_TEAM2_HPP
