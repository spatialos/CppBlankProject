# Builds a SpatialOS worker using the C++ API

# Replace project name below with your own worker name
# !!! This needs to match the artifact_name in spatialos.<name>.worker.json
# !!! because ${PROJECT_NAME} is used below when creating the zip target
project(External)
cmake_minimum_required(VERSION 3.7)

set(CMAKE_POSITION_INDEPENDENT_CODE ON)

set(APPLICATION_ROOT "${PROJECT_SOURCE_DIR}/../..")
set(SCHEMA_SOURCE_DIR "${APPLICATION_ROOT}/schema")
set(WORKER_SDK_DIR "${APPLICATION_ROOT}/dependencies")

# Strict warnings.
if(MSVC)
  add_definitions(/W2)
else()
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
  add_definitions(-Wall -Wextra -Werror -pedantic)
endif()

add_subdirectory(${WORKER_SDK_DIR} "${CMAKE_CURRENT_BINARY_DIR}/WorkerSdk")
add_subdirectory(${SCHEMA_SOURCE_DIR} "${CMAKE_CURRENT_BINARY_DIR}/Schema")

# Set the default Visual Studio startup project to the worker itself. This only has an effect from
# CMake 3.6 onwards.
set(VS_STARTUP_PROJECT ${PROJECT_NAME})

# The worker binary.
file(GLOB_RECURSE SOURCE_FILES
    "src/*.cc"
    "src/*.cpp"
    "src/*.h"
    "src/*.hpp")
add_executable(${PROJECT_NAME} ${SOURCE_FILES})
target_link_libraries(${PROJECT_NAME} WorkerSdk Schema)

# Set artifact subdirectories.
# WORKER_ASSEMBLY_DIR should not be changed so that spatial local launch
# and spatial upload can find the worker assemblies
set(WORKER_ASSEMBLY_DIR "${APPLICATION_ROOT}/build/assembly/worker")

# The worker in a zip.
add_custom_target(
  ${PROJECT_NAME}Zip ALL
  WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
  COMMAND ${CMAKE_COMMAND} -E make_directory "${WORKER_ASSEMBLY_DIR}"
  COMMAND spatial file zip -b "$<TARGET_FILE_DIR:${PROJECT_NAME}>"
          -o "${WORKER_ASSEMBLY_DIR}/${PROJECT_NAME}"
          --worker_platform=current
          "$<TARGET_FILE_NAME:${PROJECT_NAME}>"
  DEPENDS ${PROJECT_NAME})
