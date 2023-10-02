#include "pybind11/pybind11.h"
#include "pybind11/stl.h"
#include "xtensor-python/pyarray.hpp"     // Numpy bindings
typedef xt::pyarray<double> PyArray;
namespace py = pybind11;
#include "shapes.h"
#include "pyshapes.h"


void init_shapes(py::module_ &m){
    auto pyshape = py::class_<Shape, PyShape, ShapePtr>(m, "Shape")
        .def(py::init<>())
        .def("condition", &Shape::condition);

    auto pycylinder = py::class_<Cylinder, Shape, CylinderPtr>(m, "Cylinder")
        .def(py::init<Array, double, double, double, double>())
        .def(py::init<double, double, double, double, double, double, double, double>())
        .def("condition", &Cylinder::condition)
        .def_readwrite("base_point", &Cylinder::base_point)
        .def_readwrite("axis_vector", &Cylinder::axis_vector)
        .def_readwrite("height", &Cylinder::height)
        .def_readwrite("radius", &Cylinder::radius);
}
