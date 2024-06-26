#include <iostream>
#include <array>

using namespace std;

constexpr char EMPTY = '.';
constexpr char FILLED = '#';

class Polyomino {
	array<array<char, 4>, 4> polyomino;

public:
	uint64_t width;
	uint64_t height;
	uint64_t block_count = 0;

	public:
		Polyomino() {}

		void load(istream& input) {

			uint64_t start_x = ~0;
			uint64_t start_y = ~0;
			uint64_t end_x = 0;
			uint64_t end_y = 0;

			for (int y = 0; y < 4; y++) {
				for (int x = 0; x < 4; x++) {
					input >> polyomino[y][x];
					if (polyomino[y][x] == FILLED) {
						block_count++;
						if (start_x > x) start_x = x;
						if (start_y > y) start_y = y;
						if (end_x < x) end_x = x;
						if (end_y < y) end_y = y;
					}
				}
			}

			width = end_x - start_x;
			height = end_y - start_y;

			if (start_x == 0 && start_y == 0) {
				return;
			}

			// Normalize
			for (int y = start_y; y < 4; y++) {
				for (int x = start_x; x < 4; x++) {
					polyomino[y - start_y][x - start_x] = polyomino[y][x];
					polyomino[y][x] = EMPTY;
				}
			}
		}

		void rotate() {
			array<array<char, 4>, 4> copied_polyomino = polyomino;

			//polyomino clear
			for (int y = 0; y < 4; y++) {
				for (int x = 0; x < 4; x++) polyomino[y][x] = EMPTY;
			}

			//rotate
			for (int y = 0; y < 4; y++) {
				for (int x = 0; x < 4; x++) polyomino[x][3 - y] = copied_polyomino[y][x];
			}

			//normalize
			uint64_t start_x = ~0;
			uint64_t start_y = ~0;
			uint64_t end_x = 0;
			uint64_t end_y = 0;

			for (int y = 0; y < 4; y++) {
				for (int x = 0; x < 4; x++) {
					if (polyomino[y][x] == FILLED) {
						if (start_x > x) start_x = x;
						if (start_y > y) start_y = y;
						if (end_x < x) end_x = x;
						if (end_y < y) end_y = y;
					}
				}
			}

			width = end_x - start_x;
			height = end_y - start_y;

			if (start_x == 0 && start_y == 0) {
				return;
			}

			for (int y = start_y; y < 4; y++) {
				for (int x = start_x; x < 4; x++) {
					polyomino[y - start_y][x - start_x] = polyomino[y][x];
					polyomino[y][x] = EMPTY;
				}
			}
		}

		void write(array<array<char, 4>, 4>& board, uint64_t offset_x, uint64_t offset_y) {
			for (int y = 0; y < 4; y++) {
				for (int x = 0; x < 4; x++) {
					if (polyomino[y][x] == FILLED) {
						board[y + offset_y][x + offset_x] = FILLED;
					}
				}
			}
		}

		bool isOverlapped(array<array<char, 4>, 4>& board, uint64_t offset_x, uint64_t offset_y) {
			
			for (int y = 0; y < 4; y++) {
				for (int x = 0; x < 4; x++) {
					if (polyomino[y][x] == FILLED && board[y + offset_y][x + offset_x] == FILLED) {
						return true;
					}
				}
			}
			return false;
		}
};

int main() {
	Polyomino minos[3];

	for (int i = 0; i < 3; i++) {
		minos[i].load(cin);
	}

	if (minos[0].block_count + minos[1].block_count + minos[2].block_count != 4 * 4) {
		cout << "No" << endl;
		return 0;
	}

	for (int offset_x1 = 0; offset_x1 < 4 - minos[0].width; offset_x1++) {
		for (int offset_y1 = 0; offset_y1 < 4 - minos[0].height; offset_y1++) {
			array<array<char, 4>, 4> board = { EMPTY };
			minos[0].write(board, offset_x1, offset_y1);
			for (int rotate_count2 = 0; rotate_count2 < 4; rotate_count2++) {
				for (int rotate_count3 = 0; rotate_count3 < 4; rotate_count3++) {
					for (int offset_x2 = 0; offset_x2 < 4 - minos[1].width; offset_x2++) {
						for (int offset_y2 = 0; offset_y2 < 4 - minos[1].height; offset_y2++) {
							if(minos[1].isOverlapped(board, offset_x2, offset_y2)) continue;
							array<array<char, 4>, 4> board2 = board;
							minos[1].write(board2, offset_x2, offset_y2);

							for (int offset_x3 = 0; offset_x3 < 4 - minos[2].width; offset_x3++) {
								for (int offset_y3 = 0; offset_y3 < 4 - minos[2].height; offset_y3++) {
									if(minos[2].isOverlapped(board2, offset_x3, offset_y3)) continue;
									cout << "Yes" << endl;
									return 0;
								}
							}
						}
					}
					minos[2].rotate();
				}
				minos[1].rotate();
			}
		}
	}

	cout << "No" << endl;

	return 0;
}