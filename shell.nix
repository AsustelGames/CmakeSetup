{ pkgs ? import <nixpkgs> {} }:

pkgs.mkShell {
  packages = with pkgs; [
    cmake
    ninja
    glfw3
  ];

  shellHook = ''
    echo "Ready to compile"
  '';
}
