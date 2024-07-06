#include <iostream>

constexpr std::size_t COLOR_INDEX = 0;
constexpr std::size_t VALUE_INDEX = 1;

int main() {
	std::uint32_t N, K;
	std::cin >> N >> K;

	std::int64_t dp[500 + 1][2][2];
	for (std::size_t i = 0; i < K + 1; i++) {
		for (std::size_t j = 0; j < 2; j++) {
			dp[i][j][0] = -1;
			dp[i][j][1] = ((std::int64_t)1 << 63);
		}
	}

	dp[0][0][0] = 0;
	dp[0][0][1] = 0;

	for (std::size_t n = 0; n < N; n++) {
		std::uint32_t C, V;
		std::cin >> C >> V;

		for (std::size_t k = K; k > 0; k--) {

			//éÊÇËèúÇ©Ç»Ç¢Ç∆Ç´ÇÃílÇçlÇ¶ÇÈ
			if (dp[k][0][COLOR_INDEX] != C) {
				dp[k][0][COLOR_INDEX] = C;
				dp[k][0][VALUE_INDEX] += V;
			}
			else {
				dp[k][0][COLOR_INDEX] = C;
				dp[k][0][VALUE_INDEX] = dp[k][1][VALUE_INDEX] + V;
			}

			//è¨Ç≥Ç¢ï˚ÇÕçÌèú
			dp[k][1][COLOR_INDEX] = -1;
			dp[k][1][VALUE_INDEX] = ((std::int64_t)1 << 63);

			if (dp[k - 1][1][VALUE_INDEX] >= dp[k][0][VALUE_INDEX]) {
				dp[k][0][COLOR_INDEX] = dp[k - 1][0][COLOR_INDEX];
				dp[k][0][VALUE_INDEX] = dp[k - 1][0][VALUE_INDEX];
				dp[k][1][COLOR_INDEX] = dp[k - 1][1][COLOR_INDEX];
				dp[k][1][VALUE_INDEX] = dp[k - 1][1][VALUE_INDEX];
			}
			else if (dp[k - 1][0][VALUE_INDEX] >= dp[k][0][VALUE_INDEX]) {
				if (dp[k - 1][0][COLOR_INDEX] != dp[k][0][COLOR_INDEX]) {
					dp[k][1][COLOR_INDEX] = dp[k][0][COLOR_INDEX];
					dp[k][1][VALUE_INDEX] = dp[k][0][VALUE_INDEX];
				}
				else {
					dp[k][1][COLOR_INDEX] = dp[k - 1][1][COLOR_INDEX];
					dp[k][1][VALUE_INDEX] = dp[k - 1][1][VALUE_INDEX];
				}
				dp[k][0][COLOR_INDEX] = dp[k - 1][0][COLOR_INDEX];
				dp[k][0][VALUE_INDEX] = dp[k - 1][0][VALUE_INDEX];
			}
			else if (dp[k - 1][0][COLOR_INDEX] != dp[k][0][COLOR_INDEX]) {
				dp[k][1][COLOR_INDEX] = dp[k - 1][0][COLOR_INDEX];
				dp[k][1][VALUE_INDEX] = dp[k - 1][0][VALUE_INDEX];
			}
			else {
				dp[k][1][COLOR_INDEX] = dp[k - 1][1][COLOR_INDEX];
				dp[k][1][VALUE_INDEX] = dp[k - 1][1][VALUE_INDEX];
			}
		}

		if (dp[0][0][COLOR_INDEX] != C) {
			dp[0][0][COLOR_INDEX] = C;
			dp[0][0][VALUE_INDEX] += V;
		}
		else {
			dp[0][0][VALUE_INDEX] = ((std::int64_t)1 << 63);
		}
	}

	if(dp[K][0][VALUE_INDEX] < 0)std::cout << "-1" << std::endl;
	else std::cout << dp[K][0][VALUE_INDEX] << std::endl;
	return 0;
}