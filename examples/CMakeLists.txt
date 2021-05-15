include_directories(../extern)
add_executable(lecture1 lecture1.cpp ql.h ql.cpp)
target_link_libraries(lecture1 PRIVATE IRFXLib QuantLib)

add_executable(lecture2 lecture2.cpp ql.h ql.cpp)
target_link_libraries(lecture2 PRIVATE IRFXLib QuantLib)
