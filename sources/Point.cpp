
#include "Point.hpp"
#include <stdexcept>
#include <cmath>
using namespace ariel;
double Point::distance(const Point &other) const {
    if(this->_x == other._x && this->_y == other._y){
        return 0;
    }
    return sqrt(pow(_x - other._x, 2) + pow(_y - other._y, 2));
}

std::string Point::print() const {
    return  "(" + std::to_string(_x) + "," + std::to_string(_y) + ")\n";
}


Point Point::moveTowards(const Point &src, const Point &dest, const double distance) {
    if(distance < 0 ){
        throw std::invalid_argument("Distance can not be negative\n");
    }

    double distance_to = src.distance(dest);
    if (distance_to <= distance) {
        return Point{dest};
    }

    double unit_x = (dest._x - src._x) / distance_to;
    double unit_y = (dest._y - src._y) / distance_to;

    double scaled_x = unit_x * distance;
    double scaled_y = unit_y * distance;

    return Point{src._x + scaled_x, src._y + scaled_y};
}

Point Point::moveAwayFrom(const Point &src,const double distance){
    if(distance < 0 ){
        throw std::invalid_argument("Distance can not be negative\n");
    }



    return Point{src._x +distance, src._y};
}