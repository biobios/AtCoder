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
	}

	//29Ç…ëŒÇµÇƒåƒÇŒÇÍÇ»Ç¢
	void bubbleDown(array<uint8_t, 2> index) {
		uint16_t num = data[index[0]][index[1]];
		uint16_t downLeft = data[index[0] + 1][index[1]];
		uint16_t downRight = data[index[0] + 1][index[1] + 1];
		while (downLeft < num || downRight < num) {
			if (downLeft > downRight) {//âEÇ∆åä∑
				data[index[0]][index[1]] = downRight;
				data[index[0] + 1][index[1] + 1] = num;

				array<array<uint8_t, 2>, 2> ope = { index, {index[0] + 1, index[1] + 1} };
				opeHistory.push_back(ope);

				index[0]++;
				index[1]++;
			}
			else {//ç∂Ç∆åä∑
				data[index[0]][index[1]] = downLeft;
				data[index[0] + 1][index[1]] = num;

				array<array<uint8_t, 2>, 2> ope = { index, {index[0] + 1, index[1]} };
				opeHistory.push_back(ope);

				index[0]++;
			}
			if (index[0] == N - 1)break;
			downLeft = data[index[0] + 1][index[1]];
			downRight = data[index[0] + 1][index[1] + 1];
		}
	}

	void sort() {
		for (uint8_t i = N - 1; i != 0; i--) {
			for (uint8_t j = 0; j < i; j++) {
				bubbleDown({ static_cast<uint8_t>(i - 1), j });
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

	for (uint8_t i = 0; i < N; i++) {
		for (uint8_t j = 0; j < i + 1; j++) {
			uint16_t input;
			cin >> input;
			pyram.addData(input, { i, j });
		}
	}

	pyram.sort();
	pyram.dumpHistory();

	return 0;
}