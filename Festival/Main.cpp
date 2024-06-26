#include <iostream>

using namespace std;

int main() {
	uint64_t N, M;

	cin >> N >> M;

	uint64_t read_position = 0;
	int64_t val = -1;
	
	for (int64_t i = 1; i <= N; i++) {
		while (val < i) {
			cin >> val;
		}
		cout << val - i << endl;
	}

	return 0;
}