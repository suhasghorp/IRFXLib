include_directories(../extern)
add_executable(example example.cpp ql.h ql.cpp)
target_link_libraries(example PRIVATE IRFXLib QuantLib)
