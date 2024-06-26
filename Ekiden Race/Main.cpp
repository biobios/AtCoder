#include <iostream>
#include <vector>

using namespace std;

int main() {
	int64_t T;
	cin >> T;

	for (size_t i = 0; i < T; i++) {
		uint64_t N;
		cin >> N;
		vector<int64_t> sequence(N);
		

		for (size_t j = 0; j < N; j++) {
			cin >> sequence[j];
		}

		int64_t currentMinimum = ~(static_cast<uint64_t>(0)) >> 1;
		int64_t prizes = 0;
		for (auto it = sequence.rbegin(); it != sequence.rend(); it++) {
			if (currentMinimum > *it) {
				prizes++;
				currentMinimum = *it;
			}
		}

		cout << prizes << endl;
		
	}

	return 0;
}