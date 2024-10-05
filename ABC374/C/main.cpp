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

    uint64_t A = 0;
    uint64_t B = 0;

    vector<uint64_t> K(N);

    for (size_t i = 0; i < N; ++i)
    {
        cin >> K[i];
    }

    sort(K.rbegin(), K.rend());

    stack<bool> group_A;

    uint64_t result = -1ull;

    while (true)
    {
        while (group_A.size() < N)
        {
            group_A.push(true);
            A += K[group_A.size() - 1];
        }

        result = min(result, max(A, B));

        while (!group_A.empty() && group_A.top() == false)
        {
            group_A.pop();
            B -= K[group_A.size()];
        }

        if (group_A.empty())
        {
            break;
        }

        group_A.pop();
        A -= K[group_A.size()];

        group_A.push(false);
        B += K[group_A.size() - 1];
    }

    cout << result << endl;

    return 0;
}