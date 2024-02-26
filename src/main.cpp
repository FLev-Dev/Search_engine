#include "Converter_JSON.h"
#include "Inverted_index.h"
#include "Search_server.h"

std::vector<std::vector<std::pair<size_t, float>>> conv_vec(std::vector<std::vector<Relative_index>>& search_result);


int main()
{
	Converter_JSON converter;
	Inverted_index index;

	std::vector<std::string> converted_documents = converter.get_text_documents();
	if (converted_documents.empty()) {
		std::cerr << "The list is empty. Check the \"config.json\" file" << std::endl;
		exit(4);
	}

	index.update_document_base(converted_documents);

	Search_server search(index);
	std::vector<std::string> requests = converter.get_requests();

	auto search_result = search.search(requests);
	auto converted_result = conv_vec(search_result);
	converter.test();
	//converter.put_answers(converted_result);
	return 0;
}

std::vector<std::vector<std::pair<size_t, float>>> conv_vec (std::vector<std::vector<Relative_index>>& search_result){
	std::vector<std::vector<std::pair<size_t, float>>> converted_result;
	for (const auto& i : search_result) {
		std::vector<std::pair<size_t, float>> temp_vec;
		for (const auto& j : i)
			temp_vec.push_back(std::make_pair(j.doc_id, j.rank));
		converted_result.push_back(temp_vec);
	}
	return converted_result;
}
