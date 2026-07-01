#include "Mathematics.h"
#include "math.h"
#include <array>
#include <cmath>
#include <vector>

std::vector<float> SRT(std::array<float, 3> scale, std::array<float, 3> rotation, std::array<float, 3> translation)
{
    std::vector<float> m(16);
    float radX = rotation[0] * 3.1415927 / 180;
    float radY = rotation[1] * 3.1415927 / 180;
    float radZ = rotation[2] * 3.1415927 / 180;
    float cx = std::cos(radX*0.5);
    float cy = std::cos(radY*0.5);
    float cz = std::cos(radZ*0.5);
    float sx = std::sin(radX*0.5);
    float sy = std::sin(radY*0.5);
    float sz = std::sin(radZ*0.5);
    float w = cx*cy*cz + sx*sy*sz;
    float x = sx*cy*cz - cx*sy*sz;
    float y = cx*sy*cz + sx*cy*sz;
    float z = cx*cy*sz - sx*sy*cz;
    m[0]  = (1.0f - 2.0f * (y * y + z * z)) * scale[0];
    m[1]  = (2.0f * (x * y + w * z)) * scale[0];
    m[2]  = (2.0f * (x * z - w * y)) * scale[0];
    m[3]  = 0.0f;
    m[4]  = (2.0f * (x * y - w * z)) * scale[1];
    m[5]  = (1.0f - 2.0f * (x * x + z * z)) * scale[1];
    m[6]  = (2.0f * (y * z + w * x)) * scale[1];
    m[7]  = 0.0f;
    m[8]  = (2.0f * (x * z + w * y)) * scale[2];
    m[9]  = (2.0f * (y * z - w * x)) * scale[2];
    m[10] = (1.0f - 2.0f * (x * x + y * y)) * scale[2];
    m[11] = 0.0f;
    m[12] = translation[0];
    m[13] = translation[1];
    m[14] = translation[2];
    m[15] = 1.0f;
    return m;
}
std::vector<float> scale (std::array<float, 3> Scale) { return SRT(Scale, {0,0,0}, {0,0,0}); }
std::vector<float> scaleX(float scale) { return SRT({scale,1,1}, {0,0,0}, {0,0,0}); }
std::vector<float> scaleY(float scale) { return SRT({1,scale,1}, {0,0,0}, {0,0,0}); }
std::vector<float> scaleZ(float scale) { return SRT({1,1,scale}, {0,0,0}, {0,0,0}); }
std::vector<float> rotate (std::array<float, 3> rotation) { return SRT({1,1,1}, rotation, {0,0,0}); }
std::vector<float> rotateX(float rotation) { return SRT({1,1,1}, {rotation,0,0}, {0,0,0}); }
std::vector<float> rotateY(float rotation) { return SRT({1,1,1}, {0,rotation,0}, {0,0,0}); }
std::vector<float> rotateZ(float rotation) { return SRT({1,1,1}, {0,0,rotation}, {0,0,0}); }
std::vector<float> translate (std::array<float, 3> translation) { return SRT({1,1,1}, {0,0,0}, translation); }
std::vector<float> translateX(float translation) { return SRT({1,1,1}, {0,0,0}, {translation,0,0}); }
std::vector<float> translateY(float translation) { return SRT({1,1,1}, {0,0,0}, {0,translation,0}); }
std::vector<float> translateZ(float translation) { return SRT({1,1,1}, {0,0,0}, {0,0,translation}); }

std::vector<float> Projection(float FOV, float aspectRatio, float near, float far)
{
    std::vector<float> m(16, 0.0f);
    float FOVRadian = FOV * 3.14159265359f / 180.0f;
    float tangent = std::tan(FOVRadian*0.5f);
    m[0]  = 1.0f / (aspectRatio * tangent);
    m[5]  = 1.0f / tangent;
    m[10] = -(far + near) / (far - near);
    m[11] = -1.0f;
    m[14] = -(2.0f * far * near) / (far - near);
    return m;
}
