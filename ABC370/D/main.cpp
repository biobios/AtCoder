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
    uint64_t H, W, Q;
    cin >> H >> W >> Q;

    vector<set<uint64_t>> row(H);
    vector<set<uint64_t>> col(W);

    uint64_t count = H * W;

    for (size_t i = 0; i < H; ++i)
    {
        for (size_t j = 0; j < W; ++j)
        {
            row[i].insert(j);
            col[j].insert(i);
        }
    }

    for (size_t i = 0; i < Q; ++i)
    {
        uint64_t R, C;
        cin >> R >> C;

        --R;
        --C;

        if (row[R].contains(C))
        {
            row[R].erase(C);
            col[C].erase(R);
            --count;
            continue;
        }

        auto right = row[R].upper_bound(C);
        auto bottom = col[C].upper_bound(R);
        auto left = right;
        auto top = bottom;

        if (right != row[R].begin() && !row[R].empty())
        {
            --left;
            col[*left].erase(R);
            row[R].erase(left);
            --count;
        }

        if (bottom != col[C].begin() && !col[C].empty())
        {
            --top;
            row[*top].erase(C);
            col[C].erase(top);
            --count;
        }

        if (right != row[R].end())
        {
            col[*right].erase(R);
            row[R].erase(right);
            --count;
        }

        if (bottom != col[C].end())
        {
            row[*bottom].erase(C);
            col[C].erase(bottom);
            --count;
        }
    }

    cout << count << endl;

    return 0;
}