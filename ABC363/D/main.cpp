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
    N--;

    if (N == 0)
    {
        cout << "0" << endl;
        return 0;
    }

    uint64_t pow_9 = 2 * 9;
    uint64_t count = 1;
    while (N >= pow_9)
    {
        N -= pow_9;
        pow_9 *= 10;
        count++;
    }

    uint64_t digits = 2 * count;

    if (N < pow_9 / 2)
    {
        digits--;
    }
    else
    {
        N -= pow_9 / 2;
    }

    vector<char> result;

    pow_9 = 9;
    N--;
    for (uint64_t i = 0; i < (digits - 1) / 2; i++)
    {
        result.push_back('0' + N % 10);
        N /= 10;
    }

    result.push_back('1' + N);

    for (auto it = result.rbegin(); it != result.rend(); it++)
    {
        cout << *it;
    }

    auto it = result.begin();
    if (digits % 2 == 1)
        it++;
    for (; it != result.end(); it++)
    {
        cout << *it;
    }

    cout << endl;

    return 0;
}