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
    uint64_t N;
    cin >> N;

    vector<uint64_t> H(N);

    for (size_t i = 0; i < N; ++i)
    {
        cin >> H[i];
    }

    stack<pair<uint64_t, size_t>> st;
    vector<int64_t> result(N, 0);

    st.push(make_pair(H[0], 0));

    for (size_t i = 1; i < N; ++i)
    {
        while (!st.empty() && st.top().first < H[i])
        {
            st.pop();
        }

        if (st.empty())
        {
            ++result[0];
            --result[i];
            st.push(make_pair(H[i], i));
            continue;
        }

        auto [h, index] = st.top();
        ++result[index];
        --result[i];
        st.push(make_pair(H[i], i));
    }

    for (size_t i = 1; i < N; ++i)
    {
        result[i] += result[i - 1];
    }

    for (size_t i = 0; i < N; ++i)
    {
        cout << result[i] << " ";
    }

    cout << endl;

    return 0;
}