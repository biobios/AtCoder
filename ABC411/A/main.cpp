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
#include <cstdint>

using namespace std;

int main()
{
    string P;
    cin >> P;
    uint64_t L;
    cin >> L;

    if (P.length() >= L) {
        cout << "Yes" << endl;
    }else {
        cout << "No" << endl;
    }
    
    return 0;
}