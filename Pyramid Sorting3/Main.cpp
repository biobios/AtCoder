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

	void sortRight() {
		for (uint8_t level = 1; level < N; level++) {
			for (uint8_t j = 0; j < level + 1; j++) {
				uint16_t num = data[level][j];
				array<uint8_t, 2> index = {level, j};
				array<uint8_t, 2> parentIndex;
				uint16_t parentNum;
				do {
					if (index[0] == index[1]) {
						parentIndex = { static_cast<uint8_t>(index[0] - 1), static_cast<uint8_t>(index[1] - 1)};
						parentNum = data[index[0] - 1][index[1] - 1];
					}
					else {
						parentIndex = { static_cast<uint8_t>(index[0] - 1), index[1]};
						parentNum = data[index[0] - 1][index[1]];
					}
					if (parentNum < num)break;

					data[parentIndex[0]][parentIndex[1]] = num;
					data[index[0]][index[1]] = parentNum;

					opeHistory.push_back({ index, parentIndex });
					index = parentIndex;

				} while (index[0] != 0);
			}
		}
	}

	void sortLeft() {
		for (uint8_t level = 1; level < N; level++) {
			for (uint8_t j = 0; j < level + 1; j++) {
				uint16_t num = data[level][j];
				array<uint8_t, 2> index = { level, j };
				array<uint8_t, 2> parentIndex;
				uint16_t parentNum;
				do {
					if (index[1] == 0) {
						parentIndex = { static_cast<uint8_t>(index[0] - 1), index[1]};
						parentNum = data[index[0] - 1][index[1]];
					}
					else {
						parentIndex = { static_cast<uint8_t>(index[0] - 1), static_cast<uint8_t>(index[1] - 1)};
						parentNum = data[index[0] - 1][index[1] - 1];
					}
					if (parentNum < num)break;

					data[parentIndex[0]][parentIndex[1]] = num;
					data[index[0]][index[1]] = parentNum;

					opeHistory.push_back({ index, parentIndex });
					index = parentIndex;

				} while (index[0] != 0);
			}
		}
	}

	void sort() {
		size_t prev_historySize = 0;
		do
		{
			prev_historySize = opeHistory.size();

			sortRight();
			sortLeft();

		} while (prev_historySize != opeHistory.size());
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