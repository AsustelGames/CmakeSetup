#!/usr/bin/env bash

scriptName=$(basename $0)
projectDir=$(dirname "$0")
projectName=$(cat "${projectDir}/CMakeLists.txt" | awk -F'[()]' '/project\(/ {print $2}')
[[ -z "${projectName}" || -z "${projectDir}" ]] && exit

cmd="$1"
preset="$2"

buildDir="${projectDir}/build/${preset}"
binaryPath="${buildDir}/${projectName}"

compileCommandsBuildDirPath="${buildDir}/compile_commands.json"
compileCommandsPath="${projectDir}/compile_commands.json"

helpInfo="${scriptName} [commands]

commands:
  ns, nix-shell                       enter nix-shell
  lp, list-presets                    lists presets from 'CMakePresets.json'

  co, configure [cmake preset]        configures '${projectName}'
  bu, build [cmake preset]            builds/rebuilds '${projectName}'
  ru, run [cmake preset]              runs '${projectName}'

  cb, configure-build [cmake preset]  configures and builds '${projectName}'
  br, build-run [cmake preset]        builds/rebuilds and runs '${projectName}'
  db, delete-rebuild [cmake preset]   deletes and rebuilds '${projectName}' fully \n\n"

presetCheck() { [ -z "${preset}" ] && echo "No preset selected" && exit; }
binarycheck() { [ ! -f "${binaryPath}" ] && echo "No executable for '${preset}' preset" && exit; }

createCompileCommandsSymlink() { rm "${compileCommandsPath}" > /dev/null 2>&1 || true; [ -f "${compileCommandsBuildDirPath}" ] && ln -P "${compileCommandsBuildDirPath}" "${compileCommandsPath}"; }

configure() { presetCheck; cd "${projectDir}"; cmake --preset "${preset}"; createCompileCommandsSymlink; }
build() { presetCheck; cd "${projectDir}"; cmake --build --preset "${preset}"; }
run() { presetCheck; binarycheck; "./${binaryPath}"; }
deleteBuildDir() { presetCheck; rm -rf "${buildDir}" >&2; rm "${compileCommandsPath}" > /dev/null 2>&1 || true; }

case "$1" in
  "nix-shell"      |"ns") cd "${projectDir}" && nix-shell shell.nix ;;
  "list-presets"   |"lp") cmake --list-presets ;;
  "configure"      |"co") configure ;;
  "build"          |"bu") build ;;
  "run"            |"ru") run ;;
  "configure-build"|"cb") configure && build ;;
  "build-run"      |"br") build && run ;;
  "delete-rebuild" |"db") deleteBuildDir && configure && build ;;
  *) printf "${helpInfo}" ;;
esac
