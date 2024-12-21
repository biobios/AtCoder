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
#include <iomanip>

using namespace std;

int main()
{
    uint64_t N;
    cin >> N;

    vector<pair<int64_t, int64_t>> A(N);

    for (size_t i = 0; i < N; ++i)
    {
        cin >> A[i].first >> A[i].second;
    }

    double ans = -1;

    double tilt = (double)(A[1].second - A[0].second) / (double)(A[1].first - A[0].first);
    uint64_t x = A[1].first;
    uint64_t y = A[1].second;
    ans = max(ans, A[1].second - tilt * A[1].first);

    for (size_t i = 2; i < N; ++i)
    {
        if (y + tilt * (A[i].first - x) > A[i].second)
        {
            tilt = (double)(A[i].second - y) / (double)(A[i].first - x);
            x = A[i].first;
            y = A[i].second;
            ans = max(ans, A[i].second - tilt * A[i].first);
        }
    }
    if (ans < 0)
        cout << "-1" << endl;
    else
        cout << fixed << setprecision(17) << ans << endl;

    return 0;
}