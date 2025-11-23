#pragma once


#include "SDL3/SDL.h"
#include "glad/glad.h"

#include <iostream>
#include <cstdint>


struct Color
{
   uint8_t r, g, b, a;
   
   bool operator==(const Color& Other) const
   {
      return r == Other.r && g == Other.g && b == Other.b && a == Other.a;
   }

   bool operator!=(const Color& Other) const
   {
      return r != Other.r || g != Other.g || b != Other.b || a != Other.a;
   }
};

inline std::ostream& operator<<(std::ostream& OS5, const Color& V5)
{
   OS5 << "(" << V5.r << ", " << V5.g << ", " << V5.b << ", " << V5.a <<  ")"; return OS5;
}

inline void COL_glClearColor(Color Color) // custom glClearColor() that accepts Color datatype
{
   glClearColor(Color.r / 255.0f, Color.g / 255.0f, Color.b / 255.0f, Color.a / 255.0f);
}

#define BLACK {0, 0, 0, 255}
#define GRAY {100, 100, 100, 255}
#define WHITE {255, 255, 255, 255}
#define RED {255, 0, 0, 255}
#define ORANGE {255, 100, 0, 255}
#define YELLOW {255, 255, 0, 255}
#define GREEN {0, 255, 0, 255}
#define CYAN {0, 255, 255, 255}
#define BLUE {0, 0, 255, 255}
#define MAGENTA {255, 0, 255, 255}