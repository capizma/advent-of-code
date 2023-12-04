#include <iostream>
#include <fstream>
#include <string>
#include <regex>
#include <vector>
#include <unordered_map>
#include <iomanip> 
#include <chrono>
using namespace std;

static int unnecessary_hashing(float c) {
	//converts the first char to an index for vec (3x faster than mapping function)
	unsigned int ind = (int) abs(ceil(((c - 114) + 1) / 5)) - 1;
	return ind;
}

int main() {
	//start the clock
	auto clock_start = chrono::high_resolution_clock::now();
	ios_base::sync_with_stdio(false);

	//setting main outputs and file input
	string line;
	ifstream file ("input.txt");
	int total = 0;
	int powers_total = 0;

	if (file.is_open()) {
		while (getline(file, line)) {

			// read in input line by line and clean it a bit
			size_t start = line.find(':');
			int id = stoi(line.substr(5,start-5));
			string l = line.substr(start + 2, line.size() - (start + 2));
			bool valid = true;
			int pos = 0;
			vector<int> vec = {0,0,0};

			for (int i = 0; i < l.size() + 1; i++) {
				// if we've reached a delimiter or are past the final one
				if (l[i] == ',' || l[i] == ';' || i == l.size()) {
					string field = l.substr(pos, i - pos);
					size_t delim = field.find(' ');
					int result = stoi(field.substr(0, delim));
					string colour = field.substr(delim + 1, field.size() - delim);

					//get first char int value and hash to index vector
					int lookup = unnecessary_hashing(colour[0]);
					if (vec[lookup] < result) {
						vec[lookup] = result;
					}

					//limit is 12 more than the indexes for RGB, so i just add 12
					if (valid == true && result > lookup+12) {
						valid = false;
					}

					//if we have another delimiter, skip any whitespace iterations
					if (i < l.size()) {
						i += 2;
						pos = i;
					}
				}
			}
			// add to powers solution and add to valid games if game is valid
			powers_total += (vec[0] * vec[1] * vec[2]);
			total += (valid == true) ? id : 0;
		}
		file.close();
	}
	std::cout << total << '\n';
	std::cout << powers_total << '\n';

	//stop the clock
	auto clock_end = chrono::high_resolution_clock::now();
	double time_taken = chrono::duration_cast<chrono::nanoseconds>(clock_end - clock_start).count();
	time_taken *= 1e-3;
	// ~400us
	cout << "Time taken by program is : " << time_taken;
	cout << " us" << endl;

	system("pause");
	return 0;
}
