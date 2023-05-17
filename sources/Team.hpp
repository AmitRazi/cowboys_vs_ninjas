//
// Created by 97250 on 01/05/2023.
//

#ifndef SP_4_TEAM_HPP
#define SP_4_TEAM_HPP


#include <array>
#include <typeinfo>
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

        static Character *closest_character(const Team *to_search, const Character *dest_char);

        Character *closest_enemy(Team *team) const;


    public:
        explicit Team(Character *captain);

        virtual ~Team();

        void add(Character *character);

        virtual void attack(Team *enemy);

        virtual void print() const;

        int stillAlive() const;

        Character* getTeamMember(size_t index) const;
    };
}

#endif //SP_4_TEAM_HPP
