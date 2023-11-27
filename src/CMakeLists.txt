add_executable(main main.c)
add_library(database database.c
        buy_and_sell.c
        buy_and_sell.h)
target_link_libraries(main database)