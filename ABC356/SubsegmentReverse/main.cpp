#include <iostream>

using namespace std;

int main()
{
	uint64_t N, L, R;
	cin >> N >> L >> R;

	for (size_t i = 1; i < L; i++)
	{
		cout << i << " ";
	}

	for (size_t i = R; i >= L; i--)
	{
		cout << i << " ";
	}

	for (size_t i = R + 1; i <= N; i++)
	{
		cout << i << " ";
	}

	return 0;
}