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

Build targets: linux and windows <br>
Build host: linux <br>
Build system: make <br>
Compiler: zig <br>

If zig not installed:

1. Download [zig](https://ziglang.org/download/)
2. Extract it in `tool` dir
   ```sh
   tar -xf zig*
   ```
   make will autodetect zig in `tool` dir using `grep --color=never zig`
3. Delete zig archive
   ```sh
   rm zig*.tar.*
   ```

So in the end you have `tool/zig-dir`

Then you can simply run `make`, to see build options.

# DEVELOPING

Install zig (if you doesn't have it) how described in BUILDING instruction. <br>

## Commands

Run `make help` or `make` to see all commands.
