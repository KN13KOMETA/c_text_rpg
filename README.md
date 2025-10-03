# SPOILER ALERT

If you avoid spoilers, do not open next files.
- story.c
- story.h
- location.c
- location.h
- character.c
- character.h
- weapon.c
- weapon.h

# BUILDING

## Requirements

- CMake (3.15+)
- Build system (Make, Ninja or other)
- C compiler (Zig required for cross-compiling)

## Compiling (current platform)

1. Create build directory:
   ```bash
   cmake -S . -B build -DCMAKE_BUILD_TYPE=Release
   ```
      _Note: For debug build use `-DCMAKE_BUILD_TYPE=Debug`_
2. Build project:
   ```bash
   cmake --build build --parallel
   ```
    _Flag `--parallel` speed ups building by using paralleling_
3. In result there will be an executable in `build` directory

## Cross-compiling

1. Select toolchain (they are in root directory, for example `x86_64-windows-gnu.cmake`)
2. Create build directory:
   ```bash
   cmake -S . -B build-windows --toolchain x86_64-windows-gnu.cmake -DCMAKE_BUILD_TYPE=Release
   ```
3. Build project:
   ```bash
   cmake --build build-windows
   ```
4. In result there will be an executable in `build-windows` directory

## Additional options

- Generate build directory using Ninja build system:
   ```bash
   cmake -S . -B build -G Ninja -DCMAKE_BUILD_TYPE=Release
   ```
- List available targets:
   ```bash
   cmake --build build --target help
   ```
- Clean build directory:
   ```bash
   cmake --build build --target clean
   ```
- Print todo comments:
   ```bash
   cmake --build build --target todo
   ```

# DEVELOPING

Create build directory with `build` name. It will generate `build/compile_commands.json` file as well which is auto-detected by `clangd` (LSP).

# RESOURCES

- Zig toolchain stolen from https://github.com/mrexodia/zig-cross