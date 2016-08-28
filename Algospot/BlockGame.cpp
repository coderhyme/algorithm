#include <cstdio>
#include <cstring>

using namespace std;

const int threeBlocks[4] { 1 << 5 | 3, 2 << 5 | 3, 3 << 5 | 1, 3 << 5 | 2};
const int twoBlocks[2] { 1 << 5 | 1, 3 };

char cache[1 << 25];

int tryPut(int state, int block, int y, int x) {
	int adjusted = (block << ((4 - y) * 5)) << (4 - x);

	if (state & adjusted) return -1;
	return state | adjusted;
}

void print(int state) {
	for (int i=0; i<5; ++i) {
		for (int j=0; j<5; ++j) {
			if (((state >> ((4 - i) * 5)) >> (4 - j)) & 1) printf("#");
			else printf(".");
		}
		printf("\n");
	}
	printf ("\n");
}

int bitPos(int y, int x) {
	return (4 - y) * 5 + (4 - x);
}

int rotate(int state) {
	int newState = 0;
	for (int i=0; i<4; ++i) {
		newState |= ((state >> bitPos(0, i)) & 1) << bitPos(i, 4);
		newState |= ((state >> bitPos(i, 4)) & 1) << bitPos(4, 4 - i);
		newState |= ((state >> bitPos(4, 4 - i)) & 1) << bitPos(4 - i, 0);
		newState |= ((state >> bitPos(4 - i, 0)) & 1) << bitPos(0, i);
	}

	for (int i=0; i<2; ++i) {
		newState |= ((state >> bitPos(1, 1 + i)) & 1) << bitPos(i + 1, 3);
		newState |= ((state >> bitPos(i + 1, 3)) & 1) << bitPos(3, 3 - i);
		newState |= ((state >> bitPos(3, 3 - i)) & 1) << bitPos(3 - i, 1);
		newState |= ((state >> bitPos(3 - i, 1)) & 1) << bitPos(1, 1 + i);
	}

	return newState | (state & (1 << bitPos(2, 2)));
}

char solve(int state) {
	if (state == -1) return 1;

	char& ret = cache[state];
	if (ret != -1) return ret;

	int rotated = state;
	for (int i=0; i<3; ++i) {
		rotated = rotate(rotated);
		if (cache[rotated] != -1) return ret = cache[rotated];
	}

	ret = 0;

	for (int i=0; i<5; ++i) {
		for (int j=0; j<5; ++j) {
			if (i > 0 && j > 0) {
				for (int k=0; k<4; ++k) {
					if (!solve(tryPut(state, threeBlocks[k], i, j))) {
						return ret = 1;
					}
				}
			}

			if (i > 0) if (!solve(tryPut(state, twoBlocks[0], i, j))) return ret = 1;
			if (j > 0) if (!solve(tryPut(state, twoBlocks[1], i, j))) return ret = 1;
		}
	}

	return ret;
}

int main() {
#ifdef RUN_LOCALLY
	freopen("BlockGame.txt", "r", stdin);
#endif
	memset(cache, -1, sizeof(cache));

	int tc;

	scanf("%d", &tc);

	while(tc--) {
		int state = 0;

		for (int i=0; i<5; ++i) {
			char line[10];
			scanf("%s", line);
			for (int j=0; j<5; ++j) {
				state <<= 1;
				if (line[j] == '#') state |= 1;
			}
		}

		if (solve(state)) printf("WINNING\n");
		else printf("LOSING\n");
	}

	return 0;
}
