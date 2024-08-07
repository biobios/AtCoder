#include <iostream>
#include <string>
#include <sstream>

int main()
{
	std::string line;
	std::cin >> line;
	std::stringstream ss(line);

	std::uint32_t alphabet_count[26] = { 0 };

	while (true) {
		char c;
		ss >> c;

		if (ss.eof()) break;
		
		alphabet_count[c - 'a']++;
	}

	std::uint64_t result = 0;

	// 二つ以上含まれている文字があるかどうかを確認
	for (int i = 0; i < 26; i++) {
		if (alphabet_count[i] > 1) {
			result++;
			break;
		}
	}

	// 異なる種類の文字の組み合わせを数える
	for (int i = 0; i < 26; i++) {
		for (int j = i + 1; j < 26; j++) {
			result += alphabet_count[i] * alphabet_count[j];
		}
	}

	std::cout << result << std::endl;
	return 0;
}