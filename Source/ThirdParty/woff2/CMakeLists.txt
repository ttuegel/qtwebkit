set(WOFF2_DIR "${THIRDPARTY_DIR}/woff2")

set(WOFF2_INCLUDE_DIRECTORIES
  "${WOFF2_DIR}/src"
)

set(WOFF2_SOURCES
  ${WOFF2_DIR}/src/table_tags.cc
  ${WOFF2_DIR}/src/variable_length.cc
  ${WOFF2_DIR}/src/woff2_common.cc
  ${WOFF2_DIR}/src/woff2_dec.cc
  ${WOFF2_DIR}/src/woff2_out.cc
)

include_directories("${THIRDPARTY_DIR}/brotli/dec")
include_directories("${WOFF2_INCLUDE_DIRECTORIES}")
add_library(woff2 STATIC ${WOFF2_SOURCES})
target_link_libraries(woff2 brotli)
WEBKIT_SET_EXTRA_COMPILER_FLAGS(woff2)

if (COMPILER_IS_GCC_OR_CLANG)
    ADD_TARGET_PROPERTIES(woff2 COMPILE_FLAGS "-Wno-sign-compare -Wno-unused-variable -Wno-unused-parameter")
endif ()

if (CMAKE_COMPILER_IS_GNUCXX)
    ADD_TARGET_PROPERTIES(woff2 COMPILE_FLAGS "-Wno-unused-but-set-variable")
endif ()

QT_ADD_EXTRA_WEBKIT_TARGET_EXPORT(woff2)
