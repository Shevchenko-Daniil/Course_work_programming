#ifndef VECTOR3D_H_
#define VECTOR3D_H_

#include <iosfwd>

class Vector3D{
	double x,y,z;
public:
    Vector3D(double x = 0, double y = 0,double z = 0);

    Vector3D operator+() const;
    Vector3D operator-() const;

    friend Vector3D operator+(const Vector3D& v1, const Vector3D& v2);
    friend Vector3D operator-(const Vector3D& v1, const Vector3D& v2);
    friend Vector3D operator*(const Vector3D& v, double n);
    friend Vector3D operator*(double n, const Vector3D& v);
    friend Vector3D operator/(const Vector3D& v, double n);
    friend double scalprod(const Vector3D& v1, const Vector3D& v2);   //scalar product
    friend Vector3D crprod(const Vector3D& v1, const Vector3D& v2);   //cross product

    Vector3D& operator+=(const Vector3D& v);
    Vector3D& operator-=(const Vector3D& v);
    Vector3D& operator*=(double n);

    friend bool operator==(const Vector3D& a, const Vector3D& b);
    friend bool operator!=(const Vector3D& a, const Vector3D& b);

    friend std::ostream& operator<<(std::ostream& os, const Vector3D& v);
    friend std::istream& operator>>(std::istream& is, Vector3D& v);

    double length() const;

    double getx() const;
    double gety() const;
    double getz() const;

};




#endif /* VECTOR3D_H_ */
