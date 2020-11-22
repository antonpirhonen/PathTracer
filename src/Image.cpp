#include "Image.hpp"
#include <ostream>
#include <fstream>

Color* Image::GetPtrToPixel(int i, int j) {
    return &colors_[i*width_ + j];
}

// Helper for Image::Draw(): returns current time as string in format
// YY_MM_DD-HH_MM_SS
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

void Image::Draw() const {
    std::ofstream ofs(Time()+".ppm", std::ios_base::out | std::ios_base::binary);
    ofs << "P6" << std::endl << width_ << " " << height_ << std::endl
	<< "255" << std::endl;
    for (size_t i = 0; i < colors_.size(); i++) {
        std::tuple<int, int, int> rgb = colors_[i].GetComponents255();
        ofs << static_cast<unsigned char>(std::get<0>(rgb));
        ofs << static_cast<unsigned char>(std::get<1>(rgb));
        ofs << static_cast<unsigned char>(std::get<2>(rgb));
    }
    ofs.close();
}
