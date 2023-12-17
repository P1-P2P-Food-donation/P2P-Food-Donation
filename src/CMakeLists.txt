add_executable(main main.c)

add_library(database database.c)
add_library(userpanel userpanel.c)
add_library(login login.c)
add_library(interface interface.c)


add_library(timestamp timestamp.c)
add_library(auction auction.c)


target_link_libraries(main database)
target_link_libraries(main interface)

target_link_libraries(main userpanel)


target_link_libraries(login database)
target_link_libraries(interface login)
target_link_libraries(interface auction)
target_link_libraries(interface database)
target_link_libraries(userpanel interface)


target_link_libraries(database timestamp)

#Make libaries available for test dir
target_include_directories(database PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_include_directories(auction PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})