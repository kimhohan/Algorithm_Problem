#include <iostream>
#include <vector>

using namespace std;

struct Point
{
	int y, x, c;
};

vector<Point> v;
int map[51][51];
int map_c[51][51];
int copy_map[51][51];
int visit[7];
int val[7];
int Y, X, K;
int ans = 987654321;

void find_A() {
	int res = 987654321;
	for (int i = 0; i < Y; i++) {
		int sum = 0;
		for (int k = 0; k < X; k++) {
			sum += map[i][k];
		}
		if (res > sum)
			res = sum;
	}

	if (ans > res)
		ans = res;
}

void init_copy() {
	for (int i = 0; i < Y; i++) {
		for (int k = 0; k < X; k++) {
			copy_map[i][k] = 0;
		}
	}
}

void copy_m(int f) {
	if (f == 1) {
		for (int i = 0; i < Y; i++) {
			for (int k = 0; k < X; k++) {
				map_c[i][k] = map[i][k];
			}
		}
	}
	else if (f == 2) {
		for (int i = 0; i < Y; i++) {
			for (int k = 0; k < X; k++) {
				map[i][k] = map_c[i][k];
			}
		}
	}
}

void rotation(int y, int x, int t, int c) {

	int cx = x;
	int cy = y;
	int ct = t;
	// 회전
	for (int r = 0; r < c; r++) {
		// 가장 끝에 면부터 회전
		for (int i = 0; i < 4; i++) {
			if (i == 0) {
				for (int k = 0; k < t - 1; k++) {
					copy_map[y + k][x] = map[y + (k + 1)][x];
				}
			}
			if (i == 1) {
				for (int k = 0; k < t - 1; k++) {
					copy_map[y + t - 1][x + k] = map[y + t - 1][x + (k + 1)];
				}
			}
			if (i == 2) {
				for (int k = 0; k < t - 1; k++) {
					copy_map[y + (t - 1 - k)][x + t - 1] = map[y + (t - 1 - k - 1)][x + t - 1];
				}
			}
			if (i == 3) {
				for (int k = 0; k < t - 1; k++) {
					copy_map[y][x + (t - 1 - k)] = map[y][x + (t - 1 - k - 1)];
				}
			}
		}
		// 위치 갱신
		y = y + 1;
		x = x + 1;
		t = t - 2;
	}

	// map에 적용
	for (int i = cy; i < cy + ct; i++) {
		for (int k = cx; k < cx + ct; k++) {
			map[i][k] = copy_map[i][k];
		}
	}

}

void dfs(int cnt, int count) {
	if (cnt == count) {
		/*for (int i = 0; i < count; i++) {
			cout << val[i] << " ";
		}
		cout << endl;*/
		// map 복사
		copy_m(1);

		// 조합을 찾았으니 회전시작
		for (int i = 0; i < v.size(); i++) {
			int cy = v[val[i]].y;
			int cx = v[val[i]].x;
			int cc = v[val[i]].c;

			// 회전할 범위 설정
			int T = (2 * cc) + 1;

			// 중심은 그대로
			copy_map[cy][cx] = map[cy][cx];

			rotation((cy - cc), (cx - cc), T, cc);

			init_copy();
		}
		// A배열의 최솟값찾기
		find_A();

		// map되돌리기
		copy_m(2);
	}
	for (int i = 0; i < count; i++) {
		if (visit[i] == 1) continue;
		visit[i] = 1;
		val[cnt] = i;
		dfs(cnt + 1, count);
		visit[i] = 0;
	}
}

int main() {
	cin >> Y >> X >> K;
	
	// map 초기화
	for (int i = 0; i < Y; i++) {
		for (int k = 0; k < X; k++) {
			cin >> map[i][k];
		}
	}

	// 회전 벡터에 입력
	for (int i = 0; i < K; i++) {
		Point p;
		cin >> p.y >> p.x >> p.c;
		p.y--;
		p.x--;
		v.push_back(p);
	}

	// K개의 중복을 허용하지 않는 순열을 찾기
	dfs(0,K);

	// 출력
	cout << ans << endl;

	return 0;
}