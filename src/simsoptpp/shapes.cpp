#include "shapes.h"
#include <cmath>

using namespace std;

Cylinder::Cylinder(Array _base_point, double _height, double _radius, double theta, double phi){
    base_point = xt::zeros<double>({3});
    top_point = xt::zeros<double>({3});
    axis_vector = xt::zeros<double>({3});
    
    for (int i = 0; i < 3; ++i) {
        base_point[i] = _base_point[i];
    }

    height = _height;
    radius = _radius;

    axis_vector[0] = sin(theta)*cos(phi);
    axis_vector[1] = sin(theta)*sin(phi);
    axis_vector[2] = cos(theta);

    top_point[0] = base_point[0] + height*axis_vector[0];
    top_point[1] = base_point[1] + height*axis_vector[1];
    top_point[2] = base_point[2] + height*axis_vector[2];
}

Cylinder::Cylinder(double r_major, double r_minor, double toroidal_angle, double poloidal_angle, double _height, double _radius, double theta, double phi){
    base_point = xt::zeros<double>({3});
    top_point = xt::zeros<double>({3});
    axis_vector = xt::zeros<double>({3});

    height = _height;
    radius = _radius;

    base_point[0] = (r_major + r_minor*cos(poloidal_angle))*cos(toroidal_angle);
    base_point[1] = (r_major + r_minor*cos(poloidal_angle))*sin(toroidal_angle);
    base_point[2] = r_minor*sin(poloidal_angle);

    axis_vector[0] = sin(theta)*cos(phi);
    axis_vector[1] = sin(theta)*sin(phi);
    axis_vector[2] = cos(theta);

    top_point[0] = base_point[0] + height*axis_vector[0];
    top_point[1] = base_point[1] + height*axis_vector[1];
    top_point[2] = base_point[2] + height*axis_vector[2];
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

/*
bool Cylinder::condition(Array point) {
    //find the normal vector (the vector that defines the axis of the cylinder)
    double a = top_point[0] - base_point[0];
    double b = top_point[1] - base_point[1];
    double c = top_point[2] - base_point[2]; 

    //compute the cylinder and plane equations.
    return  ((((point[1]-base_point[1])*(point[2]-top_point[2]) - (point[2]-base_point[2])*(point[1]-top_point[1]))*
            ((point[1]-base_point[1])*(point[2]-top_point[2]) - (point[2]-base_point[2])*(point[1]-top_point[1]))+
            ((point[2]-base_point[2])*(point[0]-top_point[0]) - (point[0]-base_point[0])*(point[2]-top_point[2]))*
            ((point[2]-base_point[2])*(point[0]-top_point[0]) - (point[0]-base_point[0])*(point[2]-top_point[2]))+
            ((point[0]-base_point[0])*(point[1]-top_point[1]) - (point[1]-base_point[1])*(point[0]-top_point[0]))*
            ((point[0]-base_point[0])*(point[1]-top_point[1]) - (point[1]-base_point[1])*(point[0]-top_point[0]))-
            radius*radius*height*height <= 0 )
            && (a*(point[0]-top_point[0]) + b*(point[1]-top_point[1]) + c*(point[2]-top_point[2]) <= 0)
            && (a*(point[0]-base_point[0]) + b*(point[1]-base_point[1]) + c*(point[2]-base_point[2]) >= 0)) ;
}
*/
/*
bool Cylinder::condition(Array point, double lower_bound, double upper_bound){

    
    return  ((point[1]-base_point[1])*(point[2]-top_point[2]) - (point[2]-base_point[2])*(point[1]-top_point[1]))*
            ((point[1]-base_point[1])*(point[2]-top_point[2]) - (point[2]-base_point[2])*(point[1]-top_point[1]))+
            ((point[2]-base_point[2])*(point[0]-top_point[0]) - (point[0]-base_point[0])*(point[2]-top_point[2]))*
            ((point[2]-base_point[2])*(point[0]-top_point[0]) - (point[0]-base_point[0])*(point[2]-top_point[2]))+
            ((point[0]-base_point[0])*(point[1]-top_point[1]) - (point[1]-base_point[1])*(point[0]-top_point[0]))*
            ((point[0]-base_point[0])*(point[1]-top_point[1]) - (point[1]-base_point[1])*(point[0]-top_point[0]))-
            radius*radius*height*height < 0 ;
}
*/