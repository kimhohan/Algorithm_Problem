#include<iostream>

using namespace std;

int N, M, C;
int map[10][10];
int max_map[10][10];

void init() {

	for (int i = 0; i < N; i++) {
		for (int k = 0; k < N; k++) {
			max_map[i][k] = 0;
		}
	}
}

void makeMaxMap(int y, int x, int cnt, int sum, int pow) {

	if (sum > C) return;

	if (cnt == M) {
		if (max_map[y][x - M] < pow) {
			max_map[y][x - M] = pow;
		}
		return;
	}

	// 원소 선택
	makeMaxMap(y, x + 1, cnt + 1, sum + map[y][x], pow + (map[y][x] * map[y][x]));

	// 원소 비선택
	makeMaxMap(y, x + 1, cnt + 1, sum, pow);
}

int getMaxNum() {
	int max = 0, temp = 0;

	// 일꾼 A 기준 선택
	for (int i = 0; i < N; i++) {
		for (int k = 0; k <= N - M; k++) {
			// B일꾼 선택
			// 같은 행기준
			for (int k2 = k + M; k2 <= N - M; k2++) {
				temp = max_map[i][k] + max_map[i][k2];
				if (max < temp) {
					max = temp;
				}
			}

			// 다음행부터 마지막 행까지 선택
			for (int i2 = i + 1; i2 < N; i2++) {
				for (int k2 = 0; k2 <= N - M; k2++) {
					temp = max_map[i][k] + max_map[i2][k2];
					if (max < temp) {
						max = temp;
					}
				}
			}
		}
	}

	return max;
}

int main() {

	int t;
	cin >> t;

	for (int tc = 1; tc <= t; tc++) {
		cin >> N >> M >> C;

		// map 입력
		for (int i = 0; i < N; i++) {
			for (int k = 0; k < N; k++) {
				cin >> map[i][k];
			}
		}

		// max map 만들기
		for (int i = 0; i < N; i++) {
			for (int k = 0; k < N; k++) {
				makeMaxMap(i, k, 0, 0, 0);
			}
		}

		// 최대 원소값 뽑아내기
		cout << "#" << tc << " " << getMaxNum() << endl;

		// maxmap 초기화
		init();
	}

	return 0;
}
