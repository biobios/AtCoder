#include <iostream>
#include <vector>

using namespace std;



int main() {

	uint64_t N;
	cin >> N;

	int64_t prev[2];

	prev[0] = 0;
	prev[1] = 0;

	for (size_t i = 0; i < N; i++) {
		int64_t X, Y;
		cin >> X >> Y;

		int64_t poisoning_max = prev[1];
		int64_t healthy_max = prev[0];

		if (X != 0) {
			if (poisoning_max < prev[0] + Y) {
				poisoning_max = prev[0] + Y;
			}
		}
		else {
			if (healthy_max < prev[0] + Y) {
				healthy_max = prev[0] + Y;
			}
			if (healthy_max < prev[1] + Y) {
				healthy_max = prev[1] + Y;
			}
		}

		prev[0] = healthy_max;
		prev[1] = poisoning_max;

	}

	int64_t result = 0;
	if (prev[1] < prev[0]) {
		result = prev[0];
	}
	else {
		result = prev[1];
	}

	cout << result << endl;

	return 0;
}