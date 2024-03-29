#include "Converter_JSON.h"

#include <fstream>
#include <string>

json Converter_JSON::take_data_from_file(std::string file_name) const {
	json j_file;
	std::ifstream file(RESOURSES_PATH + file_name);
	if (!file) {
		std::cerr << "File \"" << file_name << "\" is missing!" << std::endl;
		exit(2);
	}
	file >> j_file;
	file.close();

	if (j_file.begin() == j_file.end()) {
		std::cerr << "File \"" << file_name << "\" is empty!" << std::endl;
		exit(3);
	}

	return j_file;
}

std::vector<std::string> Converter_JSON::get_text_documents() const {
	std::vector<std::string> documents;

	json file_list = take_data_from_file("config.json");

	for(auto& it : file_list["files"]){
		//JSON throws an error when concatenating strings. 
		// Therefore, we will convert it to a string first.
		std::string config_path = it;
		std::ifstream file(FILES_PATH + config_path);
		if (!file) {
			std::cerr << "File \"" << it << "\" not found!" << std::endl;
			continue;
		}
		std::string file_text(std::istreambuf_iterator<char>{file}, {});
		file.close();

		documents.push_back(file_text);
	}
	return documents;
}

int Converter_JSON::get_responses_limit() const {
	int limit = 0;

	json j_file = take_data_from_file("config.json");
	
	for (auto it = j_file["config"].begin(); it != j_file["config"].end(); ++it) {
		if (it.key() == "max_responses")
			limit = it.value();
	}
	return limit;
}

std::vector<std::string> Converter_JSON::get_requests() const {
	std::vector<std::string> requests;
	json j_file = take_data_from_file("requests.json");
	for (auto& it : j_file["requests"]) {
		requests.push_back(it);
	}
	return requests;
}

void Converter_JSON::put_answers(std::vector<std::vector<std::pair<size_t, float>>>& answers) const {
	int limit = get_responses_limit();
	std::string file_name = RESOURSES_PATH;
	std::ofstream file(file_name + "answers.json");
	if (!file) {
		std::cerr << "File could not be created" << std::endl;
		exit(4);
	}
	nlohmann::ordered_json jfile;
	for (int i = 0; i < answers.size(); i++) {
		std::string request_num = "request";
		if (i + 1 < 100) request_num += '0';
		if (i + 1 < 10) request_num += '0';
		request_num += std::to_string(i + 1);

		if (answers[i].empty()) {
			jfile["answers"][request_num]["result"] = false;
			continue;
		}
		jfile["answers"][request_num]["result"] = true;
		if (answers[i].size() == 1) {
			std::string docid_name = "docid_" + std::to_string(answers[i][0].first);
			float rounded = round(answers[i][0].second * 100) / 100;
			jfile["answers"][request_num][docid_name] = { {"rank", rounded} };
			continue;
		}
		nlohmann::ordered_json jfile_temp;
		jfile["answers"][request_num]["result"] = true;
		for (int j = 0; j < answers[i].size(); j++) {
			if (j >= limit) break;
			std::string docid_name = "docid_" + std::to_string(answers[i][j].first);
			float rounded = round(answers[i][j].second * 100) / 100;
			jfile["answers"][request_num]["relevance"][docid_name] = { {"rank", rounded} };
		};
		
	}
	file << jfile;
	file.close();
}