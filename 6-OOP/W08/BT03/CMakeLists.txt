cmake_minimum_required(VERSION 3.10)

project(app)

file(GLOB_RECURSE SOURCES CONFIGURE_DEPENDS
    "${CMAKE_SOURCE_DIR}/src/*.cpp"
    "${CMAKE_SOURCE_DIR}/src/*.h"
)

file(GLOB_RECURSE RESOURCES
    "${CMAKE_SOURCE_DIR}/src/*.txt"
)

add_executable(app ${SOURCES})

foreach(resource ${RESOURCES})
    get_filename_component(filename ${resource} NAME)
    configure_file(${resource} ${CMAKE_BINARY_DIR}/${filename} COPYONLY)
endforeach()