#include <cmath>


struct Vec3 {

    double x_, y_, z_;

    Vec3(double x, double y, double z) : x_(x), y_(y), z_(z) { }

    Vec3 operator + (const Vec3& vector) const { return Vec3(x_ + vector.x_, y_ + vector.y_, z_ + vector.z_); }
    Vec3 operator - (const Vec3& vector) const { return Vec3(x_ - vector.x_, y_ - vector.y_, z_ - vector.z_); }
    Vec3 operator * (double constant) const { return Vec3(constant * x_, constant * y_, constant * z_); }
    Vec3 operator / (double constant) const { return Vec3(x_ / constant, y_ / constant, z_ / constant); }

    Vec3 normalize() const {
        double VectorLength = sqrt(x_ * x_ + y_ * y_ + z_ * z_);
        return Vec3(x_ / VectorLength, y_ / VectorLength, z_ / VectorLength);
    }

    double dot_product(const Vec3& vector) {
        return (x_ * vector.x_ + y_ * vector.y_ + z_ * vector.z_);
    }

    Vec3 cross_product(const Vec3& vector) {
        return Vec3(y_ * vector.z_ - z_ * vector.y_, z_ * vector.x_ - x_ * vector.z_, x_ * vector.y_ - y_ * vector.x_);
    }

};

