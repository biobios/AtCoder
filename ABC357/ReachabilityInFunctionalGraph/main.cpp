#include <iostream>
#include <vector>
#include <cmath>
#include <set>

using namespace std;

int main()
{
	uint64_t N;
	cin >> N;
	vector<uint64_t> A(N);
	for (size_t i = 0; i < N; i++)
	{
		cin >> A[i];
		A[i]--;
	}
	set<uint64_t> unvisited;
	for (size_t i = 0; i < N; i++)
	{
		unvisited.insert(i);
	}
}