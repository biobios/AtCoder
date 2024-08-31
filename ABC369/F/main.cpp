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

bool compare(const pair<uint64_t, uint64_t> &a, const pair<uint64_t, uint64_t> &b)
{
    auto _a = a.first + a.second;
    auto _b = b.first + b.second;

    return _a < _b;
}

int main()
{
    uint64_t H, W, N;
    cin >> H >> W >> N;

    vector<pair<uint64_t, uint64_t>> A(N);

    for (size_t i = 0; i < N; ++i)
    {
        uint64_t a, b;
        cin >> a >> b;
        a--;
        b--;
        A[i] = make_pair(a, b);
    }

    sort(A.begin(), A.end(), compare);

    uint64_t R = 0;
    uint64_t C = 0;

    string result = "";
}