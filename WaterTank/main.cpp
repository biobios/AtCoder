#include <iostream>
#include <vector>
#include <stack>
#include <array>

using namespace std;

int main()
{
	uint64_t N;
	cin >> N;

	vector<uint64_t> H(N);
	for (size_t i = 0; i < N; i++)
	{
		cin >> H[i];
	}

	vector<uint64_t> A(N + 1);
	stack<array<uint64_t, 3>> S;

	for (int64_t i = 0; i < N; i++)
	{
		
		while (!S.empty() && S.top()[1] < H[i])
		{
			S.pop();
		}
		

		uint64_t count;
		if (S.empty())
			count = (i + 1) * H[i];
		else
			count = (i - S.top()[0]) * H[i] + S.top()[2];

		//uint64_t max = 0;
		//for (int64_t j = i - 1; j >= 0; j--) {
		//	if (H[j] > H[i])
		//		break;

		//	if(H[j] > max)
		//		max = H[j];

		//	count += H[i] - max;
		//}

		cout << count + 1 << " ";
		S.push({ (uint64_t)i, H[i], count });
	}

	cout << endl;
	return 0;
}