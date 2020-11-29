#include "Image.hpp"
#include <ostream>
#include <fstream>

#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.hpp"


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

void Image::DrawPpm() const {
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

void Image::DrawPng() const {

    auto name = Time() + ".png";

    uint8_t* pixels = new uint8_t[width_ * height_ * 3];

    auto index = 0;

    for (size_t i = 0; i < colors_.size(); i++) {
        std::tuple<int, int, int> rgb = colors_[i].GetComponents255();
        pixels[index++] = static_cast<unsigned char>(std::get<0>(rgb));
        pixels[index++] = static_cast<unsigned char>(std::get<1>(rgb));
        pixels[index++] = static_cast<unsigned char>(std::get<2>(rgb));
    }

    stbi_write_png(name.c_str(), width_, height_, 3, pixels, width_  * 3);

    delete[] pixels;

}

void Image::Normalize() {
    float maxi = 0; // maximal color component intensity
    for (const auto &c : colors_) {
	std::tuple<float, float, float> components = c.GetComponents();
	float r = std::get<0>(components);
	float g = std::get<1>(components);
	float b = std::get<2>(components);
	maxi = (maxi > r) ? maxi : r;
	maxi = (maxi > g) ? maxi : r;
	maxi = (maxi > b) ? maxi : r;
    }
    for (auto &c : colors_) {
	c = c / maxi;
    }
}
