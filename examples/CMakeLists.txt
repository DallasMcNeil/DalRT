file(GLOB DalRT_EXAMPLE_FILES
    "*.cpp"
)

link_directories (${CMAKE_BINARY_DIR}/build)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/build)

foreach(file_path ${DalRT_EXAMPLE_FILES})

string( REPLACE ".cpp" "" new_name ${file_path} )
get_filename_component(filename ${new_name} NAME)

add_executable( ${filename} ${file_path} )

add_dependencies(${filename} DalRT)

target_link_libraries (${filename} debug DalRTd)
target_link_libraries (${filename} optimized DalRT)

target_include_directories(${filename} PRIVATE ${CMAKE_BINARY_DIR}/include)
target_include_directories(${filename} PRIVATE ${CMAKE_BINARY_DIR}/lib)

endforeach()
