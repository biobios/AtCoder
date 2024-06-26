#include <iostream>
#include <vector>
#include <stack>
#include <algorithm>

class Tile {
	std::uint8_t width;
	std::uint8_t height;
public:
	std::uint32_t getSize() {
		return width * height;
	}

	static bool compare(Tile* a, Tile* b) {
		return a->getSize() > b->getSize();
	}
};

class TileSet {	
public:
	TileSet(std::vector<Tile*> tiles) : tiles(tiles) {
		std::sort(tiles.begin(), tiles.end(), Tile::compare);
	}

	std::vector<Tile*> tiles;
	std::vector<TileSet*> getLimitedTileSet(std::uint8_t width, std::uint8_t height) {
		std::int32_t tileCount = width * height;
		std::stack<bool> used;
		std::uint8_t i = 0;

		//　ちょうどtileCount個のタイルを使う組み合わせを探す
		while (i < tiles.size()) {
			if (tileCount == 0) {
				break;
			}
			if (tileCount >= tiles[i]->getSize()) {
				tileCount -= tiles[i]->getSize();
				used.push(true);
			}
			else {
				used.push(false);
			}
			i++;
		}
	}
};