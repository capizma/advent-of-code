#include <iostream>
#include <fstream>
#include <string>
#include <regex>
#include <iomanip> 
#include <chrono>
using namespace std;

//commenting this now i realised i didn't do part 2, i might come back to it :D

int main() {
	//start the clock
	auto clock_start = chrono::high_resolution_clock::now();
	ios_base::sync_with_stdio(false);

	//setting up inputs/regex replace
	string line;
	ifstream file ("input.txt");
	unsigned int total = 0;
	regex re ("\\D"); 

	if (file.is_open()) {
		while (getline(file, line)) {
			//remove everything that's not a digit
			line = std::regex_replace(line, re, "");
			//convert chars to decimal and -48 for int, concat the two
			int begin = line[0];
			int end = line.back();
			total += (begin-48)*10+(end-48);
		}
		file.close();
	}
	std::cout << total << '\n';

	//stop the clock
	auto clock_end = chrono::high_resolution_clock::now();
	double time_taken = chrono::duration_cast<chrono::nanoseconds>(clock_end - clock_start).count();
	time_taken *= 1e-3;
	// ~7ms
	cout << "Time taken by program is : " << time_taken;
	cout << " us" << endl;

	system("pause");
	return 0;
}