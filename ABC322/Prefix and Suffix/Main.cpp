#include <iostream>
#include <string>

using namespace std;

constexpr uint64_t NOT_SUFFIX = 0b01;
constexpr uint64_t NOT_PREFIX = 0b10;

int main() {
	uint64_t N, M;

	cin >> N >> M;

	string S, T;

	cin >> S >> T;

	uint64_t result = 0;

	auto itS = S.begin();
	auto itT = T.begin();

	while (itS != S.end()) {
		if (*itS != *itT) {
			result |= NOT_PREFIX;
			break;
		}
		itS++;
		itT++;
	}

	auto itS_r = S.rbegin();
	auto itT_r = T.rbegin();

	while (itS_r != S.rend()) {
		if (*itS_r != *itT_r) {
			result |= NOT_SUFFIX;
			break;
		}
		itS_r++;
		itT_r++;
	}

	cout << result << endl;

	return 0;
}