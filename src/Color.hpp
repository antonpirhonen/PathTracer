#ifndef COLOR_HPP
#define COLOR_HPP

#include <tuple>

class Color {
public:
    Color(float r, float g, float b);
    Color(std::tuple<float, float, float> rgb);
  
    std::tuple<float, float, float> GetComponents() const;
    std::tuple<int, int, int> GetComponents255() const;
  
    // Elementwise arithmetic. These operations (+ and * for two colors,
    // dividing by a constant float) are the only ones we really need.
    Color operator + (const Color& c) const;
    Color operator * (const Color& c) const;
    Color operator / (const float c) const;

private:
    float r_, g_, b_;
  

};

#endif
