#include <iostream>
#include <vector>
#include <array>

using namespace std;

class Pyramid {
	static constexpr uint64_t N = 30;
	static constexpr uint64_t numElements = N * (N - 1) / 2;
	vector<vector<uint16_t>> data;
	vector<array<array<uint8_t, 2>, 2>> opeHistory;
public:
	Pyramid() : data{ N } {
		for (size_t i = 0; i < N; i++) {
			data[i] = vector<uint16_t>(i + 1);
		}
	}

	void addData(uint16_t num, array<uint8_t, 2> index) {
		data[index[0]][index[1]] = num;
		uint16_t topLeft = 0;
		uint16_t topRight = 0;
		if (index[1] > 0 && index[0] > 0) {
			topLeft = data[index[0] - 1][index[1] - 1];
		}
		if (index[0] != index[1]) {
			topRight = data[index[0] - 1][index[1]];
		}
		while (topLeft > num || topRight > num) {
			if (topLeft > topRight) {//ç∂Ç∆åä∑
				uint16_t buf = data[index[0] - 1][index[1] - 1];
				data[index[0] - 1][index[1] - 1] = num;
				data[index[0]][index[1]] = buf;

				array<array<uint8_t, 2>, 2> ope = { index, {index[0] - 1, index[1] - 1} };
				opeHistory.push_back(ope);

				index[0]--;
				index[1]--;

			}
			else {//âEÇ∆åä∑
				uint16_t buf = data[index[0] - 1][index[1]];
				data[index[0] - 1][index[1]] = num;
				data[index[0]][index[1]] = buf;

				array<array<uint8_t, 2>, 2> ope = { index, {index[0] - 1, index[1]} };
				opeHistory.push_back(ope);

				index[0]--;
			}

			topLeft = 0;
			topRight = 0;
			if (index[1] > 0 && index[0] > 0) {
				topLeft = data[index[0] - 1][index[1] - 1];
			}
			if (index[0] != index[1]) {
				topRight = data[index[0] - 1][index[1]];
			}
		}
	}

	void dumpHistory() {

		cout << opeHistory.size() << endl;

		for (size_t i = 0; i < opeHistory.size(); i++) {
			cout << static_cast<uint16_t>(opeHistory[i][0][0]) << " "
				<< static_cast<uint16_t>(opeHistory[i][0][1]) << " "
				<< static_cast<uint16_t>(opeHistory[i][1][0]) << " "
				<< static_cast<uint16_t>(opeHistory[i][1][1]) << endl;
		}
	}
};

int main() {

	Pyramid pyram;

	uint64_t N = 30;
	uint64_t numElements = N * (N - 1) / 2;

	for (uint8_t i = 0; i < N; i++) {
		for (uint8_t j = 0; j < i + 1; j++) {
			uint16_t input;
			cin >> input;
			pyram.addData(input, { i, j });
		}
	}

	pyram.dumpHistory();

	return 0;
}