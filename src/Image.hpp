#ifndef IMAGE_HPP
#define IMAGE_HPP

#include "Color.hpp"
#include <vector>

class Image {

public:
    Image(int height, int width) : height_(height), width_(width), colors_(height*width, Color(0,0,0)) { }
    Color* GetPtrToPixel(int i, int j);
    void DrawPpm() const;
    void DrawPng() const;
    
private:
    std::vector<Color> colors_;
    int height_;
    int width_;

};


#endif
