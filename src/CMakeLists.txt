file(GLOB DalRT_SOURCE_FILES
    "*.h"
    "*.cpp"
)

add_library (DalRT ${DalRT_SOURCE_FILES})

target_include_directories(DalRT PRIVATE ${CMAKE_BINARY_DIR}/include)
target_include_directories(DalRT PRIVATE ${CMAKE_BINARY_DIR}/lib)

set(CMAKE_LIBRARY_OUTPUT_DIRECTORY_DEBUG ${CMAKE_BINARY_DIR}/build/${OUTPUT_DEBUG})
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY_RELEASE ${CMAKE_BINARY_DIR}/build/${OUTPUT_REL})