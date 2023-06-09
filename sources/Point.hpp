#ifndef SP_4_POINT_HPP
#define SP_4_POINT_HPP

#include <string>
namespace ariel {
    class Point {
    private:
        double _x;
        double _y;

    public:
        explicit Point(const double x_cor = 0, const double y_cor = 0) : _x(x_cor), _y(y_cor) {}

        double distance(const Point &other) const;

        std::string print() const;

        static Point moveTowards(const Point &src, const Point &dst,double);

        static Point moveAwayFrom(const Point &src, double);
    };
}
#endif //SP_4_POINT_HPP
