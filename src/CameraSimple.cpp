#include <array>
#include <vector>
#include <ctime>
#include <fstream>
#include <cstdio>
#include <iostream>
#include <iterator>
#include "Environment.hpp"
#include "Vec3.hpp"
#include "Ray.hpp"
#include "structs.hpp"
#include "CameraSimple.hpp"
#include "Image.hpp"

void CameraSimple::GetImage(Environment& env, unsigned int spp) {
    Image image(y_reso_, x_reso_);
    std::vector<Triangle> bodies = env.GetBodies();

    Vec3 tr_corner = Vec3{br_corner_.X(), br_corner_.Y(), tl_corner_.Z()};
    Vec3 bl_corner = Vec3{tl_corner_.X(), tl_corner_.Y(), br_corner_.Z()};
    size_t n;
    size_t m;

    // Uncomment the next expression to distribute the computation across all available CPU cores
    #pragma omp parallel for
    for (int i = 0; i < y_reso_; i++) {
	for (int j = 0; j < x_reso_; j++) {
	    Vec3 ray_dest = tl_corner_ + (float(j)/float(x_reso_))*(tr_corner-tl_corner_) + (float(i)/float(y_reso_))*(bl_corner-tl_corner_);
	    ray_dest.Normalize();
	    for (unsigned int sample = 0; sample < spp; sample++) {
		Ray ray = Ray(focal_point_, ray_dest);
        //std::cout << i << std::endl;
        while (!ray.IsFinished()) {
            std::tuple<float, float, float> min_distance = std::make_tuple(1000000, -1, -1);
            std::tuple<float, float, float> temp_distance = std::make_tuple(0,0,0);
            std::vector<Triangle>::iterator closest_body;
            bool hits_something = false;

            for (auto it = bodies.begin(); it != bodies.end(); it++) {
                auto body = *it;
                temp_distance = body.FindCollision(ray);
                if (std::get<0>(temp_distance) > 0 && std::get<0>(temp_distance) < std::get<0>(min_distance)) {
                    hits_something = true;
                    min_distance = temp_distance;
                    closest_body = it;
                }
            }

            if (hits_something) {
                Vec3 reflection_point = ray.GetOrigin() + ray.GetDirection()*std::get<0>(min_distance);
                auto tr = *closest_body;
                tr.Reflect(ray, reflection_point, std::get<1>(min_distance), std::get<2>(min_distance));
            }
		    else {
                ray.SetFinished();
                ray.SetNewColor(Color(0,0,0));
		    }
		}
		Color addition = ray.GetColor() / spp;
		// We need to catch for exceptions since rounding errors might produce
		// values larger than 1 for the color components.
		// TODO: Come up with a cleaner approach to this. Now we just don't add if it would overflow.
		Color new_c(0,0,0);
		Color* ptr_c = image.GetPtrToPixel(i,j);
		try {
		    new_c = *ptr_c + addition;
		}
		catch (const std::invalid_argument& ia) {
		    new_c = *ptr_c;
		}
		*ptr_c = new_c;
	    } // sample
	} // j
    } // i

	image.DrawPng();
}


