#include "shapes.h"
#include <cmath>

using namespace std;

Cylinder::Cylinder(Array _base_point, double _height, double _radius, double theta, double phi){
    //initialize the base point and axis vector
    base_point = xt::zeros<double>({3});
    axis_vector = xt::zeros<double>({3});
    
    //define the base point of the cylinder
    for (int i = 0; i < 3; ++i) {
        base_point[i] = _base_point[i];
    }

    //define the heigh and radius of the cylinder
    height = _height;
    radius = _radius;

    //calculate the axis vector using local spherical coordinates
    axis_vector[0] = cos(theta)*sin(phi);
    axis_vector[1] = sin(theta)*sin(phi);
    axis_vector[2] = cos(phi);

}

Cylinder::Cylinder(double r_major, double r_minor, double toroidal_angle, double poloidal_angle, double _height, double _radius, double theta, double phi){
    //initialize the base point and axis vector
    base_point = xt::zeros<double>({3});
    axis_vector = xt::zeros<double>({3});

    //define the heigh and radius of the cylinder
    height = _height;
    radius = _radius;

    //calculate the base point of the cylinder using toroidal coordinates
    base_point[0] = (r_major + r_minor*cos(poloidal_angle))*cos(toroidal_angle);
    base_point[1] = (r_major + r_minor*cos(poloidal_angle))*sin(toroidal_angle);
    base_point[2] = r_minor*sin(poloidal_angle);

    //calculate the axis vector using local spherical coordinates
    axis_vector[0] = cos(theta)*sin(phi);
    axis_vector[1] = sin(theta)*sin(phi);
    axis_vector[2] = cos(phi);

}

bool Cylinder::condition(Array point) {
    // L = p - B, the point p relative to the base B
    double xL = point[0] - base_point[0];
    double yL = point[1] - base_point[1];
    double zL = point[2] - base_point[2];

    // d = distance from B along cylinder axis
    double d = axis_vector[0] * xL + axis_vector[1] * yL + axis_vector[2] * zL;

    // s = distance squared from the cylinder axis
    double s = std::pow(axis_vector[1] * zL - axis_vector[2] * yL, 2) +
              std::pow(axis_vector[2] * xL - axis_vector[0] * zL, 2) +
              std::pow(axis_vector[0] * yL - axis_vector[1] * xL, 2);
    
    // Point is within the h-tall section and within the radius
    return (d >= 0 && d <= height && s <= radius * radius); 
}