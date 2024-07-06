#include <iostream>
#include <format>
#include <fstream>

int main(int argc, char* argv[])
{

	std::ofstream outputFile("D_N.txt", std::ios_base::trunc);
	if (!outputFile.is_open())
	{
		std::cerr << "Failed to open file" << std::endl;
		return 1;
	}

	for (std::size_t i = 0; i < 100; i++) {
		std::string inputFileName = std::format("in\\{:04d}.txt", i);
		std::ifstream inputFile(inputFileName);

		if(!inputFile.is_open())
			break;
		
		std::uint64_t W, D, N;
		inputFile >> W >> D >> N;

		std::uint64_t sum = 0;
		for (std::size_t i = 0; i < D * N; i++) {
			std::uint64_t size;
			inputFile >> size;
			sum += size;
		}

		std::uint64_t avg = sum / (D * N);

		outputFile << D << "," << N << "," << avg << std::endl;

	}
}