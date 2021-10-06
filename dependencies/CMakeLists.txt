# This script is included by worker and library builds
# It is not meant to be built as a standalone library

# This is defined in spatialos_worker_packages.json (usually in the directory of each project
# that requires the SDK)
set(CPP_WORKER_SDK_DIR "${CMAKE_CURRENT_SOURCE_DIR}/worker_sdk")

set(CPP_WORKER_SDK_INCLUDE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/worker_sdk/headers/include")

# Depends on threading libraries.
find_package(Threads)

# On Windows this finds the import library (.lib) file, which contains information on how to link the .dll.
find_library(LIB_IMPROBABLE_WORKER
  NAMES improbable_worker
  PATHS "${CPP_WORKER_SDK_DIR}/lib"
  NO_DEFAULT_PATH)

find_file(DLL_IMPROBABLE_WORKER
  NAMES improbable_worker.dll
  PATHS "${CPP_WORKER_SDK_DIR}/lib"
  NO_DEFAULT_PATH)

# Worker SDK library.
add_library(WorkerSdk INTERFACE)

target_include_directories(WorkerSdk SYSTEM INTERFACE "${CPP_WORKER_SDK_INCLUDE_DIR}")

target_link_libraries(WorkerSdk INTERFACE
  ${LIB_IMPROBABLE_WORKER}
  # Must be at end!
  ${CMAKE_THREAD_LIBS_INIT}
  ${CMAKE_DL_LIBS})

function(CREATE_WORKER_ZIP WORKER)
  # Set artifact subdirectories.
  set(WORKER_PACKAGE_COMMAND "spatial")
  # WORKER_BUILD_DIR should not be changed so that spatial local launch
  # and spatial upload can find the worker assemblies
  set(WORKER_BUILD_DIR "${APPLICATION_ROOT}/build/assembly/worker")

  if (MSVC)
    set(WORKER_RUNTIME_LIBRARY ${DLL_IMPROBABLE_WORKER})
  else()
    SET(WORKER_RUNTIME_LIBRARY ${LIB_IMPROBABLE_WORKER})
  endif()

  # Place the dynamic worker library next to the worker executable.
  add_custom_command(TARGET ${WORKER} POST_BUILD
      COMMAND ${CMAKE_COMMAND} -E copy_if_different
          ${WORKER_RUNTIME_LIBRARY}
          $<TARGET_FILE_DIR:${WORKER}>)

  # File name of the dynamic worker library.
  get_filename_component(WORKER_RUNTIME_LIBRARY_FILE_NAME ${WORKER_RUNTIME_LIBRARY} NAME)

  # Zip the executable and dynamic worker library.
  add_custom_target(
    ${WORKER}Zip ALL
    WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
    COMMAND ${CMAKE_COMMAND} -E make_directory "${WORKER_BUILD_DIR}"
    COMMAND ${WORKER_PACKAGE_COMMAND} file zip -b "$<TARGET_FILE_DIR:${WORKER}>"
            -o "${WORKER_BUILD_DIR}/${WORKER}"
            --worker_platform=current
            "$<TARGET_FILE_NAME:${WORKER}>"
            ${WORKER_RUNTIME_LIBRARY_FILE_NAME}
    DEPENDS ${WORKER})
endfunction()