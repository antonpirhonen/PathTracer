#ifndef COLOR_HPP
#define COLOR_HPP

#include <tuple>
#include <iostream>

class Color {
public:
    Color(float r, float g, float b);
    Color(std::tuple<float, float, float> rgb);

    Color(Color& c) {
        r_ = c.r_;
        g_ = c.g_;
        b_ = c.b_;
    }

    Color& operator=(Color& c) {
        r_ = c.r_;
        g_ = c.g_;
        b_ = c.b_;
        return *this;
    }
    
    Color(const Color& c) {
        r_ = c.r_;
        g_ = c.g_;
        b_ = c.b_;
    }

    Color& operator=(const Color& c) {
        r_ = c.r_;
        g_ = c.g_;
        b_ = c.b_;
        return *this;
    }
  
    std::tuple<float, float, float> GetComponents() const;
    std::tuple<int, int, int> GetComponents255() const;
  
    // Elementwise arithmetic. These operations (+ and * for two colors,
    // dividing by a constant float) are the only ones we really need.
    Color operator + (const Color& c) const;
    Color operator * (const Color& c) const;
    Color operator / (const float c) const;
    friend std::ostream& operator<<(std::ostream& os, Color& c);

private:
    float r_, g_, b_;
  

};

#endif
