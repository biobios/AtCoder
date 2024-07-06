#include <iostream>

using namespace std;

int main()
{
	uint64_t S_x, S_y;
	cin >> S_x >> S_y;

	uint64_t T_x, T_y;
	cin >> T_x >> T_y;

	uint64_t result = 0;
	if (S_x > T_x)
	{
		if ((S_x + S_y) % 2 != 0)
			S_x--;
		if ((T_x + T_y) % 2 != 0)
			T_x--;

		uint64_t diff_x = S_x - T_x;
		uint64_t diff_y;
		if (S_y > T_y)
		{
			diff_y = S_y - T_y;
		}
		else
		{
			diff_y = T_y - S_y;
		}

		result += diff_y;

		if (diff_x > diff_y)
			result += (diff_x - diff_y) / 2;
	}
	else {
		if(S_x != T_x && (S_x + S_y) % 2 == 0)
			S_x++;
		if(S_x != T_x && (T_x + T_y) % 2 == 0)
			T_x++;

		uint64_t diff_x = T_x - S_x;
		uint64_t diff_y;
		if (S_y > T_y)
		{
			diff_y = S_y - T_y;
		}
		else
		{
			diff_y = T_y - S_y;
		}

		result += diff_y;

		if (diff_x > diff_y)
			result += (diff_x - diff_y) / 2;
	}

	cout << result << endl;
	return 0;
}