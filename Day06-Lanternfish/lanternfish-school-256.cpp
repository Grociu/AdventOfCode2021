#include <map>
#include <vector>
#include <fstream>
#include <iostream>

void parse_input(std::ifstream& ifs, std::map<int, long long int>& data) {
	char c;
	while (ifs >> c) {
		if (isdigit(c)) {
			ifs.putback(c);
			int num;
			ifs >> num;
			data[num]++;
		}
	}
}

long long int sum_of_fish(const std::map<int, long long int>& data) {
	long long int sum{ 0 };
	for (const auto& d : data) sum = sum + d.second;
	return sum;
}


int main() {

	// prepare a stream to read input
	std::string filename = "Input.txt";
	std::ifstream ifs{ filename };

	// this will keep track of the contents of the fish school
	// keys are days until the fish will breed
	// values are the number if fish with that 
	const int RECOVERY_PERIOD = 6;
	const int MATURITY_PERIOD = 2;
	const int MAX_VALUE = RECOVERY_PERIOD + MATURITY_PERIOD;
	std::map <int, long long int> school;
	for (int i = 0; i <= MAX_VALUE; i++) school[i] = 0;

	// read input into the school map;
	parse_input(ifs, school);

	const int NUM_OF_DAYS = 256;
	// each day
	for (int day = 1; day <= NUM_OF_DAYS; day++) {
		// start by creating a vector of the school state in the morning
		std::vector<long long int> initial_state;
		for (const auto& s : school) initial_state.push_back(s.second);
		// then for each index (corresponding to 'days to breed' set the value in school of breed
		// iterate in reverse so '0' is processed last(!!)
		for (int i = initial_state.size() - 1; i >= 0; i--) {
			switch (i) {
			case 0: {
				school[RECOVERY_PERIOD + MATURITY_PERIOD] = initial_state[i]; // multiply
				school[RECOVERY_PERIOD] = school[RECOVERY_PERIOD] + initial_state[i]; // recover // this is added to previously processed case 6:
				break;
			}
			default: school[i - 1] = initial_state[i];
			}
		}
	}

	// calculate number of fish after 256 days
	long long int num_of_fish = sum_of_fish(school);

	// output to console
	std::cout << "Number of fish: " << num_of_fish << std::endl;

}