include_directories(../extern/catch2)
include_directories(../extern)

add_executable(test_Lecture1 catch_config.cpp test_Lecture1.cpp)

target_link_libraries(test_Lecture1 PRIVATE IRFXLib)

add_test(NAME Lecture1_test COMMAND test_Lecture1)
