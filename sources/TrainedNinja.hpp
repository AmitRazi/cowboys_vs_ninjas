//
// Created by 97250 on 01/05/2023.
//

#ifndef SP_4_TRAINEDNINJA_HPP
#define SP_4_TRAINEDNINJA_HPP

#include "Ninja.hpp"
namespace ariel {
static const int SPEED_TRAINED = 12;
static const int INTIAL_HITPOINTS_TRAINED = 120;


    class TrainedNinja : public Ninja {
    public:

        TrainedNinja(const std::string &name, const Point &pos) : Ninja(name,SPEED_TRAINED,pos,
                                                                        INTIAL_HITPOINTS_TRAINED) {}
    };
}

#endif //SP_4_TRAINEDNINJA_HPP
