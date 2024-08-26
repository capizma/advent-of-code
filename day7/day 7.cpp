// https://adventofcode.com/2023/day/7
// Day 7 (complete)

#include <iostream>
#include <fstream>
#include <string>
#include <regex>
#include <iomanip> 
#include <chrono>
#include <list>
#include <algorithm>
#include <unordered_map>
using namespace std;

/*
1 - High card
2 - One pair
3 - Two pair
4 - Three of a kind
5 - Full house
6 - Four of a kind
7 - Five of a kind
*/

unordered_map<int, int> um = { {5,1},{7,2},{9,3},{11,4},{13,5},{17,6},{25,7} };
unordered_map<char, string> charmap = { {'2',"02"},{'3',"03"},{'4',"04"},{'5',"05"},{'6',"06"},{'7',"07"},{'8',"08"},{'9',"09"},{'T',"10"},{'J',"11"},{'Q',"12"},{'K',"13"},{'A',"14"} };
unordered_map<char, string> charmap_joker = { {'2',"02"},{'3',"03"},{'4',"04"},{'5',"05"},{'6',"06"},{'7',"07"},{'8',"08"},{'9',"09"},{'T',"10"},{'J',"01"},{'Q',"12"},{'K',"13"},{'A',"14"} };

vector<int> evaluate_worth(string card) {
	vector<int> output = {};
	std::string::difference_type n_all;
	int first_worth = 0;
	int cnt_all = 0;
	int highest_count = 0;
	char highest_char = 'x';
	for (int i = 0; i < card.size(); i++) {
		n_all = std::count(card.begin(), card.end(), card[i]);
		cnt_all += (int)n_all;
		if ((int)n_all > highest_count && card[i] != 'J') {
			highest_count = n_all;
			highest_char = card[i];
		}
	}
	// yeah i know, they had to fill one of my hands with just jokers.
	if (highest_char == 'x') {
		highest_char = '1';
	}

	first_worth = um.at(cnt_all);
	
	string replaced = "";
	for (int i = 0; i < card.size(); i++) {
		if (card[i] == 'J') {
			replaced += highest_char;
		}
		else {
			replaced += card[i];
		}
	}

	int second_worth = 0;
	cnt_all = 0;
	for (int i = 0; i < replaced.size(); i++) {
		n_all = std::count(replaced.begin(), replaced.end(), replaced[i]);
		cnt_all += (int)n_all;
	}
	second_worth = um.at(cnt_all);

	output.push_back(first_worth);
	output.push_back(second_worth);

	return output;
}

int calc_total(vector<int> jworths,vector<int64_t> jorder) {
	int64_t total = 0;
	int64_t pos = 0;

	for (int c = 0; c < 8; c++) {
		vector<int64_t> handtype = {};
		for (int i = 0; i < jorder.size(); i++) {
			if (jworths[i] == c) {
				handtype.push_back(jorder[i]);
			}
		}
		sort(handtype.begin(), handtype.end());
		for (int h = 0; h < handtype.size(); h++) {
			pos++;
			string temp = to_string(handtype[h]);
			total += (pos)*stol(temp.substr(temp.size() - 4, 4));
		}
	}
	return total;
}

int main() {
	string ln;
	string line;
	ifstream file("input.txt");
	vector<int> worths = {};
	vector<int> joker_worths = {};
	vector<int64_t> order = {};
	vector<int64_t> joker_order = {};

	if (file.is_open()) {
		while (getline(file, ln)) {
			string card;
			string bid;
			string hand_to_int = "";
			string hand_to_int_joker = "";
			card = ln.substr(0, ln.find(' '));
			bid = to_string(stoi(ln.substr(ln.find(' '), ln.size() - ln.find(' '))));
			bid = (bid.size() == 1) ? "000" + bid : bid;
			bid = (bid.size() == 2) ? "00" + bid : bid;
			bid = (bid.size() == 3) ? "0" + bid : bid;

			for (int i = 0; i < card.size(); i++) {
				hand_to_int += charmap.at(card[i]);
				hand_to_int_joker += charmap_joker.at(card[i]);
			}
			int64_t result = stoll(hand_to_int + bid);
			order.push_back(result);
			result = stoll(hand_to_int_joker + bid);
			joker_order.push_back(result);

			vector<int> both_worths = evaluate_worth(card);
			worths.push_back(both_worths[0]);
			joker_worths.push_back(both_worths[1]);
		}
		file.close();
	}

	int first_total = calc_total(worths, order);
	int second_total = calc_total(joker_worths, joker_order);

	std::cout << "Part 1: " << first_total << '\n';
	std::cout << "Part 2: " << second_total << '\n';

	return 0;
}

