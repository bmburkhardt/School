//Bryan burkhardt
//CS202
//Lab 05 ThreeD source file
#include "Points.h"

//ThreeD constructor that sets x, y, and z to values passed to function
ThreeD::ThreeD(double x, double y, double z):TwoD(x, y), z_(z)
{}

double ThreeD::getZ()
{
    return z_;
}
void ThreeD::setZ(double z)
{
    z_=z;
}

//Distance function that calculates the euclidean distance between two 3-dimensional points
double distance(ThreeD i, ThreeD j)
{
    double xi = i.getX();
    double yi = i.getY();
    double xj = j.getX();
    double yj = j.getY();
    double zi = i.getZ();
    double zj = j.getZ();
    return (sqrt(pow(xj-xi, 2.0) + pow(yj-yi, 2.0) + pow(zj-zi, 2.0)));
}
