#include <iostream>
#include <queue>

using namespace std;

struct Point
{
	int y, x;
	int wall;
	Point(int y, int x, int wall) {
		this->wall = wall;
		this->y = y;
		this->x = x;
	}
};

int N, X, Y;
int ans = 987654321;
int map[15][12];
int c_map[15][12];
int test[3] = { 0,1,5 };
int val[15];
int dx[4] = { 0,0,1,-1 };
int dy[4] = { 1,-1,0,0 };

void copy_map(int f) {
	// 되돌리기
	if (f == 1) {
		for (int i = 0; i < Y; i++) {
			for (int k = 0; k < X; k++) {
				map[i][k] = c_map[i][k];
			}
		}
	}
	// 복사
	else if (f == 2) {
		for (int i = 0; i < Y; i++) {
			for (int k = 0; k < X; k++) {
				c_map[i][k] = map[i][k];
			}
		}
	}

	return;
}

void counting_wall(){

	int cnt = 0;
	for (int i = 0; i < Y; i++) {
		for (int k = 0; k < X; k++) {
			if (map[i][k] != 0) cnt++;
		}
	}

	if (ans > cnt)
		ans = cnt;

	return;
}

void down() {
	int flag = 0;
	for (int i = 0; i < X; i++) {
		for (int k = 0; k < Y; k++) {
			if (map[k][i] != 0 && flag == 0) {
				flag = 1;
			}
			if (map[k][i] == 0 && flag == 1) {
				for (int r = k; r > 0; r--) {
					map[r][i] = map[r - 1][i];
				}
				map[0][i] = 0;
			}
		}
	}
}

void bfs(int y, int x, int wall) {
	queue<Point>q;
	q.push(Point(y, x, wall));

	while (!q.empty()) {
		int cx = q.front().x;
		int cy = q.front().y;
		int cw = q.front().wall;

		map[cy][cx] = 0;

		q.pop();

		for (int i = 0; i < 4; i++) {
			int ccx = cx;
			int ccy = cy;
			for (int k = 1; k < cw; k++) {
				int nx = ccx + dx[i];
				int ny = ccy + dy[i];

				if (nx < 0 || ny < 0 || nx >= X || ny >= Y || map[ny][nx] == 0) {
					ccx = nx;
					ccy = ny;
					continue;
				}

				if (map[ny][nx] == 1) {
					map[ny][nx] = 0;
				}
				else {
					q.push(Point(ny, nx, map[ny][nx]));
					map[ny][nx] = 0;
				}

				ccx = nx;
				ccy = ny;
			}
		}
	}
}

void dfs(int n, int cnt) {
	if (n == cnt) {
		//// 순열 찾음
		// map 복사
		copy_map(2);

		for (int i = 0; i < n; i++) {
			int at = val[i];

			// 본격 벽돌깨기
			for (int k = 0; k < Y; k++) {
				if (map[k][at] != 0) {
					bfs(k, at, map[k][at]);
					break;
				}
			}

			// 돌 내리기
			down();

		}
		// 남은 벽돌 세기
		counting_wall();

		// map 되돌리기
		copy_map(1);
		return;
	}

	for (int i = 0; i < X; i++) {
		val[cnt] = i;
		dfs(n, cnt + 1);
	}
}

int main() {
	int t;
	cin >> t;

	for (int tc = 1; tc <= t; tc++) {

		cin >> N >> X >> Y;

		for (int i = 0; i < Y; i++) {
			for (int k = 0; k < X; k++) {
				cin >> map[i][k];
			}
		}

		// N개의 순열 찾기 중복 허용
		dfs(N, 0);

		cout << "#" << tc << " " << ans << endl;

		// 초기화
		ans = 987654321;
	}

	return 0;
}