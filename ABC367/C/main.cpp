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

    vector<uint64_t> R(N);
    uint64_t sum = 0;

    for (uint64_t i = 0; i < N; ++i)
    {
        cin >> R[i];
        sum += R[i];
    }

    deque<uint64_t> A;
    uint64_t current_sum = 0;

    for (size_t i = 0; i < N; i++)
    {
        A.push_back(1);
        current_sum += 1;
    }

    while (true)
    {
        if (current_sum % K == 0)
        {
            for (auto &a : A)
            {
                cout << a << " ";
            }
            cout << endl;
        }

        while (!A.empty() && A.back() == R[A.size() - 1])
        {
            A.pop_back();
            current_sum -= R[A.size()];
        }

        if (A.empty())
        {
            break;
        }

        A.back()++;
        current_sum++;

        while (A.size() < N)
        {
            A.push_back(1);
            current_sum += 1;
        }
    }

    return 0;
}