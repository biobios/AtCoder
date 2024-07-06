#include <iostream>
#include <cstdint>

using namespace std;

int main() {

	uint64_t result = 0;

	for (size_t i = 0; i < 64; i++) {
		uint64_t input;
		cin >> input;
		result = result | (input << i);
	}

	cout << result << endl;

	return 0;
}