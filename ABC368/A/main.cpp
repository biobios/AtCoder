#include <iostream>
#include <vector>
#include <array>
#include <stack>
#include <queue>
#include <map>
#include <set>
#include <tuple>
#include <string>
#include <bitset>
#include <algorithm>
#include <utility>
#include <cmath>

using namespace std;

int main()
{
    uint64_t N, K;
    cin >> N >> K;

    vector<uint64_t> A(N);

    for (uint64_t i = 0; i < N; ++i)
    {
        cin >> A[i];
    }

    for (size_t i = N - K; i < 2 * N - K; ++i)
    {
        cout << A[i % N] << " ";
    }

    cout << endl;

    return 0;
}