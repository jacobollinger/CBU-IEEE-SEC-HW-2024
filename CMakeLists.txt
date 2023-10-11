cmake_minimum_required(VERSION 3.15)
project(CBU_IEEE_SEC_HW_2024)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_DIR "${PROJECT_SOURCE_DIR}/src")
set(SOURCE_FILES 
    ${SOURCE_DIR}/Main.cpp
)

# option(USE_SUPERBUILD "Use Superbuild" ON)

# if(USE_SUPERBUILD)
#     include(cmake/SuperBuild.cmake)
#     return()
# endif()

# list(APPEND CMAKE_PREFIX_PATH "${CMAKE_BINARY_DIR}/install")

# find_package(OpenCV REQUIRED)

add_executable(${CMAKE_PROJECT_NAME} ${SOURCE_FILES})

target_include_directories(${CMAKE_PROJECT_NAME} PRIVATE ${PROJECT_SOURCE_DIR}/include)

# target_link_libraries(${CMAKE_PROJECT_NAME} ${OpenCV_LIBS})

add_subdirectory(Timer)
target_link_libraries(${CMAKE_PROJECT_NAME} ${CMAKE_PROJECT_NAME}_TIMER)
