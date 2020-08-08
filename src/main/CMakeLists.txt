cmake_minimum_required(VERSION 2.8.7)


file(GLOB_RECURSE orderbook main.cpp)

add_executable(orderbook ${orderbook})
target_link_libraries(orderbook stdc++fs)

target_link_libraries(orderbook stdc++fs)
set_target_properties(orderbook PROPERTIES
	COMPILE_FLAGS "-pthread -DGTEST_HAS_TR1_TUPLE=0 -fpermissive "
	LINK_FLAGS "-pthread -fpermissive"
 	)



