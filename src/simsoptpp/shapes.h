#pragma once
#include <vector>
using std::vector;
#include "xtensor-python/pyarray.hpp"     // Numpy bindings
typedef xt::pyarray<double> Array;

class Shape{
    public: 
        virtual ~Shape() { }
        virtual bool condition(Array point) = 0;
};

using ShapePtr = std::shared_ptr<Shape>;

class Cylinder: public Shape{
    public:
        Array base_point;
        Array top_point;
        Array axis_vector;
        double height;
        double radius;

        Cylinder(Array _base_point, double _height, double _radius, double theta, double phi);
        Cylinder(double r_major, double r_minor, double toroidal_angle, double poloidal_angle, double _height, double _radius, double theta, double phi);

        bool condition(Array point) override;
        //bool condition(Array point, double lower_bound, double upper_bound);
};

using CylinderPtr = std::shared_ptr<Cylinder>;