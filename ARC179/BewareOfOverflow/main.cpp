#include <iostream>
#include <stack>
#include <vector>
#include <algorithm>
#include <map>

using namespace std;

map<pair<uint64_t, uint64_t>, uint64_t> memo;

bool lessThan(uint64_t a, uint64_t b)
{

	if (memo.find({ a, b }) != memo.end())
	{
		return memo[{a, b}] == 1;
	}
	else if (memo.find({ b, a }) != memo.end())
	{
		return memo[{b, a}] == 0;
	}

	cout << "? " << a << " " << b << endl;
	cout.flush();
	uint64_t c;
	cin >> c;

	if(c == -1)
		exit(0);

	memo[{a, b}] = c;
	memo[{b, a}] = 1 - c;

	return c == 1;
}

void insert(vector<uint64_t>& A, uint64_t x)
{
	auto it = lower_bound(A.begin(), A.end(), x, lessThan);

	A.insert(it, x);
}

uint64_t merge(uint64_t a, uint64_t b)
{
	cout << "+ " << a << " " << b << endl;
	cout.flush();

	int64_t c;
	cin >> c;

	if(c == -1)
		exit(0);

	return c;
}

int main()
{
	uint64_t N;
	cin >> N;

	vector<uint64_t> A(N);

	for (size_t i = 0; i < N; i++) {
		A[i] = i + 1;
	}


	sort(A.begin(), A.end(), lessThan);
	
	while (A.size() > 1)
	{
		uint64_t min = A[0];
		uint64_t max = A[A.size() - 1];

		A.erase(A.begin());
		A.erase(A.end() - 1);

		uint64_t m = merge(min, max);

		insert(A, m);
	}

	cout << "!" << endl;
	cout.flush();

	return 0;
}