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
  return Vec3(c / x_, c / y_, c / z_);
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
  return Vec3(- x_, - y_, - x_);
}