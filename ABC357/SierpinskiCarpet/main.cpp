#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

int main()
{
	uint64_t N;
	cin >> N;

	uint64_t size = pow(3, N);

	for (size_t i = 0; i < size; i++) {
		uint64_t level_i = 6;

		for (; level_i > 0; level_i--) {
			uint64_t pow_3 = pow(3, level_i);
			uint64_t pow_3_1 = pow(3, level_i - 1);
			uint64_t i_mod = i % pow_3;

			if (i_mod < pow_3_1 || 2 * pow_3_1 <= i_mod) continue;
			else break;
		}

		for (size_t j = 0; j < size; j++) {
			uint64_t level = level_i;

			for (; level > 0; level--) {
				uint64_t pow_3 = pow(3, level);
				uint64_t pow_3_1 = pow(3, level - 1);
				uint64_t j_mod = j % pow_3;
				uint64_t i_mod = i % pow_3;

				if (j_mod < pow_3_1 || 2 * pow_3_1 <= j_mod ||
					i_mod < pow_3_1 || 2 * pow_3_1 <= i_mod) continue;
				else break;
			}

			if (level == 0) cout << "#";
			else cout << ".";

		}

		cout << endl;
	}

	return 0;
}