#include "Color.hpp"

Color::Color(float r, float g, float b) : r_(r), g_(g), b_(b) {
  if (r < 0 || r > 1 || g < 0 || g > 1 || b < 0 || b > 1) {
    throw std::invalid_argument("Values given to the constructor of class"
				" Color were not between 0 and 1");
  }
  r_ = r;
  g_ = g;
  b_ = b;
}

Color::Color(std::tuple<float, float, float> rgb) {
  if (std::get<0>(rgb) < 0 || std::get<0>(rgb) > 1 ||
      std::get<1>(rgb) < 0 || std::get<1>(rgb) > 1 ||
      std::get<2>(rgb) < 0 || std::get<2>(rgb) > 1) {
    throw std::invalid_argument("Values given to the constructor of class"
				" Color were not between 0 and 1");
  }
  r_ = std::get<0>(rgb);
  g_ = std::get<0>(rgb);
  b_ = std::get<0>(rgb);
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
