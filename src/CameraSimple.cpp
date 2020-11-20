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

//returns current time as string in format YY_MM_DD-HH_MM_SS 
static std::string Time() {
    time_t now = time(0);
    tm *ltm = localtime(&now);

    std::string ret;
    ret += std::to_string(ltm->tm_year-100) + "_";
    ret += std::to_string(ltm->tm_mon) + "_";
    ret += std::to_string(ltm->tm_mday) + "-";
    ret += std::to_string(ltm->tm_hour) + "_";
    ret += std::to_string(ltm->tm_min) + "_";
    ret += std::to_string(ltm->tm_sec);
    
    return ret;
}

void CameraSimple::GetImage(Environment& env, unsigned int spp) {
    const size_t n_rays = x_reso_*y_reso_;
    std::vector<Color> colors(n_rays, Color(0,0,0));
    std::vector<Body*> bodies = env.GetBodies();

    Vec3 tr_corner = Vec3{br_corner_.X(), br_corner_.Y(), tl_corner_.Z()};
    Vec3 bl_corner = Vec3{tl_corner_.X(), tl_corner_.Y(), br_corner_.Z()};
    size_t n;
    size_t m;

    // Uncomment the next expression to distribute the computation across all available CPU cores
    //#pragma omp parallel for
    for (size_t i = 0; i < n_rays; i++){
        n = i%x_reso_;
        m = i/y_reso_;
        Vec3 ray_dest = tl_corner_ + (float(n)/float(x_reso_))*(tr_corner-tl_corner_) + (float(m)/float(y_reso_))*(bl_corner-tl_corner_);
        ray_dest.Normalize();
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
	    try {
		new_c = colors[i] + addition;
	    }
	    catch (const std::invalid_argument& ia) {
		new_c = colors[i];
	    }
	    colors[i] = new_c;
	} // sample
    } // i

    std::ofstream ofs(Time()+".ppm", std::ios_base::out | std::ios_base::binary);
    ofs << "P6" << std::endl << x_reso_ << ' ' << y_reso_ << std::endl << "255" << std::endl;    
    for (size_t i = 0; i < n_rays; i++) {
        Color color = colors[i];
	std::tuple<int, int, int> rgb = color.GetComponents255();
        ofs << static_cast<unsigned char>(std::get<0>(rgb)); 
        ofs << static_cast<unsigned char>(std::get<1>(rgb)); 
        ofs << static_cast<unsigned char>(std::get<2>(rgb));
    }
    ofs.close();
}


