cmake_minimum_required(VERSION 3.16)

#use the below command to sync clocks
#ntpdate time.windows.com

project(IRFXLib
        VERSION 0.1.0
        DESCRIPTION "A C++ library with City UK IR/FX modeling course"
        LANGUAGES CXX
        )

## Require C++11 for Catch2
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED YES)

# tried the below to get "run with valgrind" to work but it dodn't help
#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -DBOOST_MATH_NO_LONG_DOUBLE_MATH_FUNCTIONS")

#uncomment below to use address sanitizers
#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fsanitize=address -g -O1 -fno-omit-frame-pointer")
# Add sanitizer flags for C++ compiler for "Debug" configuration
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -fsanitize=address,undefined -fno-optimize-sibling-calls -fsanitize-address-use-after-scope -fno-omit-frame-pointer -g -O1")


## Add external dependencies here, e.g.:
## add_subdirectory(extern/example_sub_project)

## The directory for the library
add_subdirectory(src)

## Only build documentation if this is the main project, and not if it is included through add_subdirectory
if (CMAKE_PROJECT_NAME STREQUAL PROJECT_NAME)
    ## Docs only available if this is the main project
    find_package(Doxygen QUIET)
    if(Doxygen_FOUND)
        add_subdirectory(docs)
    else()
        message(STATUS "Doxygen not found, not building docs")
    endif()
    ## The example executable is only available for main project
    add_subdirectory(examples)
endif()

## Allow testing for main and subprojects if -DTESTS=TRUE
if(TESTS)
    enable_testing()
    add_subdirectory(tests)
endif()
