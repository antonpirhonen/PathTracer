#include "Camera.hpp"

static void print_progress(int percentage) {
    int barlength = 20;
    int numdone = barlength * (static_cast<float>(percentage) / 100);
    std::cout << "\r[";
    for (int i = 0; i < barlength; i++) {
	if (i < numdone)
	    std::cout << "=";
	else
	    std::cout << " ";		
    }
    std::cout << "] " << percentage << "%" << std::flush;
}

void Camera::GetImage(Environment& env, unsigned int spp) {
    Image image(y_reso_, x_reso_);
    std::vector<Triangle> bodies = env.GetBodies();

    Vec3 dir = direction_;
    dir.Normalize();
	Vec3 orig = origin_;
	Vec3 x_unit = Vec3(1,0,0);
	Vec3 y_unit = Vec3(0,1,0);
	Vec3 z_unit = Vec3(0,0,1);	
	Vec3 image_x;
	Vec3 image_y;

	if ((dir.DotProduct(x_unit) == 0) && (dir.DotProduct(y_unit) == 0)){
 		image_x = Vec3(1 + (dir.Z() > 0)*(-2),0,0);
		image_y = Vec3(0,1,0);
	} else {
		Vec3 image_x_dir = z_unit.CrossProduct(dir);
		image_x = tan(x_angle_/180*M_PI/2) / image_x_dir.Norm() * image_x_dir;
		Vec3 image_y_dir = dir.CrossProduct(image_x_dir);
		image_y = tan(y_angle_/180*M_PI/2) / image_y_dir.Norm() * image_y_dir;
	}

	Vec3 tl_corner = dir - image_x + image_y;
	Vec3 tr_corner = dir + image_x + image_y;
	Vec3 bl_corner = dir - image_x - image_y;
    Vec3 br_corner = dir + image_x - image_y;

    float pixels_total = static_cast<float>(x_reso_*y_reso_); // float, since this is used in division later
    int pixels_done = 0;
    int last_ten = 0;

    std::cout << "Rendering image using " << omp_get_max_threads() << " CPU threads." << std::endl;
    #pragma omp parallel for schedule(static,1)
    for (int i = 0; i < y_reso_; i++) {
	for (int j = 0; j < x_reso_; j++) {
	    Vec3 ray_dir = tl_corner + (float(j)/float(x_reso_))*(tr_corner-tl_corner) + (float(i)/float(y_reso_))*(bl_corner-tl_corner);
        ray_dir.Normalize();
	    for (unsigned int sample = 0; sample < spp; sample++) {
		Ray ray = Ray(origin_, ray_dir);
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
		Color* ptr_c = image.GetPtrToPixel(i,j);
		*ptr_c = *ptr_c + addition;
	    } // sample
	    
	    // Calculate progress:
	    	    
#pragma omp atomic
	    (pixels_done++);
	    
	    if (omp_get_thread_num() == 0) {
		if ((pixels_done / pixels_total) * 10 >= last_ten) {
		    print_progress(last_ten*10);
		    last_ten++;
		}
	    }
	    
	} // j
    } // i
    print_progress(100);
    std::cout << std::endl << "Rendering done, now drawing image." << std::endl;
    image.Normalize();
    image.DrawPng();
}


