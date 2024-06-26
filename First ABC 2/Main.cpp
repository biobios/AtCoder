#include <iostream>
#include <string>
using namespace std;

constexpr char TEST_STR[3] = { 'A', 'B', 'C' };

int main()
{
	uint64_t N;

	cin >> N;

	string str;

	cin >> str;

	int index = str.find(TEST_STR);
	if (index != string::npos) index++;
	else index = -1;

	cout << index << endl;

	return 0;
}