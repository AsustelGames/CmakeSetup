#pragma once


#include <algorithm>


inline float Tool_GetXInPercent(float X, int Percent) // Gets size of x in percent and returns it in float
{
   float Result = X;
   std::clamp(Percent, 1, 100);
   
   Result = Result / (Result / Percent);
   
   return Result;
}
