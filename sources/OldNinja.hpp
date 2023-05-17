//
// Created by 97250 on 01/05/2023.
//

#ifndef SP_4_OLDNINJA_HPP
#define SP_4_OLDNINJA_HPP

#include "Ninja.hpp"

namespace ariel {
    const int SPEED_OLD = 8;
    const int INTIAL_HITPOINTS_OLD = 150;

    class OldNinja : public Ninja {
    public:
        OldNinja(const std::string &name, const Point &pos) : Ninja(name, SPEED_OLD,pos, INTIAL_HITPOINTS_OLD) {}
    };
}

#endif //SP_4_OLDNINJA_HPP
