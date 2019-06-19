add_executable(vector vector.cpp)
target_link_libraries(vector hemingway)
add_test(vector vector)

add_executable(table table.cpp)
target_link_libraries(table hemingway)
add_test(table table)
