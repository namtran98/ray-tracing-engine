#include "Vector3D.hpp"
#include "Point3D.hpp"

Vector3D::Vector3D() 
    : x(0), y(0), z(0) {
}

Vector3D::Vector3D(double c) 
    : x(c), y(c), z(c) {
}

Vector3D::Vector3D(double _x, double _y, double _z)
    : x(_x), y(_y), z(_z) {
}

Vector3D::Vector3D(const Point3D& p) 
    : x(p.x), y(p.y), z(p.z) {
}

Vector3D::Vector3D(const Vector3D& v) {
    x = v.x;
    y = v.y;
    z = v.z;
}

Vector3D::~Vector3D() {

}

Vector3D& Vector3D::operator= (const Vector3D& rhs) {
    this -> x == rhs.x;
    this -> y == rhs.y;
    this -> z == rhs.z;
    return *this;
}

Vector3D& Vector3D::operator=(const Point3D& rhs) {

}

Vector3D Vector3D::operator-() const {

}

Vector3D Vector3D::operator+(const Vector3D& v) const {

}

Vector3D& Vector3D::operator+=(const Vector3D& v) {

}

Vector3D Vector3D::operator-(const Vector3D& v) const {

}

Vector3D Vector3D::operator*(const double a) const {

}

Vector3D Vector3D::operator/(const double a) const {

}

void Vector3D::normalize() {

}

double Vector3D::length() {

}

double Vector3D::len_squared() {

}

double Vector3D::operator* (const Vector3D& b) const {

}

Vector3D Vector3D::operator^ (const Vector3D& v) const {

}

Vector3D operator* (const double a, const Vector3D& v) {

}
