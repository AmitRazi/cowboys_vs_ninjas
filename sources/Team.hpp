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
    private:
        std::array<Character *, MAX_TEAMMATES> _team;
        Character *_captain;
        size_t _teammates;

    protected:

        void appoint_leader();

        static Character *closest_character(const Team *to_search, const Character *dest_char);

        Character *closest_enemy(Team *team) const;

        std::array<Character *, MAX_TEAMMATES> &getTeam();


    public:
        explicit Team(Character *captain);

        Team(Team &team) = delete;

        Team(Team &&team) = delete;

        virtual ~Team();

        void add(Character *character);

        virtual void attack(Team *enemy);

        virtual void print() const;

        int stillAlive() const;

        Character* getTeamMember(size_t index) const;

        Character* getCaptain() const;

        int getTeamSize() const;

        Team &operator=(Team &team) = delete;
        Team &operator=(Team &&team) = delete;
    };
}

#endif //SP_4_TEAM_HPP
