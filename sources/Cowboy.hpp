#ifndef SP_4_COWBOY_HPP
#define SP_4_COWBOY_HPP

#include "Character.hpp"

namespace ariel {
    const int FULL_CLIP = 6;
    const int INITAIL_HITPOINTS = 110;

    const int DAMAGE = 10;

    class Cowboy : public Character {
    public:
        int _bullets;

        Cowboy(const std::string &name, const Point &point) : Character(name, point, INITAIL_HITPOINTS),
                                                              _bullets(FULL_CLIP) {
            this->getLocation().print();
        }

        std::string print() const override;

        void shoot(Character *);

        bool hasboolets() const;

        void reload();

        void attack(Character *enemy) override;

    };
}

#endif //SP_4_COWBOY_HPP
