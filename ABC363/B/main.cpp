#include <iostream>
#include <vector>
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
    uint64_t N, T, P;
    cin >> N >> T >> P;

    vector<uint64_t> L(N);
    for (auto &l : L)
    {
        cin >> l;
    }

    sort(L.rbegin(), L.rend());

    if (L[P - 1] > T)
    {
        cout << 0 << endl;
    }
    else
    {
        cout << T - L[P - 1] << endl;
    }

    return 0;
}