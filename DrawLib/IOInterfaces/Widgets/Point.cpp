#include <algorithm>

#include "Point.h"
#include "../Utility/Utility.h"

Point::Point(const double& x_, const double& y_) : x(x_), y(y_)
{

}

bool Point::operator == (const Point& other) const
{
    return equal(other.x, x) && equal(other.y, y);
}

bool Point::operator != (const Point& other) const
{
    return !equal(other.x, x) || !equal(other.y, y);
}

Point Point::operator = (const Point& other)
{
    x = other.x;
    y = other.y;

    return Point(x, y);
}

Point Point::operator + (const Point& other) const
{
    return Point(x+other.x, y+other.y);
}

Point Point::operator - (const Point& other) const
{
    return Point(x-other.x, y-other.y);
}

Point Point::operator - () const
{
    return Point(-x, -y);
}

Point Point::operator * (const double& d) const
{
    return Point(x*d, y*d);
}

Point Point::operator / (const double& d) const
{
    return Point(x/d, y/d);
}

void Point::operator += (const Point& other)
{
    x += other.x;
    y += other.y;
}

void Point::operator -= (const Point& other)
{
    x -= other.x;
    y -= other.y;
}

void Point::operator *= (const double& d)
{
    x *= d;
    y *= d;
}

void Point::operator /= (const double& d)
{
    x /= d;
    y /= d;
}

Point min_xyz(const Point& l, const Point& r)
{
    return Point(std::min(l.x, r.x), std::min(l.y, r.y));
}

Point max_xyz(const Point& l, const Point& r)
{
    return Point(std::max(l.x, r.x), std::max(l.y, r.y));
}
