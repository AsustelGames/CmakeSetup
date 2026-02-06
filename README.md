
notice
currently font and image_loader tools don't support opengl 
so you need to implement image and font loading for opengl using stb

nix-shell -p gnumake cmake ninja pkg-config sdl3 enet
cmake -G Ninja -S . -B build -DCMAKE_BUILD_TYPE=Release or Debug # configure
cd build && ninja && cd .. # build
cd .. && cd build && ./CmakeSetup # run

# CmakeSetup
![](https://github.com/AsustelGames/CmakeSetup/blob/main/screenshot.png)

## Overview
- Project Structure
- Libraries
- Features
- How To Build
## Project Structure

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
-- stb_image
-- stb_image_write
-- stb_image_resize2
-- stb_trutype
## Features
## How To Build
