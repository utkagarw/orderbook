cmake_minimum_required(VERSION 2.8.7)

file(GLOB_RECURSE all_test_files *)
#file(GLOB zstd_static_lib ${PROJECT_EXT_LIB_DIR}/zstd/libzstd*.a*)

add_executable(book.test ${all_test_files})
target_link_libraries(book.test gtest_main)
target_link_libraries(book.test stdc++fs)

set_target_properties(book.test PROPERTIES
	COMPILE_FLAGS "-pthread -DGTEST_HAS_TR1_TUPLE=1 -fPIC -fpermissive -fmessage-length=0"
	LINK_FLAGS "-pthread -fmessage-length=0 "
 	)