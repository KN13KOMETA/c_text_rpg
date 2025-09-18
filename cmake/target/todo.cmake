set(
  TODO_EXCLUDE
  --exclude
  todolist.sh
  --exclude
  Makefile
  --exclude-dir
  .git
  --exclude-dir
  .zig-cache
  --exclude-dir
  build
  --exclude-dir
  tool
)

# TODO: Somehow make it crossplatform
add_custom_target(
  todo
  COMMAND
    cd ${CMAKE_SOURCE_DIR} && grep -e TODO -Hnr . ${TODO_EXCLUDE} | awk -f
    ${CMAKE_SOURCE_DIR}/make/todo.awk
)
