#include <iostream>
#include <vector>
#include <string>

using namespace std;

constexpr uint64_t MOD = 998244353;

int main()
{
	uint64_t N, K;
	cin >> N >> K;

	string S;
	cin >> S;

	uint64_t count_question = 0;
	for (size_t i = 0; i < N; i++)
	{
		if (S[i] == '?')
			count_question++;
	}

	vector<uint64_t> ref(count_question, 0);
	uint64_t confirm = 0;

	for (size_t i = 0; i < N - K; i++)
	{
		for (size_t j = i; j < i + ((K + 1) / 2); j++)
		{
			if ((S[j] == 'A' || S[j] == 'B') && (S[j] == S[i + K - j - 1]))
				continue;

			if (S[j] == '?') {
				if (S[i + K - j - 1] == '?') {
					S[j] = 'C';
					S[i + K - j - 1] = 'C';
					confirm++;
				}
			}
			else if (S[j] == 'C') {

			}
		}
	}
}