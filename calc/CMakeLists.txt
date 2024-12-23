if(CMAKE_SOURCE_DIR STREQUAL CMAKE_CURRENT_SOURCE_DIR)
  project(calc)
  find_package(LLVM REQUIRED HINTS "${LLVM_CMAKE_PATH}")
  list(APPEND CMAKE_MODULE_PATH ${LLVM_DIR})
  include_directories("${LLVM_BINARY_DIR}/include" "${LLVM_INCLUDE_DIR}")
  link_directories("${LLVM_LIBRARY_DIR}")
endif()

add_subdirectory(src)