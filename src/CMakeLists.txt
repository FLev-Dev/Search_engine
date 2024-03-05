set(INCLUDE_DIR ${CMAKE_SOURCE_DIR}/include)

add_executable (
	search_engine 
	"main.cpp" 
	"Converter_JSON.cpp"  "Inverted_index.cpp" "Search_server.cpp"
	"${INCLUDE_DIR}/Converter_JSON.h" ${INCLUDE_DIR}/Inverted_index.h ${INCLUDE_DIR}/Search_server.h
)

set_property(TARGET search_engine
	PROPERTY 
	# Enable C++17 standard compliance
	CXX_STANDARD 17
)

target_link_libraries(search_engine PRIVATE nlohmann_json::nlohmann_json)

target_include_directories(search_engine PUBLIC ${INCLUDE_DIR})