#include <iostream>
#include <vector>
#include <algorithm>

int main() {
	std::uint64_t N, M;

	std::cin >> N >> M;

	std::vector<std::uint64_t> A(N);
	std::vector<std::uint64_t> B(M);

	for (std::size_t i = 0; i < N; i++) {
		std::cin >> A[i];
	}

	for (std::size_t i = 0; i < M; i++) {
		std::cin >> B[i];
	}

	if (A.size() >= B.size() + 2) {
		std::cout << "Yes" << std::endl;
		return 0;
	}

	std::sort(A.begin(), A.end());
	std::sort(B.begin(), B.end());

	auto itA = A.begin();
	auto itB = B.begin();
	bool prev_was_A = false;

	while (itA != A.end() && itB != B.end()) {
		if (*itA > *itB) {
			itB++;
			prev_was_A = false;
		}
		else {
			itA++;
			if (prev_was_A) {
				std::cout<< "Yes" << std::endl;
				return 0;
			}
			prev_was_A = true;
		}
	}

	while (itA != A.end()) {
		itA++;
		if (prev_was_A) {
			std::cout << "Yes" << std::endl;
			return 0;
		}
		prev_was_A = true;
	}

	std::cout << "No" << std::endl;
	
	return 0;
}