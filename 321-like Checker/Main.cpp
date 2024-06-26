#include <iostream>

using namespace std;

int main() {
	string N;
	cin >> N;

	bool is321 = true;
	for (int i = 0; i < N.length() - 1; i++) {
		if (N[i] <= N[i + 1]) {
			is321 = false;
			break;
		}
	}

	if(is321)
		cout << "Yes" << endl;
	else
		cout << "No" << endl;

	return 0;
}