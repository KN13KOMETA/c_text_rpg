# SPOILER ALERT
If you avoid spoilers, do not open next files.
- location.c
- location.h
- character.c
- character.h
- weapon.c
- weapon.h
# BUILDING
Build targets: linux and windows <br>
Build host: linux

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
4. Run build
    ```sh
    ./script/build.sh
    ```

