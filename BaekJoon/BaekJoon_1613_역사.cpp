#define _CRT_SECURE_NO_WARNINGS

#include <iostream>

using namespace std;

int n, k, s;
int map[401][401];

void makeMap() {
	for (int k = 1; k <= n; k++) {
		for (int i = 1; i <= n; i++) {
			for (int j = 1; j <= n; j++) {
				if (map[i][k] == -1 && map[k][j] == -1) {
					map[i][j] = -1;
					map[j][i] = 1;
				}
			}
		}
	}
}

int main() {

	scanf("%d", &n);
	scanf("%d", &k);

	for (int i = 0; i < k; i++) {
		int y, x;
		scanf("%d", &y);
		scanf("%d", &x);
		map[y][x] = -1; // 앞이 먼저
		map[x][y] = 1; // 뒤는 나중에 일어남
	}

	// 플로이드 - 워셜 알고리즘 - 알고리즘이후 맵이 완성이됨.
	makeMap();

	scanf("%d", &s);

	for (int tc = 0; tc < s; tc++) {
		int y, x;
		scanf("%d", &y);
		scanf("%d", &x);

		if (map[y][x] == 0) {
			cout << "0" << "\n";
		}
		else {
			cout << map[y][x] << "\n";
		}
	}

	return 0;
}