file(GLOB SOURCES *.cpp)
file(GLOB INCLUDES *.h)

include_directories(${CMAKE_CURRENT_BINARY_DIR})

add_executable(rule5 ${SOURCES})

