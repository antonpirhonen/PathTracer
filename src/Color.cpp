#include "Color.hpp"

Color::Color(float r, float g, float b) : r_(r), g_(g), b_(b) {
    if (r < 0) r_ = 0;
    if (r > 1) r_ = 1;
    if (g < 0) g_ = 0;
    if (g > 1) g_ = 1;
    if (b < 0) b_ = 0;
    if (b > 1) b_ = 1;
}

Color::Color(std::tuple<float, float, float> rgb) {
    if (std::get<0>(rgb) < 0) r_ = 0;
    if (std::get<0>(rgb) > 1) r_ = 1;
    if (std::get<1>(rgb) < 0) g_ = 0;
    if (std::get<1>(rgb) > 1) g_ = 1;
    if (std::get<2>(rgb) < 0) b_ = 0;
    if (std::get<2>(rgb) > 1) b_ = 1;
}
  
std::tuple<float, float, float> Color::GetComponents() const {
    return std::make_tuple(r_, g_, b_);
}

std::tuple<int, int, int> Color::GetComponents255() const {
    return std::make_tuple(static_cast<int>(r_*255 + 0.5),
			   static_cast<int>(g_*255 + 0.5),
			   static_cast<int>(b_*255 + 0.5));
}

Color Color::operator + (const Color& c) const {
    std::tuple<float, float, float> col = c.GetComponents();
    return Color(r_ + std::get<0>(col),
		 g_ + std::get<1>(col),
		 b_ + std::get<2>(col));
}

Color Color::operator * (const Color& c) const {
    std::tuple<float, float, float> col = c.GetComponents();
    return Color(r_ * std::get<0>(col),
		 g_ * std::get<1>(col),
		 b_ * std::get<2>(col));
}

Color Color::operator / (const float c) const {
    return Color(r_ / c,
		 g_ / c,
		 b_ / c);
}

std::ostream& operator<<(std::ostream& os, Color& c) {
  os << "r: " << c.r_ << ", g: " << c.g_ << ", b: " << c.b_ << std::endl;
  return os;
}
