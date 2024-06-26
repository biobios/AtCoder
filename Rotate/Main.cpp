#include <iostream>
#include <vector>

using namespace std;

int main() {

	std::uint16_t N;
	cin >> N;

	vector<vector<std::uint8_t>> table{N, vector<std::uint8_t>(N, 0)};

	for (size_t i = 0; i < N; i++) {
		string str;
		cin >> str;
		for (size_t j = 0; j < N; j++) {
			table[i][j] = str.at(j) - '0';
		}
	}

	uint8_t buf = table[0][0];

	for (size_t i = 1; i < N; i++) {
		uint8_t buf2 = table[0][i];
		table[0][i] = buf;
		buf = buf2;
	}

	for (size_t i = 1; i < N; i++) {
		uint8_t buf2 = table[i][N - 1];
		table[i][N - 1] = buf;
		buf = buf2;
	}

	for (size_t i = 1; i < N; i++) {
		uint8_t buf2 = table[N - 1][N - 1 -i];
		table[N - 1][N - 1 - i] = buf;
		buf = buf2;
	}

	for (size_t i = 1; i < N; i++) {
		uint8_t buf2 = table[N - 1 - i][0];
		table[N - 1 - i][0] = buf;
		buf = buf2;
	}

	for (size_t i = 0; i < N; i++) {
		for (size_t j = 0; j < N; j++) {
			cout << static_cast<std::uint16_t>(table[i][j]);
		}
		cout << endl;
	}

	return 0;
}