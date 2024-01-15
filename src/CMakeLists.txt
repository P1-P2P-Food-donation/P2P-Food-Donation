add_executable(main main.c)

#Add libaries
add_library(database database.c)
add_library(userpanel userpanel.c)
add_library(login login.c)
add_library(interface interface.c)
add_library(timestamp timestamp.c)
add_library(auction auction.c)

#Link libaries to main
target_link_libraries(main userpanel)

#Link libaries to interface
target_link_libraries(interface database)
target_link_libraries(interface auction)
target_link_libraries(interface login)

#Link libaries to userpanel
target_link_libraries(userpanel interface)
target_link_libraries(userpanel auction)
target_link_libraries(userpanel login)

#Link libaries to misc
target_link_libraries(auction database)
target_link_libraries(login database)
target_link_libraries(database auction)
target_link_libraries(database timestamp)

#Make libaries available for test dir
target_include_directories(database PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_include_directories(auction PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})