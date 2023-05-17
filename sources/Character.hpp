//
// Created by 97250 on 01/05/2023.
//

#ifndef SP_4_CHARACTER_HPP
#define SP_4_CHARACTER_HPP


#include <string>
#include "Point.hpp"
#include <stdexcept>

namespace ariel {
    class Character {
    protected:
        Character(const std::string &name, const Point &pos, const int hit_points) : _name(name), _pos(pos),
                                                                                     _hit_points(hit_points),
                                                                                     in_team(false) {
        }

        Character(const Character &other) = delete;

        Character(Character &&other) = delete;

    public:
        std::string _name;
        Point _pos;
        int _hit_points;
        bool in_team;

        double distance(Character *other) const;

        virtual ~Character() = default;

        void hit(int);

        void setTeam();

        const std::string &getName() const;

        const Point &getLocation() const;

        bool isAlive() const;

        virtual std::string print() const = 0;

        virtual void attack(Character *enemy) = 0;

        Character &operator=(Character &other) = delete;

        Character &operator=(Character &&other) = delete;
    };
}

#endif //SP_4_CHARACTER_HPP
