#include <iostream>

using namespace std;

int main()
{
	uint64_t N;
	cin >> N;

	uint64_t prev_2 = 0;
	uint64_t prev_1 = 0;
	uint64_t result = 0;

	for (size_t i = 0; i < 2 * N; i++) {
		uint64_t A;
		cin >> A;

		if (A == prev_2)
			result++;

		prev_2 = prev_1;
		prev_1 = A;
	}

	cout << result << endl;
	return 0;
}