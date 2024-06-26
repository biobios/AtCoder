#include <iostream>
#include <vector>
#include <array>
#include <algorithm>

using namespace std;

bool compare(const array<uint64_t, 2>& left, const array<uint64_t, 2>& right) {
	return left[0] < right[0];
}

int main() {

	uint64_t N, K;
	cin >> N >> K;

	vector<array<uint64_t, 2>> table;

	for (size_t i = 0; i < N; i++) {
		uint64_t a, b;
		cin >> a >> b;

		table.push_back({ a , b });
	}

	std::sort(table.begin(), table.end(), compare);

	uint64_t sum = 0;
	for (size_t i = 0; i < N; i++) {
		sum += table[i][1];
	}
	if (sum <= K) {
		cout << 1 << endl;
		return 0;
	}
	uint64_t day = 0;
	for (size_t i = 0; i < N; i++) {
		sum -= table[i][1];

		if (sum <= K) {
			day = table[i][0] + 1;
			break;
		}
	}

	cout << day << endl;

	return 0;
}