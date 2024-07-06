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

	// “ñ‚ÂˆÈãŠÜ‚Ü‚ê‚Ä‚¢‚é•¶š‚ª‚ ‚é‚©‚Ç‚¤‚©‚ğŠm”F
	for (int i = 0; i < 26; i++) {
		if (alphabet_count[i] > 1) {
			result++;
			break;
		}
	}

	// ˆÙ‚È‚éí—Ş‚Ì•¶š‚Ì‘g‚İ‡‚í‚¹‚ğ”‚¦‚é
	for (int i = 0; i < 26; i++) {
		for (int j = i + 1; j < 26; j++) {
			result += alphabet_count[i] * alphabet_count[j];
		}
	}

	std::cout << result << std::endl;
	return 0;
}