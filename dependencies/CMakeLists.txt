# This script is included by worker and library builds
# It is not meant to be built as a standalone library

# This is defined in spatialos_worker_packages.json (usually in the directory of each project
# that requires the SDK)
set(CPP_WORKER_SDK_DIR "${CMAKE_CURRENT_SOURCE_DIR}/worker_sdk/cpp")

# C++ API libraries
find_package(Threads)
find_library(LIB_CORE_SDK CoreSdk "${CPP_WORKER_SDK_DIR}/lib" DEFAULT_PATH)
find_library(LIB_WORKER_SDK WorkerSdk "${CPP_WORKER_SDK_DIR}/lib" NO_DEFAULT_PATH)
find_library(LIB_PROTOBUF NAMES protobuf libprotobuf PATHS "${CPP_WORKER_SDK_DIR}/lib" NO_DEFAULT_PATH)
find_library(LIB_RAKNET RakNetLibStatic "${CPP_WORKER_SDK_DIR}/lib" NO_DEFAULT_PATH)
find_library(LIB_SSL ssl "${CPP_WORKER_SDK_DIR}/lib" NO_DEFAULT_PATH)
find_library(LIB_ZLIB NAMES z zlibstatic PATHS "${CPP_WORKER_SDK_DIR}/lib" NO_DEFAULT_PATH)
find_library(LIB_GPR NAMES gpr PATHS "${CPP_WORKER_SDK_DIR}/lib" NO_DEFAULT_PATH)
find_library(LIB_GRPC NAMES grpc PATHS "${CPP_WORKER_SDK_DIR}/lib" NO_DEFAULT_PATH)
find_library(LIB_GRPCXX NAMES grpc++ PATHS "${CPP_WORKER_SDK_DIR}/lib" NO_DEFAULT_PATH)

# Worker SDK in library.
add_library(WorkerSdk INTERFACE)
target_include_directories(WorkerSdk SYSTEM INTERFACE "${CPP_WORKER_SDK_DIR}/include")
target_link_libraries(WorkerSdk INTERFACE
  ${LIB_WORKER_SDK} ${LIB_CORE_SDK} ${CMAKE_THREAD_LIBS_INIT} ${LIB_PROTOBUF}
  ${LIB_RAKNET} ${LIB_ZLIB} ${LIB_GRPCXX} ${LIB_GRPC} ${LIB_GPR} ${LIB_SSL}
  # Must be at end!
  ${CMAKE_DL_LIBS})