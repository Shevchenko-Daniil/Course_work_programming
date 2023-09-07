#include "vector3D.h"
#include <iostream>
#include <cmath>

Vector3D::Vector3D(double x0,double y0, double z0): x(x0), y(y0), z(z0){}

Vector3D Vector3D::operator+() const{
    return Vector3D{+x, +y, +z};
}

Vector3D Vector3D::operator-() const{
    return Vector3D{-x, -y, -z};
}

Vector3D operator+(const Vector3D& v1, const Vector3D& v2){
    return Vector3D{v1.x + v2.x, v1.y + v2.y, v1.z+ v2.z};
}

Vector3D operator-(const Vector3D& v1, const Vector3D& v2){
    return Vector3D{v1.x - v2.x, v1.y - v2.y, v1.z - v2.z};
}

Vector3D operator*(const Vector3D& v, double n){
    return Vector3D{n*v.x, n*v.y, n*v.z};
}

Vector3D operator*(double n, const Vector3D& v){
    return Vector3D{n*v.x, n*v.y, n*v.z};
}

Vector3D operator/(const Vector3D& v, double n){
	return Vector3D{v.x/n, v.y/n, v.z/n};
}

double scalprod(const Vector3D& v1, const Vector3D& v2){
    return v1.x*v2.x + v1.y*v2.y + v1.z*v2.z;
}

Vector3D crprod(const Vector3D& v1, const Vector3D& v2){
    return Vector3D{v1.y*v2.z - v1.z*v2.y, v1.z*v2.x - v1.x*v2.z, v1.x*v2.y - v1.y*v2.x};
}

Vector3D& Vector3D::operator+=(const Vector3D& v){
    this->x += v.x;
    this->y += v.y;
    this->z += v.z;
    return *this;
}

Vector3D& Vector3D::operator-=(const Vector3D& v){
    this->x -= v.x;
    this->y -= v.y;
    this->z -= v.z;
    return *this;
}

Vector3D& Vector3D::operator*=(double n){
    this->x *= n;
    this->y *= n;
    this->z *= n;
    return *this;
}

bool operator==(const Vector3D& v1, const Vector3D& v2){
    return v1.x == v2.x && v1.y == v2.y && v1.z == v2.z;
}

bool operator!=(const Vector3D& v1, const Vector3D& v2){
    return v1.x != v2.x || v1.y != v2.y || v1.z != v2.z;
}

/*std::ostream& operator<<(std::ostream& os, const Vector3D& v){			//трехмерный
    return os << "{" << v.x << ", " << v.y << "," << v.z << "}";
}*/

/*std::ostream& operator<<(std::ostream& os, const Vector3D& v){			//двумерный
    return os << "{" << v.x << ", " << v.y << "}";
}*/

std::ostream& operator<<(std::ostream& os, const Vector3D& v){       //для графика
    return os << v.x << "	" << v.y ;
}

std::istream& operator>>(std::istream& is, Vector3D& v){
    return is >> v.x >> v.y >> v.z;
}

double Vector3D::length() const{
    return sqrt(x*x+y*y+z*z);
}

double Vector3D::getx() const{
	return x;
}

double Vector3D::gety() const{
	return y;
}

double Vector3D::getz() const{
    return z;
}



