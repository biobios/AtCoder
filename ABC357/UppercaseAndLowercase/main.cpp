#include <iostream>

using namespace std;

int main()
{
	string S;
	cin >> S;

	uint64_t upper = 0;
	for (auto&& c : S)
	{
		if(isupper(c))
			upper++;
	}

	if (upper > S.size() / 2)
	{
		for (auto&& c : S)
		{
			cout << (char)toupper(c);
		}
	}
	else
	{
		for (auto&& c : S)
		{
			cout << (char)tolower(c);
		}
	}

	cout << endl;

	return 0;
}