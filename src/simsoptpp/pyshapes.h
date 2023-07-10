#pragma once
#include "shapes.h"
typedef xt::pyarray<double> PyArray;
#include "xtensor-python/pyarray.hpp"     // Numpy bindings

class PyShape : public Shape {
public:
    /* Inherit the constructors */
    using Shape::Shape;

    /* Trampoline (need one for each virtual function) */
    bool condition(Array point) override {
        PYBIND11_OVERRIDE_PURE(
            bool, /* Return type */
            Shape,      /* Parent class */
            condition,          /* Name of function in C++ (must match Python name) */
            point      /* Argument(s) */
        );
    }
};