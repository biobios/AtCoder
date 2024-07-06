#include <iostream>
#include <vector>
#include <array>
#include <cmath>

using namespace std;

int main()
{
	uint64_t M, N;
	cin >> M >> N;

	vector<uint64_t> X(M);

	for (size_t i = 0; i < M; i++)
	{
		cin >> X[i];
		X[i]--;
	}

	vector<array<uint64_t, 3>> combinations(M, {M - 1, 1, 0});

	for (size_t i = 0; i < M; i++) {
		if (i == X[i]) {
			combinations[i][1] = 0;
			combinations[i][2] = 1;
		}
		else {
			combinations[i][0] = 1;
			combinations[i][1] = 0;
		}
	}

	for (size_t i = 1; i < N; i++)
	{
		vector<array<uint64_t, 3>> combinations_editing = combinations;

		for (size_t j = 0; j < M; j++)
		{
			uint64_t x = X[j];

			combinations_editing[j][0] = combinations[j][0] * (M - 1);

			if (x == j){
				combinations_editing[j][2] = combinations[j][2] * (M - 1) + combinations[j][0];
			}
			else {
				combinations_editing[j][2] = combinations[j][2] * (M - 1) + combinations[j][1];
				combinations_editing[j][1] = combinations[j][1] * M + combinations[j][0];
			}
		}

		combinations = combinations_editing;
	}

	vector<uint64_t> X_count(M, pow(M, N)
	
}