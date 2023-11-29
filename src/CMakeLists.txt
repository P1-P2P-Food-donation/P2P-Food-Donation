add_executable(main main.c)
add_library(database database.c
        userpanel.c
        userpanel.h)
target_link_libraries(main database)