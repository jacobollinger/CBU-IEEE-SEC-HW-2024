include(ExternalProject)

set(CMAKE_INSTALL_PREFIX ${CMAKE_CURRENT_BINARY_DIR}/install)

set(OPENCV_CMAKE_ARGS
    -DBUILD_EXAMPLES=OFF 
    -DBUILD_PERF_TESTS=OFF 
    -DBUILD_TESTS=OFF 
    -DBUILD_JAVA=OFF 
    -DBUILD_opencv_python2=OFF 
    -DBUILD_opencv_python3=OFF
    -DENABLE_PRECOMPILED_HEADERS=ON 
    -DOPENCV_ENABLE_NONFREE=ON 
    -DOPENCV_EXTRA_MODULES_PATH=${CMAKE_BINARY_DIR}/opencv_contrib-prefix/src/opencv_contrib/modules
    -DWITH_TBB=ON 
    -DWITH_LIBV4L=ON
)
if(${CMAKE_SYSTEM_PROCESSOR} MATCHES "aarch64")
    set(OPENCV_CMAKE_ARGS ${OPENCV_CMAKE_ARGS} 
        -DENABLE_NEON=ON 
        -DENABLE_VFPV3=ON
        -DCMAKE_SHARED_LINKER_FLAGS=-latomic
        -DOPENCV_FORCE_LIBATOMIC_COMPILER_CHECK=ON
    )
endif()

# Download opencv_contrib
ExternalProject_Add(opencv_contrib 
    GIT_REPOSITORY https://github.com/opencv/opencv_contrib.git
    GIT_TAG 4.8.1
    CONFIGURE_COMMAND ""
    BUILD_COMMAND ""
    INSTALL_COMMAND ""
)

# Download opencv and build & install it with opencv_contrib
ExternalProject_Add(opencv
    GIT_REPOSITORY https://github.com/opencv/opencv.git
    GIT_TAG ${OPENCV_VERSION}
    DEPENDS opencv_contrib
    CMAKE_ARGS ${OPENCV_CMAKE_ARGS} -DCMAKE_INSTALL_PREFIX:PATH=${CMAKE_INSTALL_PREFIX}
)


## Add more targets here if needed ##


# Build this project
ExternalProject_Add(${CMAKE_PROJECT_NAME}
    DEPENDS opencv
    SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}
    BINARY_DIR ${CMAKE_CURRENT_BINARY_DIR}
    CMAKE_ARGS -DUSE_SUPERBUILD=OFF
    INSTALL_COMMAND ""
)