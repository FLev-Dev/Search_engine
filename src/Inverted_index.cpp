#include "Inverted_index.h"
#include <thread>
#include <sstream>

std::mutex freq_dictionary_M;

void Inverted_index::update_document_base(std::vector<std::string> input_docs) {
	docs = input_docs;
	std::vector<std::thread> threads;
	int i = 0;
	
	for (const auto& doc : docs) {
		threads.push_back(std::thread(&Inverted_index::string_indexing, this, doc, i));
		i++;
	};
	for (auto& t : threads) 
		t.join();
}

void Inverted_index::string_indexing(std::string doc, int doc_id) {
	std::istringstream sstream(doc);

	while (sstream) {
		std::string word;
		sstream >> word;
		if (word.empty()) return;
		
		freq_dictionary_M.lock();
			auto dict_by_word = freq_dictionary[word];
		freq_dictionary_M.unlock();

		bool found = false;
		int i = 0;
		for (; i < dict_by_word.size(); i++)
			if (dict_by_word[i].doc_id == doc_id) {
				found = true;
				break;
			}

		freq_dictionary_M.lock();
			if (found)
				freq_dictionary[word][i].count++;
			else
				freq_dictionary[word].push_back(Entry(doc_id, 1));
		freq_dictionary_M.unlock();
	}
}

std::vector<Entry> Inverted_index::get_word_count(const std::string& word) {
	return freq_dictionary[word];
}
