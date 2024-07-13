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
    uint64_t N;
    cin >> N;
    vector<pair<int64_t, int64_t>> v(N);
    int64_t sum_L = 0;
    int64_t sum_R = 0;
    for (int i = 0; i < N; ++i)
    {
        cin >> v[i].first >> v[i].second;
        sum_L += v[i].first;
        sum_R += v[i].second;
    }

    if (sum_L > 0 || 0 > sum_R)
    {
        cout << "No" << endl;
        return 0;
    }

    cout << "Yes" << endl;
    sum_L = -sum_L;
    for (int i = 0; i < N; ++i)
    {
        int64_t out = min(v[i].second, v[i].first + sum_L);
        cout << out << " ";
        sum_L -= out - v[i].first;
    }

    cout << endl;

    return 0;
}