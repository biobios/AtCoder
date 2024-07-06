#include <iostream>
#include <vector>

using namespace std;

class Test
{
	vector<uint64_t> keys;
	char test_result;

public:
	Test() {
		uint64_t C;
		cin >> C;

		keys.resize(C);

		for (size_t i = 0; i < C; i++)
		{
			cin >> keys[i];
			keys[i]--;
		}

		cin >> test_result;
	}

	bool IsCorrect(const vector<bool>& keys_correct, uint64_t K) const
	{
		uint64_t correct_key_count = 0;

		for (size_t i = 0; i < keys.size(); i++)
		{
			if (keys_correct[keys[i]])
			{
				correct_key_count++;
			}
		}

		if (correct_key_count >= K && test_result == 'o') {
			return true;
		}
		else if (correct_key_count < K && test_result == 'x') {
			return true;
		}
		else {
			return false;
		}
	}
};

int main()
{
	uint64_t N, M, K;
	cin >> N >> M >> K;

	uint64_t possible_combination_count = 1 << N;
	vector<bool> keys_correct(N, false);
	vector<Test*> tests(M, nullptr);

	for (size_t i = 0; i < M; i++)
	{
		tests[i] = new Test();
	}

	while (true)
	{

		// keys_correctを使ってテストを試す
		for (size_t i = 0; i < M; i++)
		{
			if (!tests[i]->IsCorrect(keys_correct, K))
			{
				possible_combination_count--;
				break;
			}
		}

		// keys_correctを全通り試す
		for (size_t i = 0;; i++)
		{
			if (keys_correct[i])
			{
				keys_correct[i] = false;
				if (i == N - 1)
				{
					// 全通り試した
					cout << possible_combination_count << endl;
					return 0;
				}
			}
			else
			{
				keys_correct[i] = true;
				break;
			}
		}
	}

	return 0;

}