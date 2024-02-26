#pragma once
#include <iostream>
#include <vector>
#include <map>
#include <mutex>

struct Entry {
	size_t doc_id, count;
	


	bool operator ==(const Entry& other) const {
		return ((doc_id == other.doc_id) && (count == other.count));
	}

	Entry(const int& _doc_id, const int& _count)
		: doc_id(_doc_id), count(_count) {}
};


class Inverted_index {

	//list of document contents
	std::vector<std::string> docs;

	//a collection for storing the frequency of words found in the text
	std::map<std::string, std::vector<Entry>> freq_dictionary;
	/*
	* A function required for threads
	* 
	* @param "doc" The string to be indexed
	*/
	void string_indexing(std::string doc, int doc_id);

public:

	Inverted_index() = default;
	/*
	* Update or fill in the database of documents for which we will
	*search
	* 
	* @param input_docs the contents of the documents
	*/
	void update_document_base (std::vector<std::string> input_docs);

	/*
	* The method determines the number of occurrences of the word "word" in the uploaded
	*document database.
	* 
	* @param "word" - The word whose frequency of occurrence must be determined
	* @return returns a prepared list with the frequency of words
	*/
	std::vector<Entry> get_word_count(const std::string& word);

};