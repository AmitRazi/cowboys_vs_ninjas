//
// Created by 97250 on 01/05/2023.
//

#ifndef SP_4_TEAM_HPP
#define SP_4_TEAM_HPP


#include <array>
#include <typeinfo>
#include "Character.hpp"
#include "Ninja.hpp"
#include "OldNinja.hpp"
#include "YoungNinja.hpp"
#include "TrainedNinja.hpp"
#include "Cowboy.hpp"
namespace ariel {
    static const int MAX_TEAMMATES = 10;

    class Team {
    protected:
        std::array<Character *, MAX_TEAMMATES> _team;
        Character *_captain;
        size_t _teammates;

        void appoint_leader();

        static Character *closest_mate(Team *, const Character *);

        Character *closest_enemy(Team *) const;

    public:
        explicit Team(Character *);

        virtual ~Team();

        void add(Character *);

        virtual void attack(Team *);

        virtual void print() const;

        int stillAlive() const;
    };
}

#endif //SP_4_TEAM_HPP
