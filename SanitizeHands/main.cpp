#include <iostream>

using namespace std;

int main()
{
	uint64_t N, M;
	cin >> N >> M;

	for (size_t i = 0; i < N; i++)
	{
		uint64_t H;
		cin >> H;

		if (M < H)
		{
			cout << i << endl;
			return 0;
		}

		M -= H;
	}

	cout << N << endl;
	return 0;
}