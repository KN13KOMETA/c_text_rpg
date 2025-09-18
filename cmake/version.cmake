# NOTE: When updating version you are supposed to only change version and/or prerelease
# You should set major.minor.patch in root file project

# Setting prerelease
set(PROJECT_VERSION_PRERELEASE "beta")

# Getting git short hash
execute_process(
  COMMAND git rev-parse --short HEAD
  WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
  OUTPUT_VARIABLE GIT_SHORT_HASH
  OUTPUT_STRIP_TRAILING_WHITESPACE
)

# Combining all we have into PROJECT_FULL_VERSION
set(PROJECT_FULL_VERSION "${PROJECT_VERSION}")
if(PROJECT_VERSION_PRERELEASE)
  set(
    PROJECT_FULL_VERSION
    "${PROJECT_FULL_VERSION}-${PROJECT_VERSION_PRERELEASE}"
  )
endif()
if(GIT_SHORT_HASH)
  set(PROJECT_FULL_VERSION "${PROJECT_FULL_VERSION}+b.${GIT_SHORT_HASH}")
endif()
