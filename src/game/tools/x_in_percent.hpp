#pragma once


#include <algorithm>


inline float Tool_GetXInPercent(float X, int Percent) // Gets size of x in percent and returns it in float
{
    int ClampedPercent = std::clamp(Percent, 0, 100);
    
    return X * ClampedPercent / 100.0f;
}
