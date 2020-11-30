#include "Vec3.hpp"
#include <cmath>

float Vec3::X() const { return x_; }
float Vec3::Y() const { return y_; }
float Vec3::Z() const { return z_; }

void Vec3::Normalize() {
    float len_inv = 1 / sqrt(x_*x_ + y_*y_ + z_*z_);
    x_ *= len_inv;
    y_ *= len_inv;
    z_ *= len_inv;
}
  
Vec3 Vec3::operator + (const Vec3& v) const {
    return Vec3(x_ + v.X(), y_ + v.Y(), z_ + v.Z());
}
Vec3 Vec3::operator + (float c) const {
    return Vec3(c + x_, c + y_, c + z_);
}
Vec3 operator + (float c, const Vec3& v) {
    return Vec3(c + v.X(), c + v.Y(), c + v.Z());
}

Vec3 Vec3::operator - (const Vec3& v) const {
    return Vec3(x_ - v.X(), y_ - v.Y(), z_ - v.Z());
}
Vec3 Vec3::operator - (float c) const {
    return Vec3(c - x_, c - y_, c - z_);
}
Vec3 operator - (float c, const Vec3& v) {
    return Vec3(c - v.X(), c - v.Y(), c - v.Z());
}

Vec3 Vec3::operator * (const Vec3& v) const {
    return Vec3(x_ * v.X(), y_ * v.Y(), z_ * v.Z());
}
Vec3 Vec3::operator * (float c) const {
    return Vec3(c * x_, c * y_, c * z_);
}
Vec3 operator * (float c, const Vec3& v) {
    return Vec3(c * v.X(), c * v.Y(), c * v.Z());
}

Vec3 Vec3::operator / (const Vec3& v) const {
    return Vec3(x_ / v.X(), y_ / v.Y(), z_ / v.Z());
}
Vec3 Vec3::operator / (float c) const {
    return Vec3(x_ / c, y_ / c, z_ / c);
}
Vec3 operator / (float c, const Vec3& v) {
    return Vec3(c / v.X(), c / v.Y(), c / v.Z());
}
float Vec3::DotProduct(Vec3& v) {
    return x_*v.X() + y_*v.Y() + z_*v.Z();
}
Vec3 Vec3::CrossProduct(Vec3& v) {
    return Vec3(y_*v.Z() - z_*v.Y(), z_*v.X() - x_*v.Z(), x_*v.Y() - y_*v.X());
}
float Vec3::Norm() {
    return sqrt(x_*x_ + y_*y_ + z_*z_);
}
Vec3 Vec3::Reverse() const {
    return Vec3(- x_, - y_, - z_);
}

bool Vec3::IsZeroVector() {
    return x_ == 0 && y_ == 0 && z_ == 0;
}

std::ostream& operator<<(std::ostream& os, Vec3& v) {
    os << "x: " << v.x_ << ", y: " << v.y_ << ", z: " << v.z_ << std::endl;
    return os;
}

Vec3 Vec3::RotateAroundXAxis(float deg) const {
    float t = deg * 2 * M_PI / 360;
    float r[] = { 1, 0,                          0,
		  0, static_cast<float>(cos(t)), static_cast<float>(-sin(t)),
		  0, static_cast<float>(sin(t)), static_cast<float>(cos(t)) };
    return Vec3(r[0]*x_ + r[1]*y_ + r[2]*z_,
		r[3]*x_ + r[4]*y_ + r[5]*z_,
		r[6]*x_ + r[7]*y_ + r[8]*z_);
}

Vec3 Vec3::RotateAroundYAxis(float deg) const {
    float t = deg * 2 * M_PI / 360;
    float r[] = { static_cast<float>(cos(t)),  0, static_cast<float>(sin(t)),
		  0,                           1, 0,
		  static_cast<float>(-sin(t)), 0, static_cast<float>(cos(t)) };
    return Vec3(r[0]*x_ + r[1]*y_ + r[2]*z_,
		r[3]*x_ + r[4]*y_ + r[5]*z_,
		r[6]*x_ + r[7]*y_ + r[8]*z_);
}

Vec3 Vec3::RotateAroundZAxis(float deg) const {
    float t = deg * 2 * M_PI / 360;
    float r[] = { static_cast<float>(cos(t)), static_cast<float>(-sin(t)), 0,
		  static_cast<float>(sin(t)), static_cast<float>(cos(t)),  0,
		  0,                          0,                           1 };

    return Vec3(r[0]*x_ + r[1]*y_ + r[2]*z_,
		r[3]*x_ + r[4]*y_ + r[5]*z_,
		r[6]*x_ + r[7]*y_ + r[8]*z_);
}
