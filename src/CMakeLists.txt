set(INCLUDE_DIR ${CMAKE_SOURCE_DIR}/include)

set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

add_executable (search_engine "main.cpp" "Converter_JSON.cpp" "${INCLUDE_DIR}/Converter_JSON.h" "Inverted_index.cpp" "Search_server.cpp" )

set_property(TARGET search_engine
	PROPERTY 
	# Enable C++20 standard compliance
	CXX_STANDARD 20
)

target_link_libraries(search_engine PRIVATE nlohmann_json::nlohmann_json)

target_include_directories(search_engine PUBLIC ${INCLUDE_DIR})


enable_testing()

add_executable(
  unit_tests
  unit_tests.cc
  Inverted_index.cpp
  ${INCLUDE_DIR}/Inverted_index.h
  Search_server.cpp
  ${INCLUDE_DIR}/Search_server.h
)

target_include_directories(unit_tests PUBLIC ${INCLUDE_DIR})

target_link_libraries(
  unit_tests
  GTest::gtest_main
  nlohmann_json::nlohmann_json
)

include(GoogleTest)
gtest_discover_tests(unit_tests)
