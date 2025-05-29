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
Build system: bash scripts <br>
Compiler: zig <br>

If zig not installed:

1. Download [zig](https://ziglang.org/download/)
2. Extract it in `tool` dir
   ```sh
   tar -xf zig*
   ```
   Bash script will autodetect zig in `tool` dir using `grep --color=never zig`
3. Delete zig archive
   ```sh
   rm zig*.tar.*
   ```

So in the end you have `tool/zig-dir`

Then you can simply run `./script/build.sh`, which will build executable for both linux and windows.

# DEVELOPING

Install zig (if you doesn't have it) how described in BUILDING instruction. <br>

Run `source ./script/env.sh` which will do some work for you. Like setup zig and commands in current terminal $PATH. <br>

## Commands

- build - will build windows and linux binaries.
- buildtest - will build linux bin and run it.
- todolist - will print every TODO.
