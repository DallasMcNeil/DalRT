file(GLOB DalRT_SOURCE_FILES
    "*.h"
    "*.cpp"
)

add_library (DalRT ${DalRT_SOURCE_FILES})

set_target_properties(DalRT PROPERTIES DEBUG_POSTFIX "d")

target_include_directories(DalRT PRIVATE ${CMAKE_BINARY_DIR}/include)
target_include_directories(DalRT PRIVATE ${CMAKE_BINARY_DIR}/lib)

set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/build)