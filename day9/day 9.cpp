#include <iostream>
#include <fstream>
#include <string>
#include <regex>
#include <iomanip> 
#include <chrono>
#include <list>
#include <algorithm>
#include <unordered_map>
#include <vector>
#include <sstream>
using namespace std;

vector<int64_t> summations = {};

bool check_if_const(vector<int64_t> vec) {
	int64_t first_val = vec[0];
	for (int i = 0; i < vec.size(); i++) {
		if (vec[i] != first_val) {
			return false;
		}
	}
	return true;
}

void differences(vector<int64_t> vec) {
	vector<int64_t> temp = {};
	for (int i = 1; i < vec.size(); i++) {
		temp.push_back(vec[i] - vec[i - 1]);
	}
	summations.push_back(temp.back());
	if (check_if_const(temp) == false) {
		differences(temp);
	}
}

int64_t extrapolate(vector<int64_t> vec) {
	int64_t results = {};
	int64_t total = 0;

	differences(vec);

	for (int c = 0; c < summations.size(); c++) {
		total += summations[c];
	}

	summations.clear();

	results = (vec.back() + total);

	return results;
}

int main() {
	int64_t total = 0;
	int64_t total_reverse = 0;
	string line;
	ifstream file("input.txt");

	if (file.is_open()) {
		while (getline(file, line)) {
			line = line+" ";
			vector<int64_t> vec = {};

			std::istringstream iss(line);
			std::string substring{};
			std::vector<std::string> substrings{};

			while (std::getline(iss, substring, ' ')) {
				vec.push_back(stoll(substring));
			}

			int64_t result = extrapolate(vec);
			total += result;

			reverse(vec.begin(), vec.end());

			result = extrapolate(vec);
			total_reverse += result;
		}
		file.close();
	}

	std::cout << "Part 1: " << total << '\n';
	std::cout << "Part 2: " << total_reverse << '\n';

	return 0;
}

