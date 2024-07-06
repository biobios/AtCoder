#include <iostream>
#include <vector>
#include <string>
#include <array>

using namespace std;

int main() {

	uint64_t HA, WA;
	cin >> HA >> WA;
	vector<array<uint8_t, 2>> sheetA{};

	for (size_t i = 0; i < HA; i++) {
		string input;
		cin >> input;
		for (size_t j = 0; j < WA; j++) {
			if (input[j] == '#') {
				array<uint8_t, 2> point = { j, i };

				sheetA.push_back(point);
			}
		}
	}

	uint64_t HB, WB;
	cin >> HB >> WB;
	vector<array<uint8_t, 2>> sheetB{};

	for (size_t i = 0; i < HA; i++) {
		string input;
		cin >> input;
		for (size_t j = 0; j < WA; j++) {
			if (input[j] == '#') {
				array<uint8_t, 2> point = { j, i };

				sheetB.push_back(point);
			}
		}
	}

	uint64_t HX, WX;
	cin >> HX >> WX;
	vector<array<uint8_t, 2>> sheetX{};

	for (size_t i = 0; i < HA; i++) {
		string input;
		cin >> input;
		for (size_t j = 0; j < WA; j++) {
			if (input[j] == '#') {
				array<uint8_t, 2> point = { j, i};

				sheetX.push_back(point);
			}
		}
	}

	for (size_t x = 0; x < sheetX.size(); x++) {
		int64_t biasAX = static_cast<int64_t>(sheetX[x][0]) - sheetA[0][0];
		int64_t biasAY = static_cast<int64_t>(sheetX[x][1]) - sheetA[0][1];

		bool isOverlap = true;
		for (size_t a = 0; a < sheetA.size(); a++) {
			bool isExist = false;
			for (size_t ax = 0; ax < sheetX.size(); ax++) {

			}
		}

	}

	return 0;
}