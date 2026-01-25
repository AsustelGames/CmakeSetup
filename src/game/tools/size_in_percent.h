#pragma once

#include "glm/glm.hpp"
#include <algorithm>

inline glm::ivec2 Tool_GetSizeInPercent_IVec2(glm::ivec2 Size, int Percent)
{
   glm::ivec2 Result;
   std::clamp(Percent, 1, 100);
   
   Result.x = Result.x / (Result.x / Percent);
   Result.y = Result.y / (Result.y / Percent);

   return Result;
}