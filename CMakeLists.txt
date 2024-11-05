cmake_minimum_required(VERSION 3.11)
project("RV32I")

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(cache_srcs
    main.cpp
)
set(ideal_cache_srcs
    src/ideal_cache.cpp
)
set(test_srcs
    src/tests.cpp
)

if (NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Release)
endif()

set(CMAKE_CXX_FLAGS_RELEASE "-O2")
set(FLAGS "-D NDEBUG")

add_executable(cache.x ${cache_srcs})
add_executable(test.x  ${test_srcs})
add_executable(ideal_cache.x  ${ideal_cache_srcs})

target_include_directories(cache.x PRIVATE 
            ${CMAKE_SOURCE_DIR}/include
)
target_include_directories(test.x PRIVATE 
            ${CMAKE_SOURCE_DIR}/include
)
target_include_directories(ideal_cache.x PRIVATE 
            ${CMAKE_SOURCE_DIR}/include
)

target_compile_options(cache.x       PRIVATE "$<$<CONFIG:RELEASE>:${CMAKE_CXX_FLAGS_RELEASE}>" ${FLAGS})
target_compile_options(test.x        PRIVATE "$<$<CONFIG:RELEASE>:${CMAKE_CXX_FLAGS_RELEASE}>" ${FLAGS})
target_compile_options(ideal_cache.x PRIVATE "$<$<CONFIG:RELEASE>:${CMAKE_CXX_FLAGS_RELEASE}>" ${FLAGS})


# cmake -DCMAKE_BUILD_TYPE=Release -S . -B build
# cmake --build build
# cmake -DCMAKE_BUILD_TYPE=Release
# ./build/cache.x
#
# cmake .. -DCMAKE_CXX_INCLUDE_WHAT_YOU_USE=./../../../../include-what-you-use/build/bin/include-what-you-use
# make
