#include "color.hpp"
#include <iostream>

Color::Color(int r, int g, int b): red_(r), green_(g), blue_(b) { //initizilaztion list
  const int kZero = 0;
  const int kTwoFiftyFive = 255;

  if (r < kZero|| r > kTwoFiftyFive || g < kZero || g > kTwoFiftyFive || b < kZero || b > kTwoFiftyFive) {
    throw std::runtime_error("bad color");
  }
}


// do not modify
bool operator==(const Color& rhs, const Color& lhs) {
  return (rhs.Red() == lhs.Red() && rhs.Green() == lhs.Green() &&
          rhs.Blue() == lhs.Blue());
}