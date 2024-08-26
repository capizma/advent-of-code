// https://adventofcode.com/2023/day/4
// Day 4 (complete)

#include <iostream>
#include <fstream>
#include <string>
#include <regex>
#include <iomanip> 
#include <chrono>
using namespace std;

int main() {
	string ln;
	string line;
	ifstream file("input.txt");
	int total = 0;
	int power_score = 0;
	vector<string> cards = {};
	vector<int> powerslist = {};
	int copieslist[203][2];
	int secondtotal = 0;

	if (file.is_open()) {
		while (getline(file, ln)) {
			cards.push_back(ln);
		}
		int original_size = cards.size();

		for (int card = 0; card < original_size; card++) {
			line = cards[card];
			size_t split1 = line.find(':') + 2;
			size_t split2 = line.find('|');
			string winning = ' ' + line.substr(split1, split2 - split1);
			string numbers = ' ' + line.substr(split2, line.size() - split2) + ' ';
			string digit = " ";
			power_score = 0;
			bool found = false;
			for (int i = 0; i < numbers.size(); i++) {
				if (numbers[i] >= 48 && numbers[i] <= 57) {
					digit.push_back(numbers[i]);
				}
				else {
					if (digit != " ") {
						int it;
						digit.push_back(' ');
						it = winning.find(digit);
						if (it != -1) {
							power_score += 1;
							found = true;
						}
					}
					digit = " ";
				}
			}
			powerslist.push_back(power_score);
			total += floor(pow(2, power_score) / 2);
		}
		file.close();
	}

	for (int i = 0; i < powerslist.size(); i++) {
		copieslist[i][0] = powerslist[i];
		copieslist[i][1] = 1;
	}

	for (int i = 0; i < powerslist.size(); i++) {
		for (int j = i + 1; j < i + copieslist[i][0] + 1; j++) {
			int quant = 1 * copieslist[i][1];
			copieslist[j][1] += quant;
			secondtotal += quant;
		}
	}

	secondtotal += powerslist.size();

	std::cout << "Part 1: " << total << '\n';
	std::cout << "Part 2: " << secondtotal << '\n';

	system("pause");
	return 0;
}
