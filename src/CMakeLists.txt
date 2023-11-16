add_executable(main main.c)
add_library(database database.c)
target_link_libraries(main database)