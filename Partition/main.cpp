#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main()
{
	uint64_t N;
	int64_t K;
	cin >> N >> K;
	vector<int64_t> A(N);

	int64_t sum = 0;

	for (size_t i = 0; i < N; i++)
	{
		cin >> A[i];
		sum += A[i];
	}

	sort(A.begin(), A.end());

	if (K > 0) {
		cout << "Yes" << endl;

		for (size_t i = 0; i < N; i++)
		{
			cout << A[i] << " ";
		}
		cout << endl;
		return 0;
	}

	if (sum < K)
	{
		cout << "No" << endl;
		return 0;
	}

	cout << "Yes" << endl;

	for (size_t i = 0; i < N; i++)
	{
		cout << A[N - i - 1] << " ";
	}

	cout << endl;

	return 0;

}