add_executable(main main.c)
add_library(database database.c)
target_link_libraries(main database)

add_library(login login.c)
target_link_libraries(login database)

add_library(interface interface.c)
target_link_libraries(main interface)
target_link_libraries(interface login)
