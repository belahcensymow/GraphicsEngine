#include "Shared.h"
#include <vector>

std::vector<float> SRT(std::array<float, 3> scale, std::array<float, 3> rotation, std::array<float, 3> translation);


std::vector<float> scale (std::array<float, 3> Scale);
std::vector<float> scaleX(float scale);
std::vector<float> scaleY(float scale);
std::vector<float> scaleZ(float scale);
std::vector<float> rotate (std::array<float, 3> rotation);
std::vector<float> rotateX(float rotation);
std::vector<float> rotateY(float rotation);
std::vector<float> rotateZ(float rotation);
std::vector<float> translate (std::array<float, 3> translation);
std::vector<float> translateX(float translation);
std::vector<float> translateY(float translation);
std::vector<float> translateZ(float translation);
