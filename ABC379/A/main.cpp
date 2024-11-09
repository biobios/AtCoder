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

    uint64_t a, b, c;
    c = N % 10;
    N /= 10;
    b = N % 10;
    N /= 10;
    a = N % 10;

    cout << (b * 100 + c * 10 + a) << " ";
    cout << (c * 100 + a * 10 + b) << endl;

    return 0;
}