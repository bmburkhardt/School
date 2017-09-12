//Bryan Burkhardt
//CS202
//Lab05 TwoD source file
#include "Points.h"

TwoD::TwoD(double x, double y):x_(x), y_(y)
{}

double TwoD::getX()
{
    return x_;
}

double TwoD::getY()
{
    return y_;
}

void TwoD::setX(double x)
{
    x_=x;
}

void TwoD::setY(double y)
{
    y_=y;
}

//Distance function that calculates the euclidean distance between two 2-dimensional points
double distance(TwoD i, TwoD j)
{
    double xi = i.getX();
    double yi = i.getY();
    double xj = j.getX();
    double yj = j.getY();
    return (sqrt(pow(xj-xi, 2.0) + pow(yj-yi, 2.0)));
}
