#ifndef POINT_H
#define POINT_H

class Point
{
public:
    double x, y;

    Point(const double& x_=0, const double& y_=0);

    bool operator == (const Point& other) const;
    bool operator != (const Point& other) const;
    Point operator = (const Point& other);
    Point operator + (const Point& other) const;
    Point operator - (const Point& other) const;
    Point operator - () const;
    Point operator * (const double& d) const;
    Point operator / (const double& d) const;

    void operator += (const Point& other);
    void operator -= (const Point& other);
    void operator *= (const double& d);
    void operator /= (const double& d);
};

Point min_xyz(const Point& l, const Point& r);
Point max_xyz(const Point& l, const Point& r);

#endif // POINT_H
