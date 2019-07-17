# This script is included by worker and library builds
# It is not meant to be built as a standalone library

# This is defined in spatialos_worker_packages.json (usually in the directory of each project
# that requires the SDK)
if(WIN32)
  set(CPP_WORKER_SDK_DIR "${CMAKE_CURRENT_SOURCE_DIR}/worker_sdk/win32")
elseif(UNIX)
  if(APPLE)
    set(CPP_WORKER_SDK_DIR "${CMAKE_CURRENT_SOURCE_DIR}/worker_sdk/macos")
  else()
    set(CPP_WORKER_SDK_DIR "${CMAKE_CURRENT_SOURCE_DIR}/worker_sdk/linux")
  endif()
endif()

set(CPP_WORKER_SDK_INCLUDE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/worker_sdk/headers/include")

# Depends on threading libraries.
find_package(Threads)

# Debug libraries.
find_library(LIB_IMPROBABLE_WORKER_DEBUG
  NAMES improbable_worker
  PATHS "${CPP_WORKER_SDK_DIR}/debug/lib" "${CPP_WORKER_SDK_DIR}/lib"
  NO_DEFAULT_PATH)
find_library(LIB_RAKNET_DEBUG
  NAMES RakNetLibStatic
  PATHS "${CPP_WORKER_SDK_DIR}/debug/lib" "${CPP_WORKER_SDK_DIR}/lib"
  NO_DEFAULT_PATH)
find_library(LIB_SSL_DEBUG
  NAMES ssl
  PATHS "${CPP_WORKER_SDK_DIR}/debug/lib" "${CPP_WORKER_SDK_DIR}/lib"
  NO_DEFAULT_PATH)
find_library(LIB_ZLIB_DEBUG
  NAMES z zlibstatic
  PATHS "${CPP_WORKER_SDK_DIR}/debug/lib" "${CPP_WORKER_SDK_DIR}/lib"
  NO_DEFAULT_PATH)

# Release libraries.
find_library(LIB_IMPROBABLE_WORKER_RELEASE
  NAMES improbable_worker
  PATHS "${CPP_WORKER_SDK_DIR}/release/lib" "${CPP_WORKER_SDK_DIR}/lib"
  NO_DEFAULT_PATH)
find_library(LIB_RAKNET_RELEASE
  NAMES RakNetLibStatic
  PATHS "${CPP_WORKER_SDK_DIR}/release/lib" "${CPP_WORKER_SDK_DIR}/lib"
  NO_DEFAULT_PATH)
find_library(LIB_SSL_RELEASE
  NAMES ssl
  PATHS "${CPP_WORKER_SDK_DIR}/release/lib" "${CPP_WORKER_SDK_DIR}/lib"
  NO_DEFAULT_PATH)
find_library(LIB_ZLIB_RELEASE
  NAMES z zlibstatic
  PATHS "${CPP_WORKER_SDK_DIR}/release/lib" "${CPP_WORKER_SDK_DIR}/lib"
  NO_DEFAULT_PATH)

# Worker SDK library.
add_library(WorkerSdk INTERFACE)

target_include_directories(WorkerSdk SYSTEM INTERFACE "${CPP_WORKER_SDK_INCLUDE_DIR}")

target_link_libraries(WorkerSdk INTERFACE
  debug ${LIB_IMPROBABLE_WORKER_DEBUG} optimized ${LIB_IMPROBABLE_WORKER_RELEASE}
  debug ${LIB_RAKNET_DEBUG} optimized ${LIB_RAKNET_RELEASE}
  debug ${LIB_ZLIB_DEBUG} optimized ${LIB_ZLIB_RELEASE}
  debug ${LIB_SSL_DEBUG} optimized ${LIB_SSL_RELEASE}
  # Must be at end!
  ${CMAKE_THREAD_LIBS_INIT}
  ${CMAKE_DL_LIBS})
