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
    uint64_t N;
    cin >> N;

    vector<uint64_t> A(N);

    for (size_t i = 0; i < N; ++i)
    {
        cin >> A[i];
        A[i] -= 1;
    }

    vector<size_t> appeared(N, false);
    vector<uint64_t> kind_count(N + 1, 0);

    uint64_t sum = 0;

    for (size_t i = 0; i < N; ++i)
    {
        if (appeared[A[i]])
        {
            kind_count[i + 1] = kind_count[i];
        }
        else
        {
            appeared[A[i]] = true;
            kind_count[i + 1] = kind_count[i] + 1;
        }

        sum += kind_count[i + 1] * (i + 1);
    }

    vector<size_t> prev_appeared_index(N, 0);

    for (size_t i = 0; i < N; ++i)
    {

        sum -= N - i;

        if (prev_appeared_index[A[i]] != 0)
        {
            sum -= i - prev_appeared_index[A[i]];
        }

        prev_appeared_index[A[i]] = i;
    }

    cout << sum << endl;

    return 0;
}