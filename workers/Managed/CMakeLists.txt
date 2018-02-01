# Builds a SpatialOS worker using the C++ API

# Replace project name below with your own worker name
# !!! This needs to match the artifact_name in spatialos.<name>.worker.json
# !!! because ${PROJECT_NAME} is used below when creating the zip target
project(Managed)
cmake_minimum_required(VERSION 3.0)

set(APPLICATION_ROOT "${PROJECT_SOURCE_DIR}/../..")
set(SCHEMA_SOURCE_DIR "${APPLICATION_ROOT}/schema")
set(WORKER_SDK_DIR "${APPLICATION_ROOT}/dependencies")

if(MSVC)
  add_definitions(/W2)
else()
  # Strict warnings.
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
  add_definitions(-Wall -Wextra -Werror -pedantic)
endif()

add_subdirectory(${WORKER_SDK_DIR}
  "${CMAKE_CURRENT_BINARY_DIR}/WorkerSdk") # WorkerSdk target created
add_subdirectory(${SCHEMA_SOURCE_DIR}
  "${CMAKE_CURRENT_BINARY_DIR}/Schema")    # Schema target created

set(GENERATED_CODE_DIR "${APPLICATION_ROOT}/generated_code/cpp")

# The worker binary.
# Make sure you add all worker and generated sources to the executable
file(GLOB_RECURSE SOURCE_FILES
    "src/*.cc"
    "src/*.cpp"
    "src/*.h"
    "src/*.hpp"
    )
    
add_executable(${PROJECT_NAME} ${SOURCE_FILES})

set(VS_STARTUP_PROJECT ${CMAKE_PROJECT_NAME})

target_link_libraries(${PROJECT_NAME} Schema WorkerSdk)
target_include_directories(${PROJECT_NAME} SYSTEM PRIVATE
                           ${GENERATED_CODE_DIR}
                           "${WORKER_SDK_DIR}/worker_sdk/cpp/include")

# Set artifact subdirectories.
# WORKER_BUILD_DIR should not be changed so that spatial local launch
# and spatial upload can find the worker assemblies
set(WORKER_BUILD_DIR "${APPLICATION_ROOT}/build/assembly/worker")
set(WORKER_PACKAGE_COMMAND "spatial")

# The worker in a zip.
add_custom_target(
  ${PROJECT_NAME}Zip ALL
  WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
  COMMAND ${CMAKE_COMMAND} -E make_directory "${WORKER_BUILD_DIR}"
  COMMAND ${WORKER_PACKAGE_COMMAND} file zip -b "$<TARGET_FILE_DIR:${PROJECT_NAME}>"
          -o "${WORKER_BUILD_DIR}/${PROJECT_NAME}"
          --worker_platform=current
          "$<TARGET_FILE_NAME:${PROJECT_NAME}>"
  DEPENDS ${PROJECT_NAME})
