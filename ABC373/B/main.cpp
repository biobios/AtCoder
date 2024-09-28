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
    string S;
    cin >> S;

    vector<size_t> index(26, 0);

    for (size_t i = 0; i < S.size(); ++i)
    {
        index[S[i] - 'A'] = i;
    }

    uint64_t move_distance = 0;

    for (size_t i = 1; i < 26; ++i)
    {
        move_distance += abs((int64_t)(index[i] - index[i - 1]));
    }

    cout << move_distance << endl;

    return 0;
}