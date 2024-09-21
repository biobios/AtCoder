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
    uint64_t M;
    cin >> M;

    vector<uint64_t> A;

    while (M > 0)
    {
        uint64_t pow_3_a = 1;
        uint64_t a = 0;

        while (pow_3_a * 3 <= M)
        {
            pow_3_a *= 3;
            a++;
        }

        A.push_back(a);
        M -= pow_3_a;
    }

    cout << A.size() << endl;

    for (auto a : A)
    {
        cout << a << " ";
    }

    cout << endl;

    return 0;
}