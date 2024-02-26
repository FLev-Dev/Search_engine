#include "Search_server.h"
#include <string>
#include <sstream>
#include <algorithm>


void Search_server::merge_sort(std::vector<std::string>& list, int start, int end)
{
	int mid;
	if (start < end) {

		mid = (start + end) / 2;
		merge_sort(list, start, mid);
		merge_sort(list, mid + 1, end);
		merge(list, start, end, mid);
	}
}

void Search_server::merge(std::vector<std::string>& list, int start, int end, int mid)
{
	
	int i, j, k;
	i = start;
	k = start;
	j = mid + 1;

	std::map<int, std::string> mergedList;

	while (i <= mid && j <= end) {
		auto temp_i = _index.get_word_count(list[i]);
		auto temp_j = _index.get_word_count(list[j]);
		if (temp_i.size() < temp_j.size()) {
			mergedList[k] = list[i];
			k++;
			i++;
		}
		else {
			mergedList[k] = list[j];
			k++;
			j++;
		}
	}

	while (i <= mid) {
		mergedList[k] = list[i];
		k++;
		i++;
	}

	while (j <= end) {
		mergedList[k] = list[j];
		k++;
		j++;
	}
	
	for (i = start; i < k; i++) 
		list[i] = mergedList[i];
}

void Search_server::merge_sort(std::vector<Relative_index>& list, int start, int end)
{
	int mid;
	if (start < end) {

		mid = (start + end) / 2;
		merge_sort(list, start, mid);
		merge_sort(list, mid + 1, end);
		merge(list, start, end, mid);
	}
}

void Search_server::merge(std::vector<Relative_index>& list, int start, int end, int mid) {
	int i, j, k;
	i = start;
	k = start;
	j = mid + 1;

	std::map<int, Relative_index> mergedList;

	while (i <= mid && j <= end) {
		auto temp_i = list[i].rank;
		auto temp_j = list[j].rank;
		if (temp_i < temp_j) {
			mergedList[k] = list[j];
			k++;
			j++;
		}
		else {
			mergedList[k] = list[i];
			k++;
			i++;
		}
	}

	while (i <= mid) {
		mergedList[k] = list[i];
		k++;
		i++;
	}

	while (j <= end) {
		mergedList[k] = list[j];
		k++;
		j++;
	}

	for (i = start; i < k; i++)
		list[i] = mergedList[i];
}

std::map<size_t, int> Search_server::find_frequency(const std::vector<std::string>& words)
{
	std::map<size_t, int> frequency; 	
	for (int i = 0; i < words.size(); i++) {
		auto word_count = _index.get_word_count(words[i]);
		for (const auto& j : word_count) {
			frequency[j.doc_id] += j.count;
		}
	}

	return frequency;
}

std::vector<Relative_index> Search_server::search_one_req(const std::vector<std::string>& request){
	auto word_count = _index.get_word_count(*request.begin());
	if (word_count.begin() == word_count.end()) return {};

	// doc_id, count
	std::map<size_t, int> frequency = find_frequency(request);
	float max_frequency = 0;
	for (const auto& i : frequency) {
		if (i.second > max_frequency) max_frequency = float(i.second);
	}
	std::vector<Relative_index> result;
	for (const auto& i : frequency) {
		result.push_back(Relative_index(i.first, float(i.second) / max_frequency));
	}
	merge_sort(result, 0, result.size() - 1);
	return result;
}


std::vector<std::vector<Relative_index>> Search_server::search(
										const std::vector<std::string>& queries_input){

	std::vector<std::vector<std::string>> unic_words;
	int i = 0;
	for (const auto& query : queries_input) {
		std::string temp;
		std::vector<std::string> temp_vec;
		std::stringstream ss(query);
		while (getline(ss, temp, ' ')) {
			if (std::find(temp_vec.begin(), temp_vec.end(), temp) == std::end(temp_vec)) {
				temp_vec.push_back(temp);
			}
		}
		unic_words.push_back(temp_vec);
		i++;
	}
	std::vector<std::vector<Relative_index>> result;
	for (auto& request : unic_words) {
		merge_sort(request, 0, request.size() - 1);
		result.push_back(search_one_req(request));
	}

	return result;
}

