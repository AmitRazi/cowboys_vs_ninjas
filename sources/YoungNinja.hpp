//
// Created by 97250 on 01/05/2023.
//

#ifndef SP_4_YOUNGNINJA_HPP
#define SP_4_YOUNGNINJA_HPP

#include "Ninja.hpp"
namespace ariel {

    static const int SPEED_YOUNG = 14;
    static const int INTIAL_HITPOINTS_YOUNG = 100;

    class YoungNinja : public Ninja {
    public:
        YoungNinja(const std::string &name, const Point &pos) : Ninja(name, SPEED_YOUNG,pos, INTIAL_HITPOINTS_YOUNG) {}
    };
}

#endif //SP_4_YOUNGNINJA_HPP
