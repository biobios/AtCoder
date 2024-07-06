#include <iostream>
#include <vector>

using namespace std;

int main() {
	uint32_t N;
	cin >> N;
	vector<bool> once(N, false);
	vector<bool> twice(N, false);

	for (size_t i = 0; i < 3 * N; i++) {
		uint32_t input;
		cin >> input;

		if (!twice[input - 1]) {
			if (once[input - 1]) {
				cout << input << " ";
				twice[input - 1] = true;
			}
			else {
				once[input - 1] = true;
			}
		}
	}
	return 0;
}