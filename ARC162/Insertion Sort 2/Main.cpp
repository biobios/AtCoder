#include <iostream>
#include <list>
#include <vector>

using namespace std;

int main() {

	uint64_t N;
	cin >> N;
	list<uint64_t> sequenceP;
	uint64_t prev = ~0;
	uint64_t numInverse = 0;
	for (size_t i = 0; i < N; i++) {
		uint64_t input;
		cin >> input;
		if (prev - 1 == input) {
			numInverse++;
		}
		sequenceP.push_back(input);
	}

	if (numInverse % 2 != 0) {
		cout << "No" << endl;
	}
	else {
		cout << "Yes" << endl;
		vector<vector<uint64_t>> result(2);
		auto itr = sequenceP.begin();
		auto end = sequenceP.end();
		end--;
		uint64_t index = 1;
		while (itr != end) {
			uint64_t prev = *itr;
			itr++;
			index++;
			uint64_t current = *itr;
			uint64_t swapElem[2];
			if (prev > current) {
				uint64_t nukidasi = index;
				swapElem[0] = current;
				itr = sequenceP.erase(itr);
				swapElem[1] = *itr;
				itr = sequenceP.erase(itr);
				itr--;
				index--;
				
				while (*itr > swapElem[0]) {
					itr--;
					index--;
				}
				itr++;

				uint64_t ire = index;

				itr = sequenceP.insert(itr, swapElem[0]);
				itr++;
				itr = sequenceP.insert(itr, swapElem[1]);

				itr--;
				index++;

				result[0].push_back(nukidasi);
				result[1].push_back(ire);

			}
			end = sequenceP.end();
			end--;
		}


		cout << result[0].size();
		for (size_t i = 0; i < result[0].size(); i++) {
			cout << result[0][i] << " " << result[1][i] << endl;
		}

	}

	return 0;
}