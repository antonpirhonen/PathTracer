#ifndef VEC3_HPP
#define VEC3_HPP
#include <iostream>

class Vec3 {

public:

    Vec3(float x, float y, float z) : x_(x), y_(y), z_(z) { }
    Vec3() : x_(0), y_(0), z_(0) { }

    Vec3(Vec3& v) {x_ = v.x_; y_ = v.y_; z_ = v.z_;}
    Vec3(const Vec3& v) {x_ = v.x_; y_ = v.y_; z_ = v.z_;}
    Vec3 operator=(Vec3& v) {x_ = v.x_; y_ = v.y_; z_ = v.z_; return *this;}
    Vec3 operator=(const Vec3& v) {x_ = v.x_; y_ = v.y_; z_ = v.z_; return *this;}

    float X() const;
    float Y() const;
    float Z() const;

    void Normalize();

    // For the operators, let's define 3 versions of each so that
    // it supports operations with two Vec3 objects as well as operations
    // with one Vec3 object and a float, in either order.
    // We must declare the last one as a friend (see more:
    // https://stackoverflow.com/questions/4622330/
    // operator-overloading-member-function-vs-non-member-function)
  
    Vec3 operator + (const Vec3& v) const; // Vec3 + Vec3
    Vec3 operator + (float c) const; // Vec3 + float
    friend Vec3 operator + (float c, const Vec3& v); // float + Vec3

    Vec3 operator - (const Vec3& v) const;
    Vec3 operator - (float c) const;
    Vec3 operator - () const;
    friend Vec3 operator - (float c, const Vec3& v);

    Vec3 operator * (const Vec3& v) const;
    Vec3 operator * (float c) const;
    friend Vec3 operator * (float c, const Vec3& v);

    Vec3 operator / (const Vec3& v) const;
    Vec3 operator / (float c) const;
    friend Vec3 operator / (float c, const Vec3& v);

    float DotProduct(Vec3& v);
    Vec3 CrossProduct(Vec3& v);
    float Norm();
    Vec3 Reverse() const;
    bool IsZeroVector();
    friend std::ostream& operator<<(std::ostream& os, Vec3& v);

    Vec3 RotateAroundXAxis(float deg) const;
    Vec3 RotateAroundYAxis(float deg) const;
    Vec3 RotateAroundZAxis(float deg) const;

private:
  
    float x_, y_, z_;
  
};

#endif
