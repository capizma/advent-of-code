// https://adventofcode.com/2023/day/6
// Day 6 (complete)

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
using namespace std;

int64_t gametime = 0;
int64_t record = 0;
int total = 1;
int64_t secondtotal = 0;
vector<int64_t> ls = { 59,543,68,1020,82,1664,74,1022,59688274,543102016641022};

int main()
{
	for (int64_t c = 0; c < ls.size() - 1; c += 2) {
		int64_t pos = 0;
		gametime = ls[c];
		for (int i = 1; i < gametime; i++) {
			if (((gametime - i) * i) > ls[c + 1]) {
				pos = i;
				break;
			}
		}
		int64_t games = 0;
		games = (gametime + 1) - (pos * 2);

		if (c != ls.size() - 2) {
			total*= games;
		}
		else {
			secondtotal = games;
		}
	}
	std::cout << "Part 1: " << total << '\n';
	std::cout << "Part 2: " << secondtotal << '\n';

	return 0;
}
