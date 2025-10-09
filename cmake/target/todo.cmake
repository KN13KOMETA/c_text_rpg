set(
  TODO_EXCLUDE
  --exclude-dir
  .git
  --exclude-dir
  .cache
  --exclude-dir
  build
)

# TODO: Somehow make it crossplatform
add_custom_target(
  todo
  COMMAND
    cd ${CMAKE_SOURCE_DIR} && grep -e TODO -Hnr . ${TODO_EXCLUDE} | awk -f
    ${CMAKE_SOURCE_DIR}/scripts/awk/todo.awk
)
