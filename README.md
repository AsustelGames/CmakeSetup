# CmakeSetup
![](https://github.com/AsustelGames/CmakeSetup/blob/main/screenshot.png)
## Overview
- Libraries
- Features
-  Project Structure
- How To Build
- Additional Info
- Planned Features
## Libraries
- sdl 3.4.0
- miniaudio
- glad (opengl 4.6 core)
- imgui
- glm
- enet
- fastnoiselite
- assimp
- stb
  - stb_image
  - stb_image_write
  - stb_image_resize2
  - stb_trutype
## Features
- You can switch between **OpenGL** and **SDL_Renderer** (more info in **Additional Info** section)
- Good Project structure
- Crossplatform
## Project Structure
```
CmakeSetup
├── libs
│   └── Here are all of the libraries
├── src
│   ├── game
│   │   ├── Everything game related is here (Game class, update func, render func, etc)
│   │   └── so write your code here
│   └── platform
│   │   └── Everything Platform specific is here (main function, window creation, etc)
├── assets
│   └── Here are all of your assets (no assets folder in github)
```
## How To Build
> Note that this Project has only been tested on **NixOS** using **Cmake** and **Ninja** and on **Windows** using **Visual Studio 2022** and **Cmake** and also using **MinGW** with **Msys2**

Make sure you have everything required installed
> If you are using **NixOS** run `nix-shell -p gnumake cmake ninja pkg-config sdl3` before building
### Using Ninja
#### cd into your project
```
cd /path/to/your/project
```
#### Configure your project 
This will create the build directory
```
cmake -G Ninja -S . -B build
```
#### Build your project
This will cd into your build directory then it will run the build command in this case it's **Ninja** and create the executable, after that it will cd back to your project directory
> It can also be used to rebuild your project if you made any changes
```
cd build
ninja
cd ..
```
or
```
cd build && ninja && cd ..
```
Now run your project
### Using Make
#### cd into your project
```
cd /path/to/your/project
```
#### Configure your project 
This will create the build directory
```
cmake -S . -B build
```
#### Build your project
This will cd into your build directory then it will run the build command in this case it's **Make** and create the executable, after that it will cd back to your project directory
> It can also be used to rebuild your project if you made any changes
```
cd build
make
cd ..
```
or
```
cd build && make && cd ..
```
Now run your project

## Additional Info
### How to use OpenGL
If you want to use **OpenGL** instead of **SDL_Renderer** you will need to set `USE_OPENGL` option to **True** in CmakeLists.txt on **line 81**  and reconfigure your project
```cpp
option(USE_OPENGL "Use OpenGL instead of SDL Renderer"  True) # Set it to True
```
> Note that the example code will only render when using the **SDL_Renderer**
### Before shipping your project
Before shipping your project set `PRODUCTION_BUILD` option to **True** in CmakeLists.txt on **line 80**  and reconfigure your project
```cpp
option(PRODUCTION_BUILD "Make this a production build" True) # Set it to True
```
### How to use ASSETS_PATH
Let's say you want to load an image using **stb_image** instead of specifing a long path you would load it like that
```cpp
// The image is in project/assets/sword.png
unsigned char *pixels = stbi_load(ASSETS_PATH"sword.png", etc...);
```
## Planned Features
- Don't show console when `PRODUCTION_BUILD` option is set to **True** on **Windows**
- Add an example for **OpenGL**
- Add font and image loaders using **stb_truetype** and **stb_image** for **OpenGL** and **SDL_Renderer**