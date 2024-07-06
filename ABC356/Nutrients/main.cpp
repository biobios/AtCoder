#include <iostream>
#include <vector>

using namespace std;

int main()
{
	uint64_t N, M;
	cin >> N >> M;

	vector<uint64_t> nutrients_sum(M);
	vector<uint64_t> nutrients_threshold(M);

	for (size_t i = 0; i < M; i++)
	{
		cin >> nutrients_threshold[i];
	}

	for (size_t i = 0; i < N; i++)
	{
		for (size_t j = 0; j < M; j++) {
			uint64_t X;
			cin >> X;

			nutrients_sum[j] += X;
		}
	}

	bool goal_reached = true;

	for (size_t i = 0; i < M; i++)
	{
		if (nutrients_sum[i] < nutrients_threshold[i])
		{
			goal_reached = false;
			break;
		}
	}

	if (goal_reached) {
		cout << "Yes" << endl;
	}
	else {
		cout << "No" << endl;
	}

	return 0;
}