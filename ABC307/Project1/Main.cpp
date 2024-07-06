#include <iostream>

using namespace std;

int main() {

	uint64_t N;
	cin >> N;
	for (size_t week = 0; week < N; week++) {
		uint64_t sum = 0;
		for (size_t day = 0; day < 7; day++) {
			uint64_t input;
			cin >> input;
			sum += input;
		}

		cout << sum << " ";
	}

	return 0;
}