include_directories(../extern)
add_executable(lecture1 lecture1.cpp ql.h ql.cpp)
target_link_libraries(lecture1 PRIVATE IRFXLib QuantLib)

add_executable(lecture2 lecture2.cpp ql.h ql.cpp)
target_link_libraries(lecture2 PRIVATE IRFXLib QuantLib)

add_executable(lecture3 lecture3.cpp ql.h ql.cpp)
target_link_libraries(lecture3 PRIVATE IRFXLib QuantLib)

#add_executable(lecture4 lecture4.cpp ql.h ql.cpp)
#target_link_libraries(lecture4 PRIVATE IRFXLib QuantLib)

add_executable(lecture5 lecture5.cpp ql.h ql.cpp)
target_link_libraries(lecture5 PRIVATE IRFXLib QuantLib)

