#pragma once


#ifdef USE_OPENGL
   #include "glad/glad.h"
#endif

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

inline std::ostream& operator<<(std::ostream& OS, const Color& C)
{
   OS << "(" << C.r << ", " << C.g << ", " << C.b << ", " << C.a <<  ")"; return OS;
}


inline void Tool_SetRenderDrawColor(SDL_Renderer* Renderer_, Color Col) // Wrapper function for SDL_SetRenderDrawColor() that accepts the Color datatype
{
   SDL_SetRenderDrawColor(Renderer_, Col.r, Col.g, Col.b, Col.a);
}

#ifdef USE_OPENGL
   inline void Tool_glClearColor(Color Col) // Wrapper function for glClearColor() that accepts the Color datatype
   {
      glClearColor(Col.r / 255.0f, Col.g / 255.0f, Col.b / 255.0f, Col.a / 255.0f);
   }
#endif


inline Color Tool_invertColor(Color Col, bool InvertAlpha = false) // Inverts Colors
{
   Color InvertedColor = Col;

   if (InvertAlpha)
   {
      InvertedColor.r = abs(Col.r - 255);
      InvertedColor.g = abs(Col.g - 255);
      InvertedColor.b = abs(Col.b - 255);
      InvertedColor.a = abs(Col.a - 255);

      return InvertedColor;
   }
   else
   {
      InvertedColor.r = abs(Col.r - 255);
      InvertedColor.g = abs(Col.g - 255);
      InvertedColor.b = abs(Col.b - 255);

      return InvertedColor;
   }
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