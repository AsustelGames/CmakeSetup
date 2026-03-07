#pragma once


#ifdef USE_OPENGL
   #include "glad/glad.h"
#endif
#include "SDL3/SDL.h"

#include <iostream>
#include <cstdint>


namespace Tool
{

   struct Color
   {
      Uint8 r, g, b, a;
   
      bool operator==(const Tool::Color& Other) const
      {
         return r == Other.r && g == Other.g && b == Other.b && a == Other.a;
      }

      bool operator!=(const Tool::Color& Other) const
      {
            return r != Other.r || g != Other.g || b != Other.b || a != Other.a;
      }
   };

   inline std::ostream& operator<<(std::ostream& OS, const Tool::Color& Color)
   {
      OS << "(" << static_cast<int>(Color.r) << ", " << static_cast<int>(Color.g) << ", " << static_cast<int>(Color.b) << ", " << static_cast<int>(Color.a) <<  ")"; return OS;
   }


   inline void SDL_SetRenderDrawColor(SDL_Renderer* Renderer_, Tool::Color Color) // Wrapper function for SDL_SetRenderDrawColor() that accepts the Color datatype
   {
      SDL_SetRenderDrawColor(Renderer_, Color.r, Color.g, Color.b, Color.a);
   }

   #ifdef USE_OPENGL
      inline void glClearColor(Tool::Color Color) // Wrapper function for glClearColor() that accepts the Color datatype
      {
         ::glClearColor(Color.r / 255.0f, Color.g / 255.0f, Color.b / 255.0f, Color.a / 255.0f); // Using global namespace to call the glClearColor() instead of self (Tool::glClearColor())
      }
   #endif


   inline Color invertColor(Tool::Color Color, bool InvertAlpha = false) // Inverts Colors
   {
      Tool::Color InvertedColor = Color;
      
      if (InvertAlpha)
      {
         InvertedColor.r = 255 - Color.r;
         InvertedColor.g = 255 - Color.g;
         InvertedColor.b = 255 - Color.b;
         InvertedColor.a = 255 - Color.a;
         
         return InvertedColor;
      }
      else
      {
         InvertedColor.r = 255 - Color.r;
         InvertedColor.g = 255 - Color.g;
         InvertedColor.b = 255 - Color.b;
         
         return InvertedColor;
      }
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