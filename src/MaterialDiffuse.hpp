#include "structs.hpp"
#include "Material.hpp"

class MaterialDiffuse : public Material {
public:
    MaterialDiffuse(bool luminous = false, RGB_color color = RGB_color{0,0,0}, Color_removal color_rem = Color_removal{1,1,1}, float mattness = 1) :
    Material(luminous, color, color_rem), mattness_(mattness)  { };

    Vec3 Reflect(Vec3 original_direction, Vec3 unit_normal);
    
private:
    float mattness_;
};