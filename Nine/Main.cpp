#include <iostream>

using namespace std;

int main() {

	std::int8_t A, B;

	cin >> A >> B;

	A--;
	B--;

	if (A % 3 == 2) cout << "No";
	else if (A + 1 == B) cout << "Yes";
	else cout << "No";

	return 0;
}