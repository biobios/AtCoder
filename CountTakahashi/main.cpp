#include <iostream>

using namespace std;

int main()
{
	uint64_t N;
	cin >> N;

	uint64_t result = 0;

	for (size_t i = 0; i < N; i++)
	{
		string S;
		cin >> S;

		if (S == "Takahashi")
		{
			result++;
		}
	}

	cout << result << endl;
	return 0;
}