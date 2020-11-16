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
#include "Camera.hpp"
/*
void Camera::GetImage(Environment& env) {
    const size_t n_rays = x_reso_*y_reso_;
    Ray* rays[n_rays];
    std::vector<Body*> bodies = env.GetBodies();

    for (Ray* ray : rays) {
        const Path& original_path = Path{path_.location_, path_.direction_};
        ray->SetNewPath(original_path);
        while (!ray->IsFinished()) {
            float min_distance = 1000000;
            float temp_distance;
            Body* closest_body;
            bool hits_something = false;
            for (Body* body : bodies) {
                temp_distance = body->FindCollision(*ray);
                if (temp_distance < min_distance) {
                    hits_something = true;
                    min_distance = temp_distance;
                    closest_body = body;
                }
            }
            if(!hits_something){
                ray->SetFinished();
            }
            ray->SetFinished();
            Vec3 reflection_point = ray->GetPath().location_+ray->GetPath().direction_*min_distance;
            closest_body->Reflect(*ray, reflection_point);        }
    }

    std::ofstream ofs(Camera::Time()+".ppm", std::ios_base::out | std::ios_base::binary);
    ofs << "P6" << std::endl << x_reso_ << ' ' << y_reso_ << std::endl << "255" << std::endl;
    for (auto i = 0; i < y_reso_; ++i) {
        for (auto j = 0; j < x_reso_; ++j) { 
            ofs << (char) (i % 256); 
            ofs << (char) (j % 256); 
            ofs << (char) ((i * j) % 256);       // red, green, blue
        }
    }
    ofs.close();
}

//returns current time as string in format YY_MM_DD-HH_MM_SS 

std::string Camera::Time() {
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
}*/