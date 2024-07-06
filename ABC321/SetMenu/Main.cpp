#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main() {

	uint64_t N, M, P;

	cin >> N >> M >> P;

	vector<uint64_t> A(N);
	vector<uint64_t> B(M);

	uint64_t minA = ~0;

	for (uint64_t i = 0; i < N; i++) {
		cin >> A[i];
		if(A[i] < minA)
			minA = A[i];
	}

	uint64_t minB = ~0;

	for (uint64_t i = 0; i < M; i++) {
		cin >> B[i];
		if (B[i] < minB)
			minB = B[i];
	}

	uint64_t result = 0;

	sort(A.begin(), A.end());
	sort(B.begin(), B.end());

	auto itA = A.begin();

	while (itA != A.end() && *itA + minB < P) {
		itA++;
	}

	result += P * distance(itA, A.end()) * B.size();
	A.erase(itA, A.end());

	auto itB = B.begin();

	while (itB != B.end() && *itB + minA < P) {
		itB++;
	}

	result += P * distance(itB, B.end()) * A.size();
	B.erase(itB, B.end());

	reverse(A.begin(), A.end());

	itA = A.begin();
	itB = B.begin();
	while (itA != A.end()) {
		while (itB != B.end()) {
			if (*itA + *itB < P) {
				result += *itB * distance(itA, A.end());
			}
			else {
				break;
			}
			itB++;
		}
		result += *itA * distance(B.begin(), itB);
		result += P * distance(itB, B.end());

		itA++;
	}

	cout << result << endl;

	return 0;
}