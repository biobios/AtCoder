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

void process()
{
    uint64_t N, K;
    cin >> N >> K;

    // 最上位ビットが1であるK桁の2進数を作る
    // 11111...11111
    // 10111...11111
    // 11011...11111
    // 10011...11111
    // 10101...11111
    // 11001...11111

    // 法則：K-1桁のですべてのビットが1である2進数を作り、
    // 1ずつ減らしていく
    // K桁目に1を立て、残りのビットを生成したビットの上下反対したものを作る

    uint64_t bits = (1 << (K - 1));

    uint64_t mask = (1 << (K - 1));

    for (size_t i = 0; i < N; ++i)
    {
        bits--;
        uint64_t output = mask;
        uint64_t bits_copy = bits;
        for (size_t j = 0; j < K - 1; ++j)
        {
            output |= (bits_copy & 1) << (K - 2 - j);
            bits_copy >>= 1;
        }
        cout << output << " ";
    }

    cout << endl;
}

int main()
{
    uint64_t T;
    cin >> T;

    for (size_t i = 0; i < T; ++i)
    {
        process();
    }
}