#include <array>
#include <iostream>

#include "Environment.hpp"
#include "Vec3.hpp"
#include "Ray.hpp"
#include "structs.hpp"

//a Camera is created with a defined resolution, can't be changed
//is now constructed e.g. Camera<10000>(direction, x_reso, y_reso, x_angle, y_angle)
//This is not robust, must be addressed in main function.
template < int N_RAYS > 
class Camera{
public:
    Camera(Path& direction, size_t x_reso, size_t y_reso, float x_angle, float y_angle)
    : direction_(direction), x_reso_(x_reso), y_reso_(y_reso), x_angle_(x_angle), y_angle_(y_angle) {
        rays_& = Ray& rays_ [N_RAYS];
    }

    void GetImage(&Environment env);
    
    void SetAngles(float x, float y);
    void SetDirection(&Path);

    std::ostream PrintInfo(std::ostream os);

private:
    std::array<Ray&, N_RAYS>& rays_;

    Path& direction_;
    size_t x_reso_;
    size_t y_reso_; 
    float x_angle_;
    float y_angle_;
};

