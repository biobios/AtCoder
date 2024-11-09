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

    string S;
    cin >> S;

    uint64_t seq_count = 0;
    uint64_t result = 0;

    for (char c : S)
    {
        if (c == 'O')
        {
            seq_count++;
            if (seq_count >= K)
            {
                result++;
                seq_count = 0;
            }
        }
        else
        {
            seq_count = 0;
        }
    }

    cout << result << endl;

    return 0;
}