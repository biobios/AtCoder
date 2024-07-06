#include <iostream>
#include <vector>

using namespace std;

bool process(vector<char>* s,vector<char>::iterator start, vector<char>::iterator end) {
	auto itr = start;
	itr++;
	for (; itr != end;itr++) {
		if (*itr == '(') {
			vector<char>::iterator arg = itr;
			itr--;
			if (!process(s, arg, end))return false;
			end = s->end();
			continue;
		}
		if (*itr == ')') {
			itr++;
			s->erase(start, itr);
			return true;
		}
	}
	return false;
}

int main() {

	uint64_t N;
	cin >> N;
	vector<char> sequense(N);

	for (size_t i = 0; i < N; i++) {
		cin >> sequense[i];
	}

	vector<char>::iterator itr = sequense.begin();
	vector<char>::iterator itr_end = sequense.end();
	
	for (; itr != itr_end; itr++) {
		if (*itr == '(') {
			vector<char>::iterator arg = itr;
			itr--;
			if (!process(&sequense, arg, itr_end)) break;
			itr_end = sequense.end();
		}
	}

	for (size_t i = 0; i < sequense.size(); i++) {
		cout << sequense[i];
	}
	cout << endl;

	return 0;
}