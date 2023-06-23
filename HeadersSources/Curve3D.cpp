#include "Curve3D.h"

namespace crv {

    //*************************ќкружность*********************
    template <typename myType>
    Circle<myType>::Circle(myType myRadius) {
        if (myRadius < 0) {
            throw std::invalid_argument("Radius must be positive.");
        }
        radius = myRadius;
    }

    template <typename myType>
    myType Circle<myType>::GetRadius() {
        return radius;
    }

    template <typename myType>
    Point3D<myType> Circle<myType>::GetPoint(myType t) const {
        myType x = radius * cos(t);
        myType y = radius * sin(t);
        myType z = 0.0;
        return Point3D<myType>(x, y, z);
    }

    template <typename myType>
    Point3D<myType> Circle<myType>::GetDerivative(myType t) const {
        myType dx = -radius * sin(t);
        myType dy = radius * cos(t);
        myType dz = 0.0;
        return Point3D<myType>(dx, dy, dz);
    }

    template class Circle<float>;
    template class Circle<double>;

    //*************************Ёллипс*********************

    template <typename myType>
    Ellipse<myType>::Ellipse(myType myRadiusX, myType myRadiusY) {
        if (myRadiusX < 0 || myRadiusY < 0) {
            throw std::invalid_argument("Radii must be positive.");
        }

        radiusX = myRadiusX;
        radiusY = myRadiusY;
    }

    template <typename myType>
    myType Ellipse<myType>::GetRadiusX() {
        return radiusX;
    }

    template <typename myType>
    myType Ellipse<myType>::GetRadiusY() {
        return radiusY;
    }

    template <typename myType>
    Point3D<myType> Ellipse<myType>::GetPoint(myType t) const {
        t = atan(tan(t) * radiusX / radiusY);
        myType x = radiusX * cos(t);
        myType y = radiusY * sin(t);
        myType z = 0.0;
        return Point3D<myType>(x, y, z);
    }

    template <typename myType>
    Point3D<myType> Ellipse<myType>::GetDerivative(myType t) const {
        t = atan(tan(t) * radiusX / radiusY);
        myType dx = -radiusX * sin(t);
        myType dy = radiusY * cos(t);
        myType dz = 0.0;
        return Point3D<myType>(dx, dy, dz);
    }

    template class Ellipse<float>;
    template class Ellipse<double>;

    //*************************—пираль*********************

    template <typename myType>
    Helix<myType>::Helix(myType myRadius, myType myStep) {
        if (myRadius < 0 || myStep < 0) {
            throw std::invalid_argument("Radius and step must be positive.");
        }

        radius = myRadius;
        step = myStep / myType((2.0 * Curve3D<myType>::PI));
    }

    template <typename myType>
    myType Helix<myType>::GetRadius() {
        return radius;
    }

    template <typename myType>
    myType Helix<myType>::GetStep() {
        return step;
    }

    template <typename myType>
    Point3D<myType> Helix<myType>::GetPoint(myType t) const {
        myType x = radius * cos(t);
        myType y = radius * sin(t);
        myType z = step * t;
        return Point3D<myType>(x, y, z);
    }

    template <typename myType>
    Point3D<myType> Helix<myType>::GetDerivative(myType t) const {
        myType dx = -radius * sin(t);
        myType dy = radius * cos(t);
        myType dz = step;
        return Point3D<myType>(dx, dy, dz);
    }

    template class Helix<float>;
    template class Helix<double>;
}
