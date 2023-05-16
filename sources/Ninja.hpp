//
// Created by 97250 on 01/05/2023.
//

#ifndef SP_4_NINJA_HPP
#define SP_4_NINJA_HPP

#include "Character.hpp"
namespace ariel {

    class Ninja : public Character {
    private:
        int _speed;

    protected:
        Ninja(const std::string &name, const Point &pos, int speed, int hit_points) : Character(name, pos, hit_points),
                                                                                      _speed(speed) {}

    public:
        static const int DAMAGE = 40;
        std::string print() const override;

        void move(const Character *);

        void slash(Character *) const;

        void attack(Character *) override;
    };
}

#endif //SP_4_NINJA_HPP
