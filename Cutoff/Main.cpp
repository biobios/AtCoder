#include <iostream>
#include <vector>

using namespace std;

int main() {

	uint64_t N, X;

	cin >> N >> X;

	uint64_t sum = 0;
	uint64_t min = ~0;
	uint64_t max = 0;

	for (uint64_t i = 0; i < N - 1; i++) {
		uint64_t A;
		cin >> A;

		sum += A;

		if(A < min)
			min = A;

		if(A > max)
			max = A;
	}

	uint64_t result = sum - min - max;
	if ((result >= X) || (X - result <= min)) {
		cout << 0 << endl;
	}
	else if (X - result <= max) {
		cout << X - result << endl;
	}
	else {
		cout << -1 << endl;
	}

	return 0;
}