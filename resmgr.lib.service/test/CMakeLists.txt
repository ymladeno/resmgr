add_executable(	test_sample
				${CMAKE_CURRENT_SOURCE_DIR}/sample/main.cpp)

target_include_directories( test_sample PUBLIC
							${CMAKE_HOME_DIRECTORY}/src/sample)

target_link_libraries( 	test_sample
						-L${CMAKE_BINARY_DIR}/src/sample/ -lsrvsample)
