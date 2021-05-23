# Find all headers in the project include folder
file(GLOB HEADERS CONFIGURE_DEPENDS "${PROJECT_SOURCE_DIR}/include/IRFXLib/*.h")

# Make a static library (tradeoff of memory for better performance)
add_library(IRFXLib STATIC "BinModel01.cpp" Options03.cpp "BinModel02.cpp" Option06.cpp DoubleDigitalPayoff.cpp Options09.cpp ${HEADERS})

# Add an alias so the target can be used while building
add_library(IRFXLib::IRFXLib ALIAS IRFXLib)

# Set the include directory for builds (tests, examples, etc) and for clients
target_include_directories(IRFXLib PUBLIC
        $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include>
        $<INSTALL_INTERFACE:include>)

# Associate the include files with the target, so they will be installed
set_target_properties(IRFXLib PROPERTIES PUBLIC_HEADER "${HEADERS}")

find_package(Threads REQUIRED)

#sudo apt install libtbb-dev
find_package(TBB REQUIRED tbb)

find_package(Boost COMPONENTS system REQUIRED)

include_directories(${Boost_INCLUDE_DIRS})

include_directories(../extern)

target_link_libraries(IRFXLib ${CMAKE_THREAD_LIBS_INIT} ${TBB_IMPORTED_TARGETS} ${Boost_LIBRARIES})

add_compile_options(-Wall -Wextra -Wpedantic -Werror)

# Set install targets and destinations
install(TARGETS IRFXLib
        EXPORT IRFXLibTargets
        LIBRARY DESTINATION lib
        ARCHIVE DESTINATION lib
        PUBLIC_HEADER DESTINATION include/IRFXLib)

# Export additional install files (for clients using CMake)
install(EXPORT IRFXLibTargets
        NAMESPACE IRFXLib::
        FILE IRFXLibConfig.cmake
        DESTINATION lib/cmake/IRFXLib)

