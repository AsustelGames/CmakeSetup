platforms

windows
linux
mac
web
android
ios

libs

sdl3
glm
miniaudio
sdl_net
stb_trutype
stb_image
stb_image_write
stb_image_resize2
imgui
enet
box2d
fnl
assimp
bgfx

branches

opengl
vulkan
sdl renderer


nix-shell -p gnumake cmake ninja pkg-config sdl3 enet
cmake -G Ninja -S . -B build
cd build && ninja && cd ..
cd .. && cd build && ./crossKittyEngine

cmake -S . -B build
cd build && make && cd ..

sdl 3.4.0
glad gl 4.6 core
imgui
glm
box2d