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
#include <cstdint>

using namespace std;

int main()
{
    uint64_t N;
    cin >> N;
    set<uint64_t> C;

    for (uint64_t i = 0; i < N; ++i)
    {
        uint64_t c;
        cin >> c;
        C.insert(c);
    }

    cout << C.size() << endl;
    for (const auto& c : C)
    {
        cout << c << " ";
    }
    cout << endl;
    return 0;
}