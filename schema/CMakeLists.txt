# This script is included by worker and library builds
# It is not meant to be built as a standalone library

set(GENERATED_CODE_DIR "${APPLICATION_ROOT}/generated_code/cpp")

# Schema generated code in library
set(SCHEMA_FILES
  blank.schema
  )

set(SCHEMA_SOURCE_FILES
  "${GENERATED_CODE_DIR}/blank.cc"
  "${GENERATED_CODE_DIR}/blank.h"
  "${GENERATED_CODE_DIR}/improbable/standard_library.cc"
  "${GENERATED_CODE_DIR}/improbable/standard_library.h"
  )

source_group(schema "${CMAKE_CURRENT_SOURCE_DIR}/[^/]*")
source_group(generated_code\\schema "${GENERATED_CODE_DIR}/[^/]*")
source_group(generated_code\\improbable "${GENERATED_CODE_DIR}/improbable/[^/]*")

add_library(Schema STATIC ${SCHEMA_FILES} ${SCHEMA_SOURCE_FILES})
target_include_directories(Schema SYSTEM PUBLIC "${GENERATED_CODE_DIR}")

target_link_libraries(Schema PRIVATE WorkerSdk)