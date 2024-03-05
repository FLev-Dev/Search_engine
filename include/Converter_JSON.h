#pragma once
#include <nlohmann/json.hpp>
#include <iostream>
#include <vector>

//Change this if ur compiler not MinGW or ur OS not a Windows
constexpr auto RESOURSES_PATH = "..\\..\\resourses\\";
constexpr auto FILES_PATH = "..\\..\\resourses\\files for search\\";



using json = nlohmann::json;


class Converter_JSON {
private: 	
	/*
	*	@return json from the file_name
	*/
	json take_data_from_file(std::string file_name);

public:
	Converter_JSON() = default;
	/*
	*	@return a list with the contents
	*	 of the files listed in CONFIG_FILE
	*/
	std::vector<std::string> get_text_documents();

	/*
	*	Reads the max_responses field to determine the
	*	 maximum number of responses per request
	*	@return maximum number of responses per request from
	*/
	int get_responses_limit();

	/*
	*	@return a list with the contents
	*	 of the files listed in CONFIG_FILE
	*/
	std::vector<std::string> get_requests();

	/*
	*	Adds an answer to the file.json search results
	*/
	void put_answers(std::vector<std::vector<std::pair<size_t, float>>>& answers);
};