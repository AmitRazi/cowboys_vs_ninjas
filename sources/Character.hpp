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
    public:
        const std::string &_name;
        Point _pos;
        int _hit_points;

        Character(const std::string &name, const Point &pos, const int hit_points) : _name(name), _pos(pos),
                                                                                     _hit_points(hit_points) {
        }

        double distance(Character *other) const;

        void hit(int);

        const std::string &getName() const;

        const Point &getLocation() const;

        bool isAlive() const;

        virtual std::string print() const = 0;

        virtual void attack(Character *) = 0;
    };
}

#endif //SP_4_CHARACTER_HPP
