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
    int64_t X_A, Y_A, X_B, Y_B, X_C, Y_C;
    cin >> X_A >> Y_A >> X_B >> Y_B >> X_C >> Y_C;

    int64_t X_A_B = X_B - X_A;
    int64_t Y_A_B = Y_B - Y_A;
    int64_t X_B_C = X_C - X_B;
    int64_t Y_B_C = Y_C - Y_B;
    int64_t X_C_A = X_A - X_C;
    int64_t Y_C_A = Y_A - Y_C;

    // 内積の計算をして0ならYes
    if (X_A_B * X_B_C + Y_A_B * Y_B_C == 0 || X_B_C * X_C_A + Y_B_C * Y_C_A == 0 || X_C_A * X_A_B + Y_C_A * Y_A_B == 0)
    {
        cout << "Yes" << endl;
    }
    else
    {
        cout << "No" << endl;
    }

    return 0;
}