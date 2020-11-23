#include <array>
#include <vector>
#include <ctime>
#include <fstream>
#include <cstdio>
#include <iostream>
#include "Environment.hpp"
#include "Vec3.hpp"
#include "Ray.hpp"
#include "structs.hpp"
#include "CameraSimple.hpp"
#include "Image.hpp"

void CameraSimple::GetImage(Environment& env, unsigned int spp) {
    Image image(y_reso_, x_reso_);
    std::vector<Body*> bodies = env.GetBodies();

    Vec3 tr_corner = Vec3{br_corner_.X(), br_corner_.Y(), tl_corner_.Z()};
    Vec3 bl_corner = Vec3{tl_corner_.X(), tl_corner_.Y(), br_corner_.Z()};
    size_t n;
    size_t m;

    // Uncomment the next expression to distribute the computation across all available CPU cores
    //#pragma omp parallel for
    for (int i = 0; i < y_reso_; i++) {
    std::cout << "i = " << i << std::endl;
	for (int j = 0; j < x_reso_; j++) {
	    Vec3 ray_dest = tl_corner_ + (float(j)/float(x_reso_))*(tr_corner-tl_corner_) + (float(i)/float(y_reso_))*(bl_corner-tl_corner_);
	    ray_dest.Normalize();
		std::cout << ray_dest.X() << " " << ray_dest.Y() << " " << ray_dest.Z() << std::endl;
	    for (unsigned int sample = 0; sample < spp; sample++) {
		Ray ray = Ray(focal_point_, ray_dest);
		while (!ray.IsFinished()) {
		    float min_distance = 1000000;
		    float temp_distance = 0;
		    Body* closest_body;
		    bool hits_something = false;
	    
		    for (Body* body : bodies) {
			temp_distance = body->FindCollision(ray);
			if (temp_distance > 0 && temp_distance < min_distance) {
			    hits_something = true;
			    min_distance = temp_distance;
			    closest_body = body;
			}
		    }
		    
		    if(hits_something){
			Vec3 reflection_point = ray.GetOrigin() + ray.GetDirection()*min_distance;
			closest_body->Reflect(ray, reflection_point);
		    }
		    else{
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
    image.Draw();
}


