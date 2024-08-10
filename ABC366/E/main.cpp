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
    uint64_t N, D;
    cin >> N >> D;

    vector<int64_t> X(N), Y(N);

    uint64_t max_X = 0;
    uint64_t max_Y = 0;

    for (size_t i = 0; i < N; i++)
    {
        cin >> X[i] >> Y[i];

        max_X = max(max_X, (uint64_t)abs(X[i]));
        max_Y = max(max_Y, (uint64_t)abs(Y[i]));
    }

    sort(X.begin(), X.end());
    sort(Y.begin(), Y.end());

    vector<uint64_t> G(2 * (max_X + D) + 1);
    vector<uint64_t> H(2 * (max_Y + D) + 1);

    for (auto x : X)
    {
        G[0] += x;
    }

    G[0] += (max_X + D) * N;

    size_t x_i = 0;

    for (int64_t i = -(max_X + D) + 1; i <= (int64_t)(max_X + D); i++)
    {

        while (x_i < N && X[x_i] < i)
        {
            x_i++;
        }

        G[i + max_X + D] = G[i + max_X + D - 1] + 2 * x_i - N;
    }

    for (auto y : Y)
    {
        H[0] += y;
    }

    H[0] += (max_Y + D) * N;

    size_t y_i = 0;

    for (int64_t i = -(max_Y + D) + 1; i <= (int64_t)(max_Y + D); i++)
    {

        while (y_i < N && Y[y_i] < i)
        {
            y_i++;
        }

        H[i + max_Y + D] = H[i + max_Y + D - 1] + 2 * y_i - N;
    }

    sort(G.rbegin(), G.rend());
    sort(H.begin(), H.end());

    uint64_t result = 0;
    size_t g_i = 0;
    for (auto g : G)
    {
        while (g_i < H.size() && g + H[g_i] <= D)
        {
            g_i++;
        }

        result += g_i;
    }

    cout << result << endl;

    return 0;
}