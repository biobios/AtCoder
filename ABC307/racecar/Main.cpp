#include <iostream>
#include <vector>
#include <string>

using namespace std;

int main() {

	uint64_t N;
	cin >> N;
	vector<string> sequenses{N, ""};

	for (size_t i = 0; i < N; i++) {
		cin >> sequenses[i];
	}

	for (size_t i = 0; i < N; i++) {
		for(size_t j = 0; j < N; j++){
			if (i == j) continue;

			string T = sequenses[i] + sequenses[j];

			bool isPalindrome = true;

			for (size_t k = 0; k < ((T.length() + 1) / 2); k++) {
				if (T[k] != T[T.size() - 1 - k]) {
					isPalindrome = false;
					break;
				}
			}

			if (isPalindrome) {
				cout << "Yes" << endl;
				return 0;
			}

		}
	}

	cout << "No" << endl;

	return 0;
}