project(${CMAKE_PROJECT_NAME}_ARDUINO)

set(${PROJECT_NAME}_BOARD arduino:avr:uno)

if(CMAKE_BUILD_TYPE STREQUAL "Release")
    # set(${CMAKE_PROJECT_NAME}_PORT CACHE STRING /dev/ttyACM0)
else()
    set(${PROJECT_NAME}_PORT CACHE STRING "Arduino port")

    if(NOT ${PROJECT_NAME}_PORT)
        message(WARNING "Arduino port not set. Please set it with -D${PROJECT_NAME}_PORT=/path/to/port or the variable in the CMakeCache.txt")
    endif()
endif()

set(${PROJECT_NAME}_SKETCH ${CMAKE_CURRENT_SOURCE_DIR}/main/main.ino)

if (NOT EXISTS "/dev/ttyUSB0")
    message(WARNING "Arduino is not connected to /dev/ttyUSB0. Please connect it or change the port with -D${PROJECT_NAME}_PORT=/path/to/port or the variable in the CMakeCache.txt")
endif()

add_custom_target(${PROJECT_NAME}
    COMMAND arduino-cli compile --fqbn ${${PROJECT_NAME}_BOARD} --build-path ${CMAKE_BINARY_DIR}/Arduino ${${PROJECT_NAME}_SKETCH}
    COMMAND arduino-cli upload --fqbn ${${PROJECT_NAME}_BOARD} --port ${${PROJECT_NAME}_PORT} --input-dir ${CMAKE_BINARY_DIR}/Arduino ${${PROJECT_NAME}_SKETCH}
)


