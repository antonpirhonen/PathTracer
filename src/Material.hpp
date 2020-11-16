#include "structs.hpp"
class Material {

public:
  Material(bool luminous = false, RGB_color color = RGB_color{0,0,0}, Color_removal color_rem = Color_removal{1,1,1} ) :
    luminous_(luminous), color_(color) , color_rem_(color_rem) { };

  bool GetLuminosity() const { return luminous_; };

  RGB_color GetColor() const { return color_; };

  const Color_removal GetColorRem() const { return color_rem_; };

  virtual Vec3 Reflect(Vec3) = 0;
protected:
  const bool luminous_;
  const RGB_color color_;
  const Color_removal color_rem_;
};
