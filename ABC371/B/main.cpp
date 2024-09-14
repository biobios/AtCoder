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
    uint64_t N, M;
    cin >> N >> M;

    vector<bool> named_taro(N, false);

    for (size_t i = 0; i < M; ++i)
    {
        uint64_t A;
        char B;
        cin >> A >> B;

        if (B == 'F')
        {
            cout << "No" << endl;
            continue;
        }

        if (named_taro[A - 1])
        {
            cout << "No" << endl;
            continue;
        }

        named_taro[A - 1] = true;
        cout << "Yes" << endl;
    }

    return 0;
}