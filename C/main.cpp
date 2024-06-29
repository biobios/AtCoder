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

    vector<int64_t> A(N);
    for (size_t i = 0; i < N; i++)
    {
        cin >> A[i];
    }

    set<int64_t> s;
    map<int64_t, uint64_t> m;
    s.insert(0);
    m[0] = 1;

    uint64_t result = 1;

    for (size_t i = 0; i < N; i++)
    {
        set<int64_t> s2;
        map<int64_t, uint64_t> m2;
        uint64_t sum = 0;
        for (auto x : s)
        {
            s2.insert(x + A[i]);
            uint64_t m_buf = m[x];
            sum += m_buf;
            if (x == 0 && m[A[i]] >= 1)
                m_buf--;
            m2[x + A[i]] += m_buf;
        }

        for (auto m_e : m2)
        {
            m[m_e.first] += m_e.second;
        }

        result += sum - 1;
        s.merge(s2);
    }

    cout << result << endl;

    return 0;
}