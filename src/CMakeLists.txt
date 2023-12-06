add_executable(main main.c)

add_library(database database.c)
add_library(userpanel userpanel.c)
add_library(login login.c)
add_library(interface interface.c)
add_library(buy_and_sell buy_and_sell.c)

target_link_libraries(main database)
target_link_libraries(main interface)
target_link_libraries(login database)
target_link_libraries(interface login)