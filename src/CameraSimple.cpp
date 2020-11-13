#include <array>
#include <vector>
#include <iostream>
#include <ctime>
#include <fstream>
#include <cstdio>

#include "Environment.hpp"
#include "Vec3.hpp"
#include "Ray.hpp"
#include "structs.hpp"
#include "CameraSimple.hpp"


void CameraSimple::GetImage(Environment& env) {
    const size_t n_rays = x_reso_*y_reso_;
    std::vector<Ray> rays;
//    std::vector<RGB_color> colors;

    std::vector<Body*> bodies = env.GetBodies();
    Vec3 tr_corner = Vec3{br_corner_.X(), br_corner_.Y(), tl_corner_.Z()};
    Vec3 bl_corner = Vec3{tl_corner_.X(), tl_corner_.Y(), br_corner_.Z()};
    size_t i = 0;
    std::cout << "size = " << rays.size() << std::endl;
    size_t n;
    size_t m;
    Vec3 new_direction;

    for (size_t i = 0; i < n_rays; i++){
        n = i%x_reso_;
        m = i/y_reso_;
 //       std::cout << "\nn = " << n << " m = " << m << std::endl;
        Vec3 ray_dest = tl_corner_ + (float(n)/float(x_reso_))*(tr_corner-tl_corner_) + (float(m)/float(y_reso_))*(bl_corner-tl_corner_);
        ray_dest.Normalize();
//        std::cout << "Path origin = " << focal_point_.X() << " " << focal_point_.Y() << " " << focal_point_.Z() << " " << std::endl; 
//        std::cout << "Path direction = " << new_direction.X() << " " << new_direction.Y() << " " << new_direction.Z() << std::endl; 
        Ray ray = Ray{focal_point_, ray_dest};
//        std::cout << "Path origin = " << ray.GetOrigin().X() << " " << ray.GetOrigin().Y() << " " << ray.GetOrigin().Z() << " " << std::endl; 
//        std::cout << "Path direction = " << ray.GetDirection().X() << " " << ray.GetDirection().Y() << " " << ray.GetDirection().Z() << std::endl; 
//        std::cout << "i = " << i << std::endl;
        while (!ray.IsFinished()) {
            float min_distance = 1000000;
            float temp_distance = 0;
            Body* closest_body;
            bool hits_something = false;
            for (Body* body : bodies) {
                temp_distance = body->FindCollision(ray);
//                std::cout << "t_dist                                         = " << temp_distance << std::endl;
                if (temp_distance > 0 && temp_distance < min_distance) {
                    hits_something = true;
                    min_distance = temp_distance;
                    closest_body = body;
                }
            }
//            std::cout << "GC testi " << ray->GetColor().blue_ << std::endl;
            if(!hits_something){
//                RGB_color* color = new RGB_color{100,0,0};
//                colors.push_back(*color);
                ray.SetFinished();
            }
            else{
                Vec3 reflection_point = ray.GetOrigin() + ray.GetDirection()*min_distance;
//                RGB_color* color = new RGB_color{0,0,200};
                closest_body->Reflect(ray, reflection_point);
                RGB_color new_color = closest_body->GetMaterial().GetColor();
                ray.SetNewColor(new_color);
//                std::cout << "uusi ";
//                std::cout << "red " << ray.GetColor().red_;   
//                std::cout << " blue " << ray.GetColor().blue_;
//                std::cout << " green " << ray.GetColor().green_ <<  std::endl;
//                color = &new_color;
//                colors.push_back(*color);
                }
//            std::cout << "Origin = " << ray.GetOrigin().X() << " " << ray.GetOrigin().Y() << " " << ray.GetOrigin().Z() << " " << std::endl; 
//            std::cout << "Direction = " << ray.GetDirection().X() << " " << ray.GetDirection().Y() << " " << ray.GetDirection().Z() << std::endl; 
            }
//        std::cout << "######### End of reflections "<< min_distance << std::endl;
        rays.push_back(ray);
    }

    std::ofstream ofs(CameraSimple::Time()+".ppm", std::ios_base::out | std::ios_base::binary);
    ofs << "P6" << std::endl << x_reso_ << ' ' << y_reso_ << std::endl << "255" << std::endl;
    /*
    for (auto i = 0; i < y_reso_; ++i) {
        for (auto j = 0; j < x_reso_; ++j) { 
            ofs << (char) (i % 256); 
            ofs << (char) (j % 256); 
            ofs << (char) ((i * j) % 256);       // red, green, blue
        }
    }
    */
    
    for (size_t i = 0; i < n_rays; i++){
        Ray ray = rays[i];
    //    std::cout << "i = " << i << std::endl;
        ofs << (char) (ray.GetColor().red_); 
        ofs << (char) (ray.GetColor().green_); 
        ofs << (char) (ray.GetColor().blue_);
    }
    ofs.close();
    
    /*
    for (size_t i = 0; i < n_rays; i++){
//        std::cout << "size = " << colors.size() << std::endl;
        RGB_color color = colors[i];
        std::cout << color.red_ << " " << color.green_ << " " << color.blue_ << " " << std::endl;
        ofs << (char) (color.red_); 
        ofs << (char) (color.green_); 
        ofs << (char) (color.blue_);
    }
    ofs.close();
    */
}

//returns current time as string in format YY_MM_DD-HH_MM_SS 

std::string CameraSimple::Time() {
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