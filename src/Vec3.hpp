class Vec3 {

public:

  Vec3(float x, float y, float z) : x_(x), y_(y), z_(z) { }

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
  friend Vec3 operator - (float c, const Vec3& v);

  Vec3 operator * (const Vec3& v) const;
  Vec3 operator * (float c) const;
  friend Vec3 operator * (float c, const Vec3& v);

  Vec3 operator / (const Vec3& v) const;
  Vec3 operator / (float c) const;
  friend Vec3 operator / (float c, const Vec3& v);

  float DotProduct(Vec3& v);
  Vec3 CrossProduct(Vec3& v);
  
private:
  
    float x_, y_, z_;
  
};
