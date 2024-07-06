#include <iostream>

using namespace std;

const char TEN = '9' + 1;

void carryUp(string& number, uint64_t order) {
	size_t index = number.length() - order - 1;
	
	if (index == -1) {
		number = (char)(number[0] + 1) + number;
		return;
	}
	
	char next;
	if (index == 0) {
		next = TEN;
	}
	else {
		next = number[index - 1];
	}

	if (number[index] + 1 >= next) {
		if(order == 0)
			number[index] = '0';
		else
			number[index] = number[index + 1] + 1;
		carryUp(number, order + 1);
	}
	else {
		number[index]++;
	}
}

int main() {

	uint64_t K;
	cin >> K;

	string result = "1";

	for (uint64_t i = 1; i < K; i++) {
		carryUp(result, 0);
	}

	cout << result << endl;

	return 0;
}