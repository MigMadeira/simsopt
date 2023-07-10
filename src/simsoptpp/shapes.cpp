#include "shapes.h"
#include <cmath>

using namespace std;

Cylinder::Cylinder(Array _base_point, double _height, double _radius, double theta, double phi){
    base_point = xt::zeros<double>({3});
    top_point = xt::zeros<double>({3});
    for (int i = 0; i < 3; ++i) {
        base_point[i] = _base_point[i];
    }
    height = _height;
    radius = _radius;
    top_point[0] = base_point[0] + height*sin(theta)*cos(phi);
    top_point[1] = base_point[1] + height*sin(theta)*sin(phi);
    top_point[2] = base_point[2] + height*cos(theta);
}

Cylinder::Cylinder(double r_major, double r_minor, double toroidal_angle, double poloidal_angle, double _height, double _radius, double theta, double phi){
    base_point = xt::zeros<double>({3});
    top_point = xt::zeros<double>({3});

    height = _height;
    radius = _radius;

    base_point[0] = (r_major + r_minor*cos(poloidal_angle))*cos(toroidal_angle);
    base_point[1] = (r_major + r_minor*cos(poloidal_angle))*sin(toroidal_angle);
    base_point[2] = r_minor*sin(poloidal_angle);

    top_point[0] = base_point[0] + height*sin(theta)*cos(phi);
    top_point[1] = base_point[1] + height*sin(theta)*sin(phi);
    top_point[2] = base_point[2] + height*cos(theta);
}

bool Cylinder::condition(Array point){
    return  ((point[1]-base_point[1])*(point[2]-top_point[2]) - (point[2]-base_point[2])*(point[1]-top_point[1]))*
            ((point[1]-base_point[1])*(point[2]-top_point[2]) - (point[2]-base_point[2])*(point[1]-top_point[1]))+
            ((point[2]-base_point[2])*(point[0]-top_point[0]) - (point[0]-base_point[0])*(point[2]-top_point[2]))*
            ((point[2]-base_point[2])*(point[0]-top_point[0]) - (point[0]-base_point[0])*(point[2]-top_point[2]))+
            ((point[0]-base_point[0])*(point[1]-top_point[1]) - (point[1]-base_point[1])*(point[0]-top_point[0]))*
            ((point[0]-base_point[0])*(point[1]-top_point[1]) - (point[1]-base_point[1])*(point[0]-top_point[0]))-
            radius*radius*height*height < 0 ;
}

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