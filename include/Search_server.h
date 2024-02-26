#pragma once
#include "Inverted_index.h"


struct Relative_index {
	size_t doc_id;
	float rank;

	Relative_index(const size_t& _doc_id, const float& _rank) :
		doc_id(_doc_id), rank(_rank) {};

	bool operator ==(const Relative_index& other) const {
		return (doc_id == other.doc_id && rank == other.rank);
	}
	Relative_index& operator =(const Relative_index& other) {
		if (&other != this){
			doc_id = other.doc_id;
			rank = other.rank;
		}
		return *this;
	}	

	Relative_index() = default;
};
class Search_server {
	Inverted_index _index;

	std::vector<Relative_index> search_one_req(const std::vector<std::string>& words);
	std::map<size_t, int> find_frequency(const std::vector<std::string> &words);

	void merge(std::vector<std::string>& list, int start, int end, int mid);
	void merge(std::vector<Relative_index>& list, int start, int end, int mid);
	/*
	* @param list = array std::vector<std::string> or std::vector<Relative_index>,
	*	start = start of the array, end = end of the array
	*/
	void merge_sort(std::vector<std::string>& list, int start, int end);
	void merge_sort(std::vector<Relative_index>& list, int start, int end);
public:
	/*
	* @param "idx" a reference to the class is passed to the class 
	*	constructor Inverted_index, so that the Search_server can 
	*	find out the frequency of words encountered in the query
	*/
	Search_server(Inverted_index& idx) : _index(idx){};


	/*
	* The method of processing search queries
	* 
	* @param "queries_input" search queries taken from the file "requests.json"
	*	
	* @return a sorted list of relevant responses for
	*	the specified queries
	*/
	std::vector<std::vector<Relative_index>> search(
							const std::vector<std::string>& queries_input);

};