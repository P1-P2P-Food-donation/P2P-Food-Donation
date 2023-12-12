add_executable(main main.c)

add_library(database database.c)
add_library(userpanel userpanel.c)
add_library(login login.c)
add_library(interface interface.c)

add_library(buy_and_sell buy_and_sell.c)
add_library(timestamp timestamp.c)
add_library(auction auction.c)
add_library(input_data input_data.c)


target_link_libraries(main database)
target_link_libraries(main interface)
target_link_libraries(main input_data)
target_link_libraries(main userpanel)
target_link_libraries(input_data database)

target_link_libraries(login database)
target_link_libraries(interface login)
target_link_libraries(database timestamp)

#Make libaries available for test dir
target_include_directories(database PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_include_directories(auction PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})