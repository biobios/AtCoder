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
    string S;
    cin >> S;
    vector<uint64_t> A(3);

    for (char c : S)
    {
        if (c == 'A')
            A[0]++;
        else if (c == 'B')
            A[1]++;
        else if (c == 'C')
            A[2]++;
    }

    if (A[0] == 1 && A[1] == 1 && A[2] == 1)
        cout << "Yes" << endl;
    else
        cout << "No" << endl;

    return 0;
}