#pragma once
#include "Shared.h"
#include <array>

std::array<float, 16> SRT(std::array<float, 3> scale, std::array<float, 3> rotation, std::array<float, 3> translation);
std::array<float, 16> scale (std::array<float, 3> Scale);
std::array<float, 16> scaleX(float scale);
std::array<float, 16> scaleY(float scale);
std::array<float, 16> scaleZ(float scale);
std::array<float, 16> rotate (std::array<float, 3> rotation);
std::array<float, 16> rotateX(float rotation);
std::array<float, 16> rotateY(float rotation);
std::array<float, 16> rotateZ(float rotation);
std::array<float, 16> translate (std::array<float, 3> translation);
std::array<float, 16> translateX(float translation);
std::array<float, 16> translateY(float translation);
std::array<float, 16> translateZ(float translation);

std::array<float, 16> Projection(float FOV, float aspectRatio, float near, float far);
std::array<float, 3> Normalize(std::array<float, 3> array3);

template<typename T, std::size_t N> std::array<T,N> operator+(std::array<T,N> leftArray, std::array<T,N> rightArray)
{
    std::array<T, N> result;
    for (std::size_t i = 0; i < N; i++)
    {
        result[i] = leftArray[i] + rightArray[i];
    }
    return result;
}
template<typename T, std::size_t N> std::array<T,N> operator-(std::array<T,N> leftArray, std::array<T,N> rightArray)
{
    std::array<T, N> result;
    for (std::size_t i = 0; i < N; i++)
    {
        result[i] = leftArray[i] - rightArray[i];
    }
    return result;
}
template<typename T, std::size_t N> std::array<T,N> operator*(std::array<T,N> leftArray, std::array<T,N> rightArray)
{
    std::array<T, N> result;
    for (std::size_t i = 0; i < N; i++)
    {
        result[i] = leftArray[i] * rightArray[i];
    }
    return result;
}
template<typename T, std::size_t N> std::array<T,N> operator/(std::array<T,N> leftArray, std::array<T,N> rightArray)
{
    std::array<T, N> result;
    for (std::size_t i = 0; i < N; i++)
    {
        result[i] = leftArray[i] / rightArray[i];
    }
    return result;
}

template<typename T, std::size_t N> std::array<T,N> operator+(std::array<T,N> leftArray, T scalar)
{
    std::array<T, N> result;
    for (std::size_t i = 0; i < N; i++)
    {
        result[i] = leftArray[i] + scalar;
    }
    return result;
}
template<typename T, std::size_t N> std::array<T,N> operator-(std::array<T,N> leftArray, T scalar)
{
    std::array<T, N> result;
    for (std::size_t i = 0; i < N; i++)
    {
        result[i] = leftArray[i] - scalar;
    }
    return result;
}
template<typename T, std::size_t N> std::array<T,N> operator*(std::array<T,N> leftArray, T scalar)
{
    std::array<T, N> result;
    for (std::size_t i = 0; i < N; i++)
    {
        result[i] = leftArray[i] * scalar;
    }
    return result;
}
template<typename T, std::size_t N> std::array<T,N> operator/(std::array<T,N> leftArray, T scalar)
{
    std::array<T, N> result;
    for (std::size_t i = 0; i < N; i++)
    {
        result[i] = leftArray[i] / scalar;
    }
    return result;
}

template<typename T, std::size_t N> void operator+=(std::array<T,N>& leftArray, std::array<T,N>& rightArray) { for (std::size_t i = 0; i < N; i++) leftArray[i] += rightArray[i]; }
template<typename T, std::size_t N> void operator-=(std::array<T,N>& leftArray, std::array<T,N>& rightArray) { for (std::size_t i = 0; i < N; i++) leftArray[i] -= rightArray[i]; }
template<typename T, std::size_t N> void operator*=(std::array<T,N>& leftArray, std::array<T,N>& rightArray) { for (std::size_t i = 0; i < N; i++) leftArray[i] *= rightArray[i]; }
template<typename T, std::size_t N> void operator/=(std::array<T,N>& leftArray, std::array<T,N>& rightArray) { for (std::size_t i = 0; i < N; i++) leftArray[i] /= rightArray[i]; }

template<typename T, std::size_t N> void operator+=(std::array<T,N>& leftArray, T scalar) { for (std::size_t i = 0; i < N; i++) leftArray[i] += scalar; }
template<typename T, std::size_t N> void operator-=(std::array<T,N>& leftArray, T scalar) { for (std::size_t i = 0; i < N; i++) leftArray[i] -= scalar; }
template<typename T, std::size_t N> void operator*=(std::array<T,N>& leftArray, T scalar) { for (std::size_t i = 0; i < N; i++) leftArray[i] *= scalar; }
template<typename T, std::size_t N> void operator/=(std::array<T,N>& leftArray, T scalar) { for (std::size_t i = 0; i < N; i++) leftArray[i] /= scalar; }

float dotProduct3(std::array<float, 3> leftArray, std::array<float, 3> rightArray);
std::array<float, 3> crossProduct3(std::array<float, 3> leftArray, std::array<float, 3> rightArray);
