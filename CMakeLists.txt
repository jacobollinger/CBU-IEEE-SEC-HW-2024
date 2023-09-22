cmake_minimum_required(VERSION 3.10)
project(CBU_IEEE_ROBOTICS_2024)


set(CMAKE_CXX_STANDARD 11)

set(SOURCE_DIR "${PROJECT_SOURCE_DIR}/src")
set(SOURCE_FILES 
    ${SOURCE_DIR}/main.cpp
)

find_package(OpenCV REQUIRED)

add_executable(CBU_IEEE_ROBOTICS_2024 ${SOURCE_FILES})

target_include_directories(CBU_IEEE_ROBOTICS_2024 PRIVATE ${PROJECT_SOURCE_DIR}/include)

target_link_libraries(CBU_IEEE_ROBOTICS_2024 ${OpenCV_LIBS})

add_subdirectory(Timer)
target_link_libraries(CBU_IEEE_ROBOTICS_2024 CBU_IEEE_ROBOTICS_2024_TIMER)
