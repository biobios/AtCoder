#include <iostream>
#include <vector>
#include <fstream>
#include <format>
#include <cmath>

class Area
{
	std::uint16_t x;
	std::uint16_t y;
	std::uint16_t width;
	std::uint16_t height;
public:
	Area(std::uint16_t x, std::uint16_t y, std::uint16_t width, std::uint16_t height) : x(x), y(y), width(width), height(height)
	{
	}

	void print(std::ostream& os)
	{
		os << x << " " << y << " " << (x + width) << " " << (y + height) << std::endl;
	}

	Area* split()
	{
		Area* newArea = new Area(x, y, width, 1);
		y++;
		height--;
		return newArea;
	}
};

class EventHall
{
	std::vector<Area*> freeAreas;
	std::vector<Area*> usedAreas;
};

class DevidedPart
{
public:
	enum class Direction
	{
		Left,
		Right
	};
private:
	std::uint16_t W;
	std::vector<DevidedPart*> opositeParts;
	Direction direction;
	std::uint16_t width = 0;
	std::uint16_t y;
	std::uint16_t height;
public:
	DevidedPart(std::uint16_t W, std::uint16_t y, std::uint16_t height, Direction d) : W(W), direction(d), y(y), height(height)
	{
	}

	void AddOpositePart(DevidedPart* part)
	{
		opositeParts.push_back(part);
	}

	bool isAvailable(std::uint32_t allocatingSize)
	{

		std::uint16_t max = 0;

		for (auto part : opositeParts)
		{
			if (part->width > max)
				max = part->width;
		}

		std::uint16_t allocatingWidth = (allocatingSize + height - 1) / height;

		if (max + width + allocatingWidth > W)
			return false;
		else return true;

	}

	std::uint32_t getAvailableSize()
	{
		std::uint16_t max = 0;

		for (auto part : opositeParts)
		{
			if (part->width > max)
				max = part->width;
		}

		if (max + width > W)
			return 0;
		else return (W - max - width) * height;

	}

	std::uint16_t getAvailableWidth()
	{
		std::uint16_t max = 0;

		for (auto part : opositeParts)
		{
			if (part->width > max)
				max = part->width;
		}

		if (max + width > W)
			return 0;
		else return W - max - width;
	}

	Area* allocate(std::uint32_t size)
	{
		std::uint16_t allocatingWidth = (size + height - 1) / height;
		std::uint16_t allocatableWidth = getAvailableWidth();
		if (allocatingWidth > allocatableWidth)
			allocatingWidth = allocatableWidth;

		Area* area = nullptr;

		switch (direction)
		{
		case Direction::Left:
			area = new Area(width, y, allocatingWidth, height);
			break;
		case Direction::Right:
			area = new Area(W - width - allocatingWidth, y, allocatingWidth, height);
			break;
		}

		width += allocatingWidth;
		return area;
	}

	std::uint16_t calcWidthWhenAllocated(std::uint32_t size)
	{
		std::uint16_t allocatingWidth = (size + height - 1) / height;
		return width + allocatingWidth;
	}

	std::uint16_t getWidth()
	{
		return width;
	}

	void reset()
	{
		width = 0;
	}
};

class Test
{
	std::vector<DevidedPart*> left;
	std::vector<DevidedPart*> right;
	std::vector<Area*> areas;
public:
	Test(std::uint16_t W, std::uint16_t numLeft)
	{

		std::uint16_t numRight = numLeft * 2;
		std::uint16_t leftHeight = W / numLeft;
		std::uint16_t rightHeight = W / numRight;

		for (std::uint16_t i = 0; i < numLeft; i++)
		{
			left.push_back(new DevidedPart(W, i * leftHeight, leftHeight, DevidedPart::Direction::Left));
		}

		for (std::uint16_t i = 0; i < numRight; i++)
		{
			right.push_back(new DevidedPart(W, i * rightHeight, rightHeight, DevidedPart::Direction::Right));
		}

		for (std::uint16_t i = 0; i < numLeft; i++)
		{
			left[i]->AddOpositePart(right[i * 2]);
			left[i]->AddOpositePart(right[i * 2 + 1]);
			right[i * 2]->AddOpositePart(left[i]);
			right[i * 2 + 1]->AddOpositePart(left[i]);
		}
	}

	static constexpr std::uint16_t threshold_width = 400;

	void allocate(std::vector<std::uint32_t> reservations)
	{
		areas.assign(reservations.size(), nullptr);

		std::int32_t allocating_index = reservations.size() - 1;

		while (allocating_index >= 0) {

			bool over_threshold = false;
			for (std::size_t i = 0; i < left.size(); i++) {
				if (left[i]->getWidth() >= threshold_width) {
					over_threshold = true;
					break;
				}
			}
			if (over_threshold)
				break;

			std::size_t min_index = 0;
			for (std::size_t i = 1; i < left.size(); i++)
			{
				if (left[min_index]->getWidth() > left[i]->getWidth())
					min_index = i;
			}

			areas[allocating_index] = left[min_index]->allocate(reservations[allocating_index]);
			allocating_index--;
		}

		std::uint16_t left_max_width = 0;
		for (std::size_t i = 0; i < left.size(); i++)
		{
			if (left[i]->getWidth() > left_max_width)
				left_max_width = left[i]->getWidth();
		}

		while (allocating_index >= 0) {
			std::int32_t fitting_index = -1;
			std::uint16_t max_width = 0;
			for (std::size_t i = 0; i < left.size(); i++) {
				std::uint16_t expected_width = left[i]->calcWidthWhenAllocated(reservations[allocating_index]);
				if (expected_width <= left_max_width && expected_width > max_width) {
					fitting_index = i;
					max_width = expected_width;
				}
			}

			if (fitting_index != -1 && left[fitting_index]->isAvailable(reservations[allocating_index])) {
				areas[allocating_index] = left[fitting_index]->allocate(reservations[allocating_index]);
				allocating_index--;
				continue;
			}

			std::size_t min_index = 0;
			for (std::size_t i = 1; i < right.size(); i++)
			{
				if (right[min_index]->getWidth() > right[i]->getWidth())
					min_index = i;
			}

			if (right[min_index]->isAvailable(reservations[allocating_index])) {
				areas[allocating_index] = right[min_index]->allocate(reservations[allocating_index]);
				allocating_index--;
				continue;
			}

			fitting_index = -1;
			std::uint16_t min_width = ~0;
			for (std::size_t i = 0; i < left.size(); i++) {
				std::uint32_t expected_width = left[i]->calcWidthWhenAllocated(reservations[allocating_index]);
				if (expected_width < min_width && left[i]->isAvailable(reservations[allocating_index])) {
					fitting_index = i;
					min_width = expected_width;
				}
			}

			if (fitting_index != -1 && left[fitting_index]->getAvailableSize() > 0) {
				areas[allocating_index] = left[fitting_index]->allocate(reservations[allocating_index]);
				allocating_index--;
				continue;
			}

			areas[allocating_index] = areas[areas.size() - 1]->split();
			allocating_index--;
		}
	}

	void reset()
	{
		for (auto area : areas)
		{
			delete area;
		}

		areas.clear();

		for (auto part : left)
		{
			part->reset();
		}

		for (auto part : right)
		{
			part->reset();
		}
	}

	void print(std::ostream& os)
	{
		for (auto area : areas)
		{
			area->print(os);
		}
	}
};

int process(std::istream& inputStream, std::ostream& outputStream)
{
	std::uint64_t W, D, N;
	inputStream >> W >> D >> N;

	std::vector<std::vector<std::uint32_t>> reservations(D, std::vector<std::uint32_t>(N));

	std::uint32_t max = 0;
	std::uint64_t sum = 0;

	for (std::uint64_t i = 0; i < D; i++)
	{
		for (std::uint64_t j = 0; j < N; j++)
		{
			inputStream >> reservations[i][j];
			sum += reservations[i][j];
			if (reservations[i][j] > max)
				max = reservations[i][j];
		}
	}

	std::uint64_t avg = sum / (D * N);
	std::uint16_t numLeft = std::min(W * W / max, W * W / (avg * 2) );
	if (numLeft > 4) {
		numLeft = 4;
	}
	else if (numLeft > 2) {
		numLeft = 2;
	}
	else {
		numLeft = 1;
	}

	Test test(W, numLeft);

	for (std::size_t i = 0; i < D; i++) {
		test.allocate(reservations[i]);
		test.print(outputStream);
		test.reset();
	}

	return 0;
}

int main(int argc, char* argv[])
{

	//std::cout << argv[0] << std::endl;

	//for (std::size_t i = 0; i < 100; i++) {
	//	std::string inputFileName = std::format("in\\{:04d}.txt", i);
	//	std::string outputFileName = std::format("out\\abcd_{:04d}.txt", i);

	//	std::cout << inputFileName << std::endl;
	//	std::cout << outputFileName << std::endl;

	//	std::ifstream inputFile(inputFileName);
	//	std::ofstream outputFile(outputFileName, std::ios_base::trunc);

	//	if (!inputFile.is_open() || !outputFile.is_open())
	//		break;

	//	process(inputFile, outputFile);
	//}

	return process(std::cin, std::cout);
}