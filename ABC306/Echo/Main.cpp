#include <iostream>
#include <string>

using namespace std;

int main() {

	int N;
	cin >> N;
	string str(2*N, '\0');

	for (size_t i = 0; i < N; i++) {
		char input;
		cin >> input;
		str[i * 2] = input;
		str[i * 2 + 1] = input;
	}

	cout << str << endl;

	return 0;
}